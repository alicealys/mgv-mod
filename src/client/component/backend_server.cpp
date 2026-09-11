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

				auto json = nlohmann::json::parse(data);
				auto cmd = json["msgid"].get<std::string>();
				auto result = json["result"].get<std::string>();

				if (result == "NOERR")
				{
					console::info("[net] received response for command \"%s\": %s", cmd.data(), result.data());
				}
				else
				{
					console::error("[net] received response for command \"%s\": %s", cmd.data(), result.data());
				}

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

				auto json = nlohmann::json::parse(data);
				auto cmd = json["msgid"].get<std::string>();

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

		std::uint8_t* get_static_key()
		{
			static std::uint8_t static_key[16] =
			{
				0x17, 0xF0, 0xF7, 0xA6, 
				0x2E, 0x8F, 0xEE, 0x67, 
				0x78, 0x66, 0x79, 0xD0, 
				0x8C, 0x8A, 0x0A, 0x1C
			};

			return static_key;
		}

		std::string encrypt_data(const std::string& data, game::fox::ncl::NclDaemon* ncl_daemon)
		{
			utils::cryptography::blowfish blow;

			auto key = ncl_daemon != nullptr
				? ncl_daemon->key
				: get_static_key();

			blow.set_key(key, 16);
			return blow.encrypt(data);
		}

		std::string decrypt_data(const std::string& data, game::fox::ncl::NclDaemon* ncl_daemon)
		{
			utils::cryptography::blowfish blow;

			auto key = ncl_daemon != nullptr
				? ncl_daemon->key
				: get_static_key();

			blow.set_key(key, 16);
			return blow.decrypt(data);
		}

		std::string serialize_message(const nlohmann::json& data, game::fox::ncl::NclDaemon* ncl_daemon)
		{
			nlohmann::json message;

			auto compress = false;

			const auto use_crypto = ncl_daemon != nullptr && ncl_daemon->sessionKey.data != nullptr;

			message["compress"] = compress;
			message["session_crypto"] = use_crypto;
			message["session_key"] = use_crypto ? ncl_daemon->sessionKey.data->buffer : "";

			auto data_serialized = data.dump();
			const auto original_size = data_serialized.size();

			if (compress)
			{
				data_serialized = utils::compression::zlib::compress(data_serialized);
			}

			if (use_crypto)
			{
				data_serialized = encrypt_data(data_serialized, ncl_daemon);
			}

			if (compress && !use_crypto)
			{
				data_serialized = utils::cryptography::base64::encode(data_serialized);
			}

			message["data"] = data_serialized;
			message["original_size"] = original_size;

			auto message_serialized = message.dump();
			message_serialized = encrypt_data(message_serialized, nullptr);

			return message_serialized;
		}

		std::optional<nlohmann::json> deserialize_message(const std::string& data, game::fox::ncl::NclDaemon* ncl_daemon)
		{
			auto message_deserialized = utils::string::replace(data, "\r\n", "");
			message_deserialized = decrypt_data(message_deserialized, nullptr);

			auto message = nlohmann::json::parse(message_deserialized);

			if (!message["data"].is_string())
			{
				return {message};
			}

			auto message_data = message["data"].get<std::string>();
			const auto compressed = message["compress"].is_boolean() && message["compress"].get<bool>();
			const auto session_crypto = message["session_crypto"].is_boolean() && message["session_crypto"].get<bool>();

			if (session_crypto)
			{
				message_data = utils::string::replace(message_data, "\r\n", "");
				message_data = decrypt_data(message_data, ncl_daemon);
			}

			if (compressed)
			{
				message_data = utils::compression::zlib::decompress(message_data);
			}

			message["data"] = nlohmann::json::parse(message_data);
			return {message};
		}
	}

	std::optional<nlohmann::json> send_command(const std::string& endpoint, const nlohmann::json& data, bool use_session)
	{
		const auto ncl_daemon = *game::fox::ncl::NclDaemon_::s_instance;
		const auto endpoint_id = game::fox::FoxStrHash32(endpoint.data(), std::strlen(endpoint.data()));
		const auto url = game::fox::ncl::NclDaemon_::GetUrl(ncl_daemon, endpoint_id);

		if (url == nullptr)
		{
			return {};
		}

		const auto crypto = use_session ? ncl_daemon : nullptr;
		auto post_data = serialize_message(data, crypto);

		utils::http::headers headers;
		headers["Connection"] = "Keep-Alive";
		headers["Content-Type"] = "application/json";

		const auto& proxy_url = var_net_proxy_url->current.get_string();
		const auto result = utils::http::post_data(url->data->buffer, post_data, headers, {}, proxy_url);
		if (!result.has_value())
		{
			return {};
		}

		const auto& value = result.value();
		if (value.response_code != 200)
		{
			return {};
		}

		if (value.buffer.size() == 0)
		{
			return {};
		}

		const auto msg = deserialize_message(value.buffer, crypto);
		if (msg.has_value() && msg->contains("data"))
		{
			return {msg->operator[]("data")};
		}

		return {};
	}
	
	std::optional<nlohmann::json> send_command(const std::string& endpoint, const char* cmd, bool use_session)
	{
		nlohmann::json request;
		request["msgid"] = cmd;
		request["rqid"] = 0;
		return send_command(endpoint, request, use_session);
	}

	bool is_using_custom_server()
	{
		return var_net_ncl_url->current != var_net_ncl_url->reset && !var_net_ncl_url->current.get_string().empty();
	}

	std::string get_gate_url()
	{
		if (is_using_custom_server())
		{
			return var_net_ncl_url->current.get_string();
		}

		return var_net_ncl_url->reset.get_string();
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
