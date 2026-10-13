#include <std_include.hpp>

#include "steam_video.hpp"

namespace steam
{
	namespace
	{

	}

	game::ISteamVideo* steam_video::create()
	{
		static game::ISteamVideo instance{};
		static game::ISteamVideo_vtbl vtable{};

		instance.__vftable = &vtable;

		return &instance;
	}

	game::ISteamVideo* steam_video::get_instance()
	{
		static const auto instance = create();
		return instance;
	}
}
