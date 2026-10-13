#pragma once

#include "game/game.hpp"

namespace steam
{
	struct steam_ugc
	{
		static game::ISteamUGC* create();
		static game::ISteamUGC* get_instance();
	};
}
