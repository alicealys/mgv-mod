#pragma once

#include "game/game.hpp"

namespace steam
{
	struct steam_http
	{
		static game::ISteamHTTP* create();
		static game::ISteamHTTP* get_instance();
	};
}
