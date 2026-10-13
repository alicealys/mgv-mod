#pragma once

#include "game/game.hpp"

namespace steam
{
	struct steam_matchmaking
	{
		static game::ISteamMatchmaking* create();
		static game::ISteamMatchmaking* get_instance();
	};
}
