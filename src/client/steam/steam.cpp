#include <std_include.hpp>

#include "game/game.hpp"
#include "steam.hpp"

#include "interfaces/steam_client.hpp"
#include "interfaces/steam_user.hpp"
#include "interfaces/steam_friends.hpp"
#include "interfaces/steam_utils.hpp"
#include "interfaces/steam_matchmaking.hpp"
#include "interfaces/steam_matchmakingservers.hpp"
#include "interfaces/steam_userstats.hpp"
#include "interfaces/steam_apps.hpp"
#include "interfaces/steam_networking.hpp"
#include "interfaces/steam_remotestorage.hpp"
#include "interfaces/steam_screenshots.hpp"
#include "interfaces/steam_http.hpp"
#include "interfaces/steam_unifiedmessages.hpp"
#include "interfaces/steam_controller.hpp"
#include "interfaces/steam_ugc.hpp"
#include "interfaces/steam_applist.hpp"
#include "interfaces/steam_music.hpp"
#include "interfaces/steam_musicremote.hpp"
#include "interfaces/steam_htmlsurface.hpp"
#include "interfaces/steam_inventory.hpp"
#include "interfaces/steam_video.hpp"

#include <utils/hook.hpp>

namespace steam
{
	namespace
	{
		using interface_creator_t = void*(*)();
		std::unordered_map<std::string, interface_creator_t> interface_creators;

		template <typename F>
		void register_interface(const std::string& name, F&& fn)
		{
			static auto callback = fn;
			interface_creators.insert(std::make_pair(name, []()
			{
				return reinterpret_cast<void*>(callback());
			}));
		}

		void steamapi_register_callback()
		{

		}

		void steamapi_unregister_callback()
		{

		}

		void steamapi_run_callbacks()
		{

		}

		void steamapi_register_call_result(void* callback, int type)
		{

		}

		void steamapi_unregister_callresult(void* callback, int type)
		{

		}

		void* steaminternal_create_interface(const char* name)
		{
			const auto iter = interface_creators.find(name);
			if (iter == interface_creators.end())
			{
				return nullptr;
			}

			return iter->second();
		}

		unsigned int steamapi_get_h_user()
		{
			return 1u;
		}

		unsigned int steamapi_get_h_pipe()
		{
			return 1u;
		}

		int steamapi_init()
		{
			register_interface("SteamClient017", steam_client::create);
			register_interface("SteamUser019", steam_user::create);
			register_interface("SteamFriends015", steam_friends::create);
			register_interface("SteamUtils008", steam_utils::create);
			register_interface("SteamMatchMaking009", steam_matchmaking::create);
			register_interface("SteamMatchMakingServers002", steam_matchmakingservers::create);
			register_interface("STEAMUSERSTATS_INTERFACE_VERSION011", steam_userstats::create);
			register_interface("STEAMAPPS_INTERFACE_VERSION008", steam_apps::create);
			register_interface("SteamNetworking005", steam_networking::create);
			register_interface("STEAMREMOTESTORAGE_INTERFACE_VERSION013", steam_remotestorage::create);
			register_interface("STEAMSCREENSHOTS_INTERFACE_VERSION002", steam_screenshots::create);
			register_interface("STEAMHTTP_INTERFACE_VERSION002", steam_http::create);
			register_interface("STEAMUNIFIEDMESSAGES_INTERFACE_VERSION001", steam_unifiedmessages::create);
			register_interface("SteamController003", steam_controller::create);
			register_interface("STEAMUGC_INTERFACE_VERSION008", steam_ugc::create);
			register_interface("STEAMAPPLIST_INTERFACE_VERSION001", steam_applist::create);
			register_interface("STEAMMUSIC_INTERFACE_VERSION001", steam_music::create);
			register_interface("STEAMMUSICREMOTE_INTERFACE_VERSION001", steam_musicremote::create);
			register_interface("STEAMHTMLSURFACE_INTERFACE_VERSION_003", steam_htmlsurface::create);
			register_interface("STEAMINVENTORY_INTERFACE_V001", steam_inventory::create);
			register_interface("STEAMVIDEO_INTERFACE_V001", steam_video::create);

			return 1;
		}
	}

	void disable_steam()
	{
		utils::hook::set(0x141FEB250_r, steamapi_register_callback);
		utils::hook::set(0x141FEB258_r, steamapi_unregister_callback);
		utils::hook::set(0x141FEB260_r, steamapi_run_callbacks);
		utils::hook::set(0x141FEB268_r, steamapi_register_call_result);
		utils::hook::set(0x141FEB270_r, steaminternal_create_interface);
		utils::hook::set(0x141FEB278_r, steamapi_get_h_user);
		utils::hook::set(0x141FEB280_r, steamapi_get_h_pipe);
		utils::hook::set(0x141FEB288_r, steamapi_init);
		utils::hook::set(0x141FEB290_r, steamapi_unregister_callresult);
	}
}
