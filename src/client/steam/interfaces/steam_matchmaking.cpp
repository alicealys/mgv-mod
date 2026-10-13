#include <std_include.hpp>

#include "steam_matchmaking.hpp"

namespace steam
{
	namespace
	{

	}

	game::ISteamMatchmaking* steam_matchmaking::create()
	{
		static game::ISteamMatchmaking instance{};
		static game::ISteamMatchmaking_vtbl vtable{};

		instance.__vftable = &vtable;

		return &instance;
	}

	game::ISteamMatchmaking* steam_matchmaking::get_instance()
	{
		static const auto instance = create();
		return instance;
	}
}
