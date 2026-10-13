#include <std_include.hpp>

#include "steam_inventory.hpp"

namespace steam
{
	namespace
	{

	}

	game::ISteamInventory* steam_inventory::create()
	{
		static game::ISteamInventory instance{};
		static game::ISteamInventory_vtbl vtable{};

		instance.__vftable = &vtable;

		return &instance;
	}

	game::ISteamInventory* steam_inventory::get_instance()
	{
		static const auto instance = create();
		return instance;
	}
}
