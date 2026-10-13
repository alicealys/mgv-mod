#pragma once

#include "game/game.hpp"

namespace steam
{
	struct steam_apps
	{
		static game::ISteamApps* create();
		static game::ISteamApps* get_instance();
	};
}
