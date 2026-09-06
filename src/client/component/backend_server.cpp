#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/game.hpp"

#include "scheduler.hpp"
#include "console.hpp"
#include "vars.hpp"
#include "backend_server.hpp"

#include <utils/string.hpp>
#include <utils/hook.hpp>
#include <utils/flags.hpp>
#include <utils/io.hpp>
#include <utils/cryptography.hpp>
#include <utils/http.hpp>
#include <utils/compression.hpp>
#include <utils/properties.hpp>

namespace backend_server
{
	namespace
	{
		char custom_url[0x100]{};

		utils::hook::detour http_codec_begin_encode_hook;
		utils::hook::detour http_codec_end_decode_hook;

		vars::var_ptr var_net_custom_server;
		vars::var_ptr var_net_server_logging;
		vars::var_ptr var_net_proxy_url;

		game::ISteamRemoteStorage_vtbl steam_remote_storage_vtbl{};

		std::unordered_set<std::string> savefile_names =
		{
			//{"PERSONAL_DATA"},
			//{"PERSONAL_DATA0"},
			//{"PERSONAL_DATA1"},
			{"SSD_GAME_DATA"},
			{"SSD_GAME_DATA0"},
			{"SSD_GAME_DATA1"},
		};

		std::string get_url_hash()
		{
			const auto url_hash = utils::cryptography::sha1::compute(custom_url, true).substr(0, 8);
			return url_hash;
		}

		std::uint64_t get_user_steamid()
		{
			const auto steam_user = game::get_steam_interfaces()->steamUser;
			game::steam_id steam_id{};
			steam_user->__vftable->GetSteamID(steam_user, &steam_id);
			return steam_id.bits;
		}

		std::string get_base_path()
		{
			const auto steam_id = get_user_steamid();
			const auto appdata = utils::properties::get_appdata_path();
			return std::format("{}\\userdata\\{}", appdata.generic_string(), steam_id);
		}

		std::string get_data_folder()
		{
			const auto url_hash = get_url_hash();
			return std::format("{}\\steam_storage\\server-{}", get_base_path(), url_hash);
		}

		std::string get_auth_token_save_path()
		{
			const auto url_hash = get_url_hash();
			return std::format("{}\\auth_tokens\\{}", get_base_path(), url_hash);
		}

		std::string get_data_file_path(const std::string& file_name)
		{
			const auto folder = get_data_folder();
			return std::format("{}\\{}", folder, file_name);
		}

		std::string get_dump_path(const std::string cmd_name, const bool request)
		{
			static const auto folder = backend_server::is_using_custom_server() ? "server_dump/custom" : "server_dump/konami";

			const auto request_folder = request ? "requests" : "responses";
			const auto name = utils::string::va("mgv-mod/%s/%s/%s/%lli.json", folder, request_folder,
				cmd_name.data(), GetTickCount64());

			return name;
		}

		std::string get_fox_buffer(game::fox::Buffer* buffer)
		{
			return std::string{buffer->data, buffer->data + buffer->size};
		}

		void* http_codec_end_decode_stub(void* this_, void* ctx, game::fox::Buffer* buffer)
		{
			const auto res = http_codec_end_decode_hook.invoke<void*>(this_, ctx, buffer);

			if (var_net_server_logging->current.enabled())
			{
				const auto data = get_fox_buffer(buffer);
				const auto json = nlohmann::json::parse(data);
				const auto cmd = json["msgid"].get<std::string>();

				console::info("[net] received response for command \"%s\"", cmd.data());

				const auto path = get_dump_path(cmd, false);
				utils::io::write_file(path, json.dump(4));
			}

			return res;
		}

		void* http_codec_begin_encode_stub(void* this_, void* ctx, game::fox::Buffer* buffer, void* session_key)
		{
			if (var_net_server_logging->current.enabled())
			{
				const auto data = get_fox_buffer(buffer);
				const auto json = nlohmann::json::parse(data);
				const auto cmd = json["msgid"].get<std::string>();

				console::info("[net] sending request for command \"%s\"", cmd.data());

				const auto path = get_dump_path(cmd, true);
				utils::io::write_file(path, json.dump(4));
			}

			return http_codec_begin_encode_hook.invoke<void*>(this_, ctx, buffer, session_key);
		}

		std::wstring parse_proxy_url(const std::string& url)
		{
			auto url_w = utils::string::convert(url);

			while (url_w.ends_with(L"/"))
			{
				url_w.pop_back();
			}

			return url_w;
		}

