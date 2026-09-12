#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/game.hpp"

#include "vars.hpp"
#include "scheduler.hpp"
#include "backend_server.hpp"
#include "filesystem.hpp"
#include "console.hpp"
#include "scripting.hpp"

#include <utils/hook.hpp>
#include <utils/flags.hpp>
#include <utils/string.hpp>
#include <utils/io.hpp>

namespace savedata
{
	namespace
	{
		void dump_save_data()
		{
			const auto is_logged_in = scripting::script_exec("return TppServerManager.IsLoginKonami()");
			if (!is_logged_in.has_value() || !is_logged_in->get_bool())
			{
				console::error("[savedata] you must be logged in to dump your save data!\n");
				return;
			}

			nlohmann::json save_data;

			const auto add_data = [&](const std::string& name, const std::string& cmd)
			{
				auto data = backend_server::send_command("WEB", cmd.data(), true);
				if (!data.has_value())
				{
					console::error("[savedata] failed to load %s from server\n", cmd.data());
					return false;
				}

				save_data["data"][name] = data.value();
				return true;
			};

			const auto add_building_info = [&](nlohmann::json& data_res, const std::uint32_t map_location)
			{
				nlohmann::json request;
				request["msgid"] = "CMD_BUILDING_LOAD";
				request["rqid"] = 0;
				request["map_location"] = map_location;

				auto data = backend_server::send_command("WEB", request, true);
				if (!data.has_value())
				{
					console::error("[savedata] failed to load CMD_BUILDING_LOAD %i from server\n", map_location);
					return false;
				}

				data_res = data.value();
				return true;
			};

			add_data("avatar", "CMD_AVATAR_LOAD");
			add_data("mission_progress", "CMD_MISSION_PROGRESS_LOAD");
			add_data("crew", "CMD_CREW_LOAD");
			add_data("base_resource", "CMD_BASE_RESOURCE_LOAD");
			add_data("deploy_team", "CMD_DEPLOY_LOAD_TEAM");
			add_data("player_list", "CMD_GET_PLAYERLIST");

			add_building_info(save_data["data"]["building"][0], 0);
			add_building_info(save_data["data"]["building"][1], 1);

			const auto steam = game::get_steam_interfaces();
			const auto timestamp = utils::string::get_timestamp();
			game::steam_id user_id{};
			steam->steamUser->__vftable->GetSteamID(steam->steamUser, &user_id);

			save_data["server_url"] = backend_server::get_gate_url();
			save_data["timestamp"] = timestamp;
			save_data["steam_id"] = user_id.bits;

			const auto data_path = filesystem::get_config_path().generic_string();
			const auto save_name = std::format("save-{}", timestamp);
			const auto save_path = std::format("{}/saves/{}.json", data_path, save_name);
			const auto data = save_data.dump(4);

			if (!utils::io::write_file(save_path, data))
			{
				console::error("[savedata] failed to write save data");
			}
			else
			{
				console::info("[savedata] save data dumped to \"%s\", use \"restoresave %s\" to restore it\n", save_name.data());
			}
		}

		void restore_save_data(const std::string& name)
		{
			if (!backend_server::is_using_custom_server())
			{
				console::error("[savedata] konami server does not support save restoration!\n");
				return;
			}

			const auto is_logged_in = scripting::script_exec("return TppServerManager.IsLoginKonami()");
			if (!is_logged_in.has_value() || !is_logged_in->get_bool())
			{
				console::error("[savedata] you must be logged in to restore your save data!\n");
				return;
			}

			const auto data_path = filesystem::get_config_path().generic_string();
			const auto save_path = std::format("{}/saves/{}.json", data_path, name);

			std::string data;
			if (!utils::io::read_file(save_path, &data))
			{
				console::error("[savedata] save file %s not found!\n", name.data());
				return;
			}

			auto save_data = nlohmann::json::parse(data, nullptr, false);
			if (save_data.is_discarded())
			{
				console::error("invalid save data\n");
				return;
			}

			save_data["data"]["msgid"] = "CMD_RESTORE_SAVE";
			save_data["data"]["rqid"] = 0;

			auto res = backend_server::send_command("WEB", save_data["data"], true);
			if (!res.has_value() || res->operator[]("result") != "NOERR")
			{
				console::error("[savedata] failed to restore savedata to server\n");
				return;
			}

			console::info("[savedata] savedata restored, restart your game\n");
		}
	}

	class component final : public component_interface
	{
	public:
		void pre_load() override
		{
			command::add("dumpsave", []()
			{
				scheduler::once(dump_save_data, scheduler::async);
			});

			command::add("restoresave", [](const command::params& params)
			{
				if (params.size() < 2)
				{
					console::info("usage: restoresave <name>\n");
					return;
				}

				const auto name = params.get(1);
				scheduler::once([name]
				{
					restore_save_data(name);
				}, scheduler::async);
			});
		}
	};
}

REGISTER_COMPONENT(savedata::component)
