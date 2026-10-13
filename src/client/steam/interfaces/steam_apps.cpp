#include <std_include.hpp>

#include "base.hpp"

#include "steam_apps.hpp"

namespace steam
{
	namespace
	{
		bool b_is_subscribed(game::ISteamApps*)
		{
			return true;
		}

		bool b_is_dlc_installed(game::ISteamApps*, game::AppId_t app)
		{
			return true;
		}
	}

	game::ISteamApps* steam_apps::create()
	{
		static game::ISteamApps instance{};
		static game::ISteamApps_vtbl vtable{};

		init_vtable(vtable);

		instance.__vftable = &vtable;
		instance.__vftable->BIsSubscribed = b_is_subscribed;
		instance.__vftable->BIsDlcInstalled = b_is_dlc_installed;

		return &instance;
	}

	game::ISteamApps* steam_apps::get_instance()
	{
		static const auto instance = create();
		return instance;
	}
}
