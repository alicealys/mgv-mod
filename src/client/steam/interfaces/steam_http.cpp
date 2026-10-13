#include <std_include.hpp>

#include "steam_http.hpp"

namespace steam
{
	namespace
	{

	}

	game::ISteamHTTP* steam_http::create()
	{
		static game::ISteamHTTP instance{};
		static game::ISteamHTTP_vtbl vtable{};

		instance.__vftable = &vtable;

		return &instance;
	}

	game::ISteamHTTP* steam_http::get_instance()
	{
		static const auto instance = create();
		return instance;
	}
}
