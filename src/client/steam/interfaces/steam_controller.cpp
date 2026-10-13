#include <std_include.hpp>

#include "steam_controller.hpp"

namespace steam
{
	namespace
	{

	}

	game::ISteamController* steam_controller::create()
	{
		static game::ISteamController instance{};
		static game::ISteamController_vtbl vtable{};

		instance.__vftable = &vtable;

		return &instance;
	}

	game::ISteamController* steam_controller::get_instance()
	{
		static const auto instance = create();
		return instance;
	}
}
