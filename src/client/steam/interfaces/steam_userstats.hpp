#pragma once

#include "game/game.hpp"

namespace steam
{
	struct steam_userstats
	{
		static game::ISteamUserStats* create();
		static game::ISteamUserStats* get_instance();
	};
}
