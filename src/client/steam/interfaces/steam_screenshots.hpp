#pragma once

#include "game/game.hpp"

namespace steam
{
	struct steam_screenshots
	{
		static game::ISteamScreenshots* create();
		static game::ISteamScreenshots* get_instance();
	};
}
