#include <std_include.hpp>

#include "steam_ugc.hpp"

namespace steam
{
	namespace
	{

	}

	game::ISteamUGC* steam_ugc::create()
	{
		static game::ISteamUGC instance{};
		static game::ISteamUGC_vtbl vtable{};

		instance.__vftable = &vtable;

		return &instance;
	}

	game::ISteamUGC* steam_ugc::get_instance()
	{
		static const auto instance = create();
		return instance;
	}
}