		int steam_storage_file_read_stub(game::ISteamRemoteStorage* inst, const char* file, void* data, int size)
		{
			printf("[ISteamStorage] FileRead %s\n", file);

			if (!savefile_names.contains(file))
			{
				return steam_remote_storage_vtbl.FileRead(inst, file, data, size);
			}

			const auto path = get_data_file_path(file);
			std::string file_data;
			if (!utils::io::read_file(path, &file_data))
			{
				return steam_remote_storage_vtbl.FileRead(inst, file, data, size);
			}

			if (file_data.size() > size)
			{
				return 0;
			}

			std::memcpy(data, file_data.data(), file_data.size());
			return static_cast<int>(file_data.size());
		}

		bool steam_storage_file_write_stub(game::ISteamRemoteStorage* inst, const char* file, void* data, int size)
		{
			printf("[ISteamStorage] FileWrite %s\n", file);

			if (!savefile_names.contains(file))
			{
				return steam_remote_storage_vtbl.FileWrite(inst, file, data, size);
			}

			const auto path = get_data_file_path(file);
			const auto file_data = std::string{reinterpret_cast<char*>(data), static_cast<std::size_t>(size)};
			return utils::io::write_file(path, file_data, false);
		}

		HANDLE create_file_stub(LPCWSTR file_name, DWORD desired_access, DWORD share_mode,
			LPSECURITY_ATTRIBUTES security_attributes, DWORD creation_disp, DWORD flags, HANDLE template_file)
		{
			const auto get_new_path = [&]()
				-> std::wstring
			{
				const auto name = utils::string::convert(file_name);
				const auto base_name = name.substr(name.find_last_of("/\\") + 1);

				if (!savefile_names.contains(base_name))
				{
					return file_name;
				}

				console::info("[LocalStorage] Create file \"%s\"\n", base_name.data());

				const auto path = get_data_file_path(base_name);
				return utils::string::convert(path);
			};

			const auto new_path = get_new_path();
			return CreateFileW(file_name, desired_access, share_mode, security_attributes, creation_disp, flags, template_file);
		}

		void apply_custom_server()
		{
			const auto& custom_server = var_net_custom_server->current.get_string();
			if (custom_server.empty())
			{
				return;
			}

			std::memcpy(custom_url, custom_server.data(), custom_server.size());
			console::info("[net] using server url: \"%s\"\n", custom_url);

			utils::hook::far_inject(0x140895ED1_r + 3, custom_url);
			utils::hook::set(0x141FEA470_r, create_file_stub);
		}

		BOOL win_http_set_option_stub(HINTERNET handle, DWORD option, LPVOID buffer, DWORD buffer_length)
		{
			auto result = WinHttpSetOption(handle, option, buffer, buffer_length);

			const auto& url = var_net_proxy_url->current.get_string();
			if (!url.empty())
			{
				auto url_w = parse_proxy_url(url);
				WINHTTP_PROXY_INFO proxy = {};
				proxy.dwAccessType = WINHTTP_ACCESS_TYPE_NAMED_PROXY;
				proxy.lpszProxy = url_w.data();
				result &= WinHttpSetOption(handle, WINHTTP_OPTION_PROXY, &proxy, sizeof(proxy));
			}

			if (result == 0)
			{
				console::error("error setting http proxy: %i", GetLastError());
			}

			return result;
		}

		void patch_win_http()
		{
			utils::hook::nop(0x14197E776_r, 6);
			utils::hook::far_call(0x14197E776_r, win_http_set_option_stub);
		}
	}

	bool is_using_custom_server()
	{
		return custom_url[0] != 0;
	}

	class component final : public component_interface
	{
	public:
		void pre_load() override
		{
			var_net_custom_server = vars::register_string("net_custom_server", "", vars::var_flag_saved | vars::var_flag_latched, "custom server url (empty = disabled)");
			var_net_proxy_url = vars::register_string("net_proxy_url", "", vars::var_flag_saved, "proxy url for backend server (example: http://1.2.3.4:1234 empty = disabled)");

			var_net_server_logging = vars::register_bool("net_server_logging", false, vars::var_flag_saved, "enable server logging");
		}

		void start() override
		{
			apply_custom_server();
			patch_win_http();

			http_codec_begin_encode_hook.create(0x141C102E0_r, http_codec_begin_encode_stub);
			http_codec_end_decode_hook.create(0x141C10B60_r, http_codec_end_decode_stub);
		}

		void game_initialized() override
		{
			if (!is_using_custom_server())
			{
				return;
			}

			const auto steam_interfaces = game::get_steam_interfaces();
			std::memcpy(&steam_remote_storage_vtbl, steam_interfaces->steamRemoteStorage->__vftable, sizeof(steam_remote_storage_vtbl));

			utils::hook::set(&steam_interfaces->steamRemoteStorage->__vftable->FileRead, steam_storage_file_read_stub);
			utils::hook::set(&steam_interfaces->steamRemoteStorage->__vftable->FileWrite, steam_storage_file_write_stub);
		}
	};
}

REGISTER_COMPONENT(backend_server::component)
