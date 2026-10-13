#include <std_include.hpp>

#include "steam_htmlsurface.hpp"

namespace steam
{
	namespace
	{

	}

	game::ISteamHTMLSurface* steam_htmlsurface::create()
	{
		static game::ISteamHTMLSurface instance{};
		static game::ISteamHTMLSurface_vtbl vtable{};

		instance.__vftable = &vtable;

		return &instance;
	}

	game::ISteamHTMLSurface* steam_htmlsurface::get_instance()
	{
		static const auto instance = create();
		return instance;
	}
}
