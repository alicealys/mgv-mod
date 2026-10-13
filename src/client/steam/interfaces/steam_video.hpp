#pragma once

#include "game/game.hpp"

namespace steam
{
	struct steam_video
	{
		static game::ISteamVideo* create();
		static game::ISteamVideo* get_instance();
	};
}
