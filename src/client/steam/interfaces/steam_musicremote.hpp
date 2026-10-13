#pragma once

#include "game/game.hpp"

namespace steam
{
	struct steam_musicremote
	{
		static game::ISteamMusicRemote* create();
		static game::ISteamMusicRemote* get_instance();
	};
}
