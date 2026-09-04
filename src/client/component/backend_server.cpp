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
		utils::hook::detour http_codec_begin_encode_hook;
		utils::hook::detour http_codec_end_decode_hook;

		vars::var_ptr var_server_logging;
		vars::var_ptr var_net_server_heartbeat;

		std::string get_dump_path(const std::string cmd_name, const bool request)
		{
			static const auto folder = backend_server::is_using_custom_server() ? "server_dump/custom" : "server_dump/konami";

			const auto request_folder = request ? "requests" : "responses";
			const auto name = utils::string::va("tpp-mod/%s/%s/%s/%lli.json", folder, request_folder,
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

			if (var_server_logging->current.enabled())
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
			if (var_server_logging->current.enabled())
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
	}

	bool is_using_custom_server()
	{
		return false;
	}

	class component final : public component_interface
	{
	public:
		void pre_load() override
		{
			var_server_logging = vars::register_bool("net_server_logging", false, vars::var_flag_saved, "enable server logging");
		}

		void start() override
		{
			http_codec_begin_encode_hook.create(0x141C102E0_r, http_codec_begin_encode_stub);
			http_codec_end_decode_hook.create(0x141C10B60_r, http_codec_end_decode_stub);
		}
	};
}

REGISTER_COMPONENT(backend_server::component)
