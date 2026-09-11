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
			add_data("challenge_task_list", "CMD_CHALLENGE_TASK_GET_LIST");

			add_building_info(save_data["building"][0], 0);
			add_building_info(save_data["building"][1], 1);

			const auto steam = game::get_steam_interfaces();
			const auto timestamp = utils::string::get_timestamp();
			game::steam_id user_id{};
			steam->steamUser->__vftable->GetSteamID(steam->steamUser, &user_id);

			save_data["server_url"] = backend_server::get_gate_url();
			save_data["timestamp"] = timestamp;
			save_data["steam_id"] = user_id.bits;

			const auto data_path = filesystem::get_config_path().generic_string();
			const auto save_path = std::format("{}/saves/save-{}.json", data_path, timestamp);
			const auto data = save_data.dump(4);

			if (!utils::io::write_file(save_path, data))
			{
				console::error("[savedata] failed to write save data");
			}
			else
			{
				console::info("[savedata] save data dumped to \"%s\"\n", save_path.data());
			}
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
		}
	};
}

REGISTER_COMPONENT(savedata::component)
