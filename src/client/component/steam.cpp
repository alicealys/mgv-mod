#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/game.hpp"
#include "steam/steam.hpp"

#include "steam.hpp"

#include <utils/flags.hpp>

namespace steam
{
	vars::var_ptr var_steam_emulator_enable;
	vars::var_ptr var_steam_emulator_id;

	bool is_nosteam()
	{
		static const auto result = utils::flags::has_flag("nosteam");
		return result || var_steam_emulator_enable->current.enabled();
	}

	class component final : public component_interface
	{
	public:
		void pre_load() override
		{
			var_steam_emulator_enable = vars::register_bool("steam_emulator_enable", false,
				vars::var_flag_saved | vars::var_flag_latched, "enable steam emulator");

			var_steam_emulator_id = vars::register_int64("steam_emulator_id", 76561197960265728, 
				0, 0, vars::var_flag_saved | vars::var_flag_latched, "steam emulator user id");
		}
		
		void start() override
		{
			if (is_nosteam())
			{
				steam::disable_steam();
			}
		}

		void game_initialized() override
		{
			if (is_nosteam())
			{
				return;
			}

			if (var_steam_emulator_id->current == var_steam_emulator_id->reset)
			{
				const auto steam_user = game::get_steam_interfaces()->steamUser;
				game::steam_id steam_id{};
				steam_user->__vftable->GetSteamID(steam_user, &steam_id);
				vars::set_var(var_steam_emulator_id, static_cast<std::int64_t>(steam_id.bits), vars::var_source_external);
			}
		}
	};
}

REGISTER_COMPONENT(steam::component)
