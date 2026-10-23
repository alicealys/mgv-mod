#pragma once

#include "game/game.hpp"

namespace steam
{
	struct steam_remotestorage
	{
		static std::string get_file_path(const char* file);
		static game::ISteamRemoteStorage* create();
		static game::ISteamRemoteStorage* get_instance();
	};
}
