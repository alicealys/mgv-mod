#pragma once

#include "game/game.hpp"

namespace steam
{
	struct steam_music
	{
		static game::ISteamMusic* create();
		static game::ISteamMusic* get_instance();
	};
}
