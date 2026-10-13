#pragma once

#include "game/game.hpp"

namespace steam
{
	struct steam_friends
	{
		static game::ISteamFriends* create();
		static game::ISteamFriends* get_instance();
	};
}
