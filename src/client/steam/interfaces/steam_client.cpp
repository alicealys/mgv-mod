#include <std_include.hpp>

#include "base.hpp"

#include "steam_client.hpp"
#include "steam_user.hpp"
#include "steam_friends.hpp"
#include "steam_utils.hpp"
#include "steam_matchmaking.hpp"
#include "steam_matchmakingservers.hpp"
#include "steam_userstats.hpp"
#include "steam_apps.hpp"
#include "steam_networking.hpp"
#include "steam_remotestorage.hpp"
#include "steam_screenshots.hpp"
#include "steam_http.hpp"
#include "steam_unifiedmessages.hpp"
#include "steam_controller.hpp"
#include "steam_ugc.hpp"
#include "steam_applist.hpp"
#include "steam_music.hpp"
#include "steam_musicremote.hpp"
#include "steam_htmlsurface.hpp"
#include "steam_inventory.hpp"
#include "steam_video.hpp"


namespace steam
{
	namespace
	{
		game::ISteamUser* get_i_steam_user(game::ISteamClient*, game::HSteamUser, game::HSteamPipe, const char* version)
		{
			return steam_user::get_instance();
		}

		game::ISteamFriends* get_i_steam_friends(game::ISteamClient*, game::HSteamUser, game::HSteamPipe, const char* version)
		{
			return steam_friends::get_instance();
		}

		game::ISteamUtils* get_i_steam_utils(game::ISteamClient*, game::HSteamPipe, const char* version)
		{
			return steam_utils::get_instance();
		}

		game::ISteamMatchmaking* get_i_steam_matchmaking(game::ISteamClient*, game::HSteamUser, game::HSteamPipe, const char* version)
		{
			return steam_matchmaking::get_instance();
		}

		game::ISteamMatchmakingServers* get_i_steam_matchmaking_servers(game::ISteamClient*, game::HSteamUser, game::HSteamPipe, const char* version)
		{
			return steam_matchmakingservers::get_instance();
		}

		game::ISteamUserStats* get_i_steam_user_stats(game::ISteamClient*, game::HSteamUser, game::HSteamPipe, const char* version)
		{
			return steam_userstats::get_instance();
		}

		game::ISteamApps* get_i_steam_apps(game::ISteamClient*, game::HSteamUser, game::HSteamPipe, const char* version)
		{
			return steam_apps::get_instance();
		}

		game::ISteamNetworking* get_i_steam_networking(game::ISteamClient*, game::HSteamUser, game::HSteamPipe, const char* version)
		{
			return steam_networking::get_instance();
		}

		game::ISteamRemoteStorage* get_i_steam_remote_storage(game::ISteamClient*, game::HSteamUser, game::HSteamPipe, const char* version)
		{
			return steam_remotestorage::get_instance();
		}

		game::ISteamScreenshots* get_i_steam_screenshots(game::ISteamClient*, game::HSteamUser, game::HSteamPipe, const char* version)
		{
			return steam_screenshots::get_instance();
		}

		game::ISteamHTTP* get_i_steam_http(game::ISteamClient*, game::HSteamUser, game::HSteamPipe, const char* version)
		{
			return steam_http::get_instance();
		}

		game::ISteamUnifiedMessages* get_i_steam_unified_messages(game::ISteamClient*, game::HSteamUser, game::HSteamPipe, const char* version)
		{
			return steam_unifiedmessages::get_instance();
		}

		game::ISteamController* get_i_steam_controller(game::ISteamClient*, game::HSteamUser, game::HSteamPipe, const char* version)
		{
			return steam_controller::get_instance();
		}

		game::ISteamAppList* get_i_steam_app_list(game::ISteamClient*, game::HSteamUser, game::HSteamPipe, const char* version)
		{
			return steam_applist::get_instance();
		}

		game::ISteamUGC* get_i_steam_ugc(game::ISteamClient*, game::HSteamUser, game::HSteamPipe, const char* version)
		{
			return steam_ugc::get_instance();
		}

		game::ISteamMusic* get_i_steam_music(game::ISteamClient*, game::HSteamUser, game::HSteamPipe, const char* version)
		{
			return steam_music::get_instance();
		}

		game::ISteamMusicRemote* get_i_steam_music_remote(game::ISteamClient*, game::HSteamUser, game::HSteamPipe, const char* version)
		{
			return steam_musicremote::get_instance();
		}

		game::ISteamHTMLSurface* get_i_steam_html_surface(game::ISteamClient*, game::HSteamUser, game::HSteamPipe, const char* version)
		{
			return steam_htmlsurface::get_instance();
		}

		game::ISteamInventory* get_i_steam_inventory(game::ISteamClient*, game::HSteamUser, game::HSteamPipe, const char* version)
		{
			return steam_inventory::get_instance();
		}

		game::ISteamVideo* get_i_steam_video(game::ISteamClient*, game::HSteamUser, game::HSteamPipe, const char* version)
		{
			return steam_video::get_instance();
		}
	}

	game::ISteamClient* steam_client::create()
	{
		static game::ISteamClient instance{};
		static game::ISteamClient_vtbl vtable{};

		init_vtable(vtable);

		instance.__vftable = &vtable;
		instance.__vftable->GetISteamUser = get_i_steam_user;
		instance.__vftable->GetISteamFriends = get_i_steam_friends;
		instance.__vftable->GetISteamUtils = get_i_steam_utils;
		instance.__vftable->GetISteamMatchmaking = get_i_steam_matchmaking; // not used
		instance.__vftable->GetISteamMatchmakingServers = get_i_steam_matchmaking_servers; // not used
		instance.__vftable->GetISteamUserStats = get_i_steam_user_stats; 
		instance.__vftable->GetISteamApps = get_i_steam_apps;
		instance.__vftable->GetISteamNetworking = get_i_steam_networking;
		instance.__vftable->GetISteamRemoteStorage = get_i_steam_remote_storage; 
		instance.__vftable->GetISteamScreenshots = get_i_steam_screenshots; // not used
		instance.__vftable->GetISteamHTTP = get_i_steam_http; // not used
		instance.__vftable->GetISteamUnifiedMessages = get_i_steam_unified_messages; // not used
		instance.__vftable->GetISteamController = get_i_steam_controller; // not used
		instance.__vftable->GetISteamUGC = get_i_steam_ugc; // not used
		instance.__vftable->GetISteamAppList = get_i_steam_app_list; // not used
		instance.__vftable->GetISteamMusic = get_i_steam_music; // not used
		instance.__vftable->GetISteamMusicRemote = get_i_steam_music_remote; // not used
		instance.__vftable->GetISteamHTMLSurface = get_i_steam_html_surface; // not used
		instance.__vftable->GetISteamInventory = get_i_steam_inventory; // not used
		instance.__vftable->GetISteamVideo = get_i_steam_video; // not used

		return &instance;
	}

	game::ISteamClient* steam_client::get_instance()
	{
		static const auto instance = create();
		return instance;
	}
}
