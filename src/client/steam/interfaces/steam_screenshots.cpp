#include <std_include.hpp>

#include "steam_screenshots.hpp"

namespace steam
{
	namespace
	{

	}

	game::ISteamScreenshots* steam_screenshots::create()
	{
		static game::ISteamScreenshots instance{};
		static game::ISteamScreenshots_vtbl vtable{};

		instance.__vftable = &vtable;

		return &instance;
	}

	game::ISteamScreenshots* steam_screenshots::get_instance()
	{
		static const auto instance = create();
		return instance;
	}
}
