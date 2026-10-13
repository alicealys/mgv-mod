#pragma once

#include "game/game.hpp"

namespace steam
{
	struct steam_applist
	{
		static game::ISteamAppList* create();
		static game::ISteamAppList* get_instance();
	};
}
