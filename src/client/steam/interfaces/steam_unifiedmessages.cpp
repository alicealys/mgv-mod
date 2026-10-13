#include <std_include.hpp>

#include "steam_unifiedmessages.hpp"

namespace steam
{
	namespace
	{

	}

	game::ISteamUnifiedMessages* steam_unifiedmessages::create()
	{
		static game::ISteamUnifiedMessages instance{};
		static game::ISteamUnifiedMessages_vtbl vtable{};

		instance.__vftable = &vtable;

		return &instance;
	}

	game::ISteamUnifiedMessages* steam_unifiedmessages::get_instance()
	{
		static const auto instance = create();
		return instance;
	}
}
