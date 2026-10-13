#include <std_include.hpp>

#include "base.hpp"

#include "steam_utils.hpp"

namespace steam
{
	namespace
	{
		unsigned int get_app_id(game::ISteamUtils*)
		{
			return 543900;
		}

		bool is_overlay_enabled(game::ISteamUtils*)
		{
			return false;
		}
	}

	game::ISteamUtils* steam_utils::create()
	{
		static game::ISteamUtils instance{};
		static game::ISteamUtils_vtbl vtable{};

		init_vtable(vtable);

		instance.__vftable = &vtable;
		instance.__vftable->GetAppID = get_app_id;
		instance.__vftable->IsOverlayEnabled = is_overlay_enabled;

		return &instance;
	}

	game::ISteamUtils* steam_utils::get_instance()
	{
		static const auto instance = create();
		return instance;
	}
}
