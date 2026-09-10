#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/game.hpp"

#include "scheduler.hpp"
#include "console.hpp"
#include "vars.hpp"
#include "backend_server.hpp"
#include "filesystem.hpp"

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
		char ncl_url[0x100]{};
		char stun_server_host[0x100]{};

		utils::hook::detour http_codec_begin_encode_hook;
		utils::hook::detour http_codec_end_decode_hook;

		vars::var_ptr var_net_ncl_url;
		vars::var_ptr var_net_stun_server;
		vars::var_ptr var_net_server_logging;
		vars::var_ptr var_net_proxy_url;

		std::string get_url_hash()
		{
			const auto url_hash = utils::cryptography::sha1::compute(ncl_url, true).substr(0, 8);
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
			const auto& config_path = filesystem::get_config_path();
			return std::format("{}\\userdata\\{}", config_path.generic_string(), steam_id);
		}

		std::string get_auth_token_save_path()
		{
			const auto url_hash = get_url_hash();
			return std::format("{}\\auth_tokens\\{}", get_base_path(), url_hash);
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

		bool parse_address(const std::string& address, char* dest, const std::size_t dest_size, std::uint16_t* port)
		{
			if (address.size() > dest_size)
			{
				return false;
			}

			const auto sep = address.find(':');
			if (sep != std::string::npos)
			{
				*port = static_cast<std::uint16_t>(std::atol(&address[sep + 1]));
				strncpy_s(dest, dest_size, address.data(), sep);
			}
			else
			{
				strncpy_s(dest, dest_size, address.data(), address.size());
			}

			return true;
		}

		void apply_custom_server()
		{
			const auto& custom_server = var_net_ncl_url->current.get_string();
			if (!custom_server.empty())
			{
				std::memcpy(ncl_url, custom_server.data(), custom_server.size());
				console::info("[net] using ncl server url: \"%s\"\n", ncl_url);
				utils::hook::far_inject(0x140895ED1_r + 3, ncl_url);
			}

			std::uint16_t stun_port = 3478;
			const auto& stun_address = var_net_stun_server->current.get_string();
			if (!stun_address.empty() && parse_address(stun_address, stun_server_host, sizeof(stun_server_host), &stun_port))
			{
				console::info("[net] using stun server: \"%s:%i\"\n", stun_server_host, stun_port);
				utils::hook::far_inject(0x1418FCC7D_r + 3, stun_server_host);
				utils::hook::far_inject(0x14190075A_r + 3, stun_server_host);
				utils::hook::far_inject(0x141907B2A_r + 3, stun_server_host);
				utils::hook::far_inject(0x141907B3E_r + 3, stun_server_host);
				utils::hook::far_inject(0x14190F845_r + 3, stun_server_host);

				utils::hook::set<std::uint16_t>(0x1430B7BC0_r, stun_port);
				utils::hook::set<std::uint16_t>(0x140530769_r + 1, stun_port);
			}
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
		return var_net_ncl_url->current != var_net_ncl_url->reset && !var_net_ncl_url->current.get_string().empty();
	}

	class component final : public component_interface
	{
	public:
		void pre_load() override
		{
			var_net_ncl_url = vars::register_string("net_ncl_url", "https://mgssd-game.cs.konami.net/ssdstm/gate", vars::var_flag_saved | vars::var_flag_latched, "ncl server gate url");
			var_net_stun_server = vars::register_string("net_stun_server", "mgssd-stun.cs.konami.net:3478", vars::var_flag_saved | vars::var_flag_latched, "stun server address");
			var_net_proxy_url = vars::register_string("net_http_proxy_url", "", vars::var_flag_saved, "http proxy url (example: http://1.2.3.4:1234 empty = disabled)");

			var_net_server_logging = vars::register_bool("net_server_logging", false, vars::var_flag_saved, "enable server logging");
		}

		void start() override
		{
			apply_custom_server();
			patch_win_http();

			http_codec_begin_encode_hook.create(0x141C102E0_r, http_codec_begin_encode_stub);
			http_codec_end_decode_hook.create(0x141C10B60_r, http_codec_end_decode_stub);
		}
	};
}

REGISTER_COMPONENT(backend_server::component)
