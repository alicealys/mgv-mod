#pragma once

#include "game/game.hpp"

namespace steam
{
	struct steam_controller
	{
		static game::ISteamController* create();
		static game::ISteamController* get_instance();
	};
}
