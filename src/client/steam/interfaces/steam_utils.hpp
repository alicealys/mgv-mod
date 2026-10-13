#pragma once

#include "game/game.hpp"

namespace steam
{
	struct steam_utils
	{
		static game::ISteamUtils* create();
		static game::ISteamUtils* get_instance();
	};
}
