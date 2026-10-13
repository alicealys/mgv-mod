#pragma once

#include "game/game.hpp"

namespace steam
{
	struct steam_htmlsurface
	{
		static game::ISteamHTMLSurface* create();
		static game::ISteamHTMLSurface* get_instance();
	};
}
