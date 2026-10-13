#pragma once

#include "game/game.hpp"

namespace steam
{
	struct steam_networking
	{
		static game::ISteamNetworking* create();
		static game::ISteamNetworking* get_instance();
	};
}
