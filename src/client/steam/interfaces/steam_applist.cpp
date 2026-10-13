#include <std_include.hpp>

#include "steam_applist.hpp"

namespace steam
{
	namespace
	{

	}

	game::ISteamAppList* steam_applist::create()
	{
		static game::ISteamAppList instance{};
		static game::ISteamAppList_vtbl vtable{};

		instance.__vftable = &vtable;

		return &instance;
	}

	game::ISteamAppList* steam_applist::get_instance()
	{
		static const auto instance = create();
		return instance;
	}
}
