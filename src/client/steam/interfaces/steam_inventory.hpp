#pragma once

#include "game/game.hpp"

namespace steam
{
	struct steam_inventory
	{
		static game::ISteamInventory* create();
		static game::ISteamInventory* get_instance();
	};
}
