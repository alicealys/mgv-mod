#include <std_include.hpp>

#include "steam_musicremote.hpp"

namespace steam
{
	namespace
	{

	}

	game::ISteamMusicRemote* steam_musicremote::create()
	{
		static game::ISteamMusicRemote instance{};
		static game::ISteamMusicRemote_vtbl vtable{};

		instance.__vftable = &vtable;

		return &instance;
	}

	game::ISteamMusicRemote* steam_musicremote::get_instance()
	{
		static const auto instance = create();
		return instance;
	}
}
