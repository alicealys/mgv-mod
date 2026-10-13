#pragma once

#include "game/game.hpp"

namespace steam
{
	struct steam_matchmakingservers
	{
		static game::ISteamMatchmakingServers* create();
		static game::ISteamMatchmakingServers* get_instance();
	};
}
