#pragma once

#include "game/game.hpp"

namespace steam
{
	struct steam_user
	{
		static game::steam_id get_steam_id();

		static game::ISteamUser* create();
		static game::ISteamUser* get_instance();
	};
}
