#pragma once

#include "game/game.hpp"

namespace steam
{
	struct steam_remotestorage
	{
		static game::ISteamRemoteStorage* create();
		static game::ISteamRemoteStorage* get_instance();
	};
}
