#pragma once

#include "game/game.hpp"

namespace steam
{
	struct steam_unifiedmessages
	{
		static game::ISteamUnifiedMessages* create();
		static game::ISteamUnifiedMessages* get_instance();
	};
}
