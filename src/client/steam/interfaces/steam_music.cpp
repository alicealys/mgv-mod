#include <std_include.hpp>

#include "steam_music.hpp"

namespace steam
{
	namespace
	{

	}

	game::ISteamMusic* steam_music::create()
	{
		static game::ISteamMusic instance{};
		static game::ISteamMusic_vtbl vtable{};

		instance.__vftable = &vtable;

		return &instance;
	}

	game::ISteamMusic* steam_music::get_instance()
	{
		static const auto instance = create();
		return instance;
	}
}
