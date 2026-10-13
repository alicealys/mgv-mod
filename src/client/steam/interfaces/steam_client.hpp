#pragma once

#include "game/game.hpp"

namespace steam
{
	struct steam_client
	{
		static game::ISteamClient* create();
		static game::ISteamClient* get_instance();
	};
}
