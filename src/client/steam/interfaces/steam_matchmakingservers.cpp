#include <std_include.hpp>

#include "steam_matchmakingservers.hpp"

namespace steam
{
	namespace
	{

	}

	game::ISteamMatchmakingServers* steam_matchmakingservers::create()
	{
		static game::ISteamMatchmakingServers instance{};
		static game::ISteamMatchmakingServers_vtbl vtable{};

		instance.__vftable = &vtable;

		return &instance;
	}

	game::ISteamMatchmakingServers* steam_matchmakingservers::get_instance()
	{
		static const auto instance = create();
		return instance;
	}
}
