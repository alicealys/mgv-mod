#include <std_include.hpp>

#include "base.hpp"

#include "steam_friends.hpp"

namespace steam
{
	namespace
	{
		void set_ingame_voice_speaking(game::ISteamFriends*, game::steam_id user, bool speaking)
		{

		}

		const char* get_persona_name(game::ISteamFriends*)
		{
			return "Unknown Soldier";
		}

		const char* get_friend_persona_name(game::ISteamFriends*, game::steam_id)
		{
			return "Unknown Soldier";
		}

		bool request_user_information(game::ISteamFriends*, game::steam_id, bool)
		{
			return false;
		}

		void clear_rich_presence(game::ISteamFriends*)
		{

		}

		bool set_rich_presence(game::ISteamFriends*, const char*, const char*)
		{
			return false;
		}

		bool invite_user_to_game(game::ISteamFriends*, game::steam_id, const char*)
		{
			return false;
		}


		bool get_friend_game_played(game::ISteamFriends*, game::steam_id steamIDFriend, game::FriendGameInfo_t* pFriendGameInfo)
		{
			return false;
		}

		const char* get_friend_rich_presence(game::ISteamFriends*, game::steam_id, const char*)
		{
			return "";
		}


		game::EPersonaState get_friend_persona_state(game::ISteamFriends*, game::steam_id)
		{
			return game::EPersonaState(0);
		}

		game::steam_id* get_friend_by_index(game::ISteamFriends*, game::steam_id* out, int, int)
		{
			out = {};
			return out;
		}

		int get_friend_count(game::ISteamFriends*, int)
		{
			return 0;
		}

		void active_game_overlay_to_user(game::ISteamFriends*, const char*, game::steam_id)
		{

		}
	}

	game::ISteamFriends* steam_friends::create()
	{
		static game::ISteamFriends instance{};
		static game::ISteamFriends_vtbl vtable{};

		init_vtable(vtable);

		instance.__vftable = &vtable;
		instance.__vftable->SetInGameVoiceSpeaking = set_ingame_voice_speaking;
		instance.__vftable->GetPersonaName = get_persona_name;
		instance.__vftable->GetFriendPersonaName = get_friend_persona_name;
		instance.__vftable->RequestUserInformation = request_user_information;
		instance.__vftable->ClearRichPresence = clear_rich_presence;
		instance.__vftable->SetRichPresence = set_rich_presence;
		instance.__vftable->InviteUserToGame = invite_user_to_game;
		instance.__vftable->GetFriendGamePlayed = get_friend_game_played;
		instance.__vftable->GetFriendRichPresence = get_friend_rich_presence;
		instance.__vftable->GetFriendPersonaState = get_friend_persona_state;
		instance.__vftable->GetFriendByIndex = get_friend_by_index;
		instance.__vftable->GetFriendCount = get_friend_count;
		instance.__vftable->ActivateGameOverlayToUser = active_game_overlay_to_user;

		return &instance;
	}

	game::ISteamFriends* steam_friends::get_instance()
	{
		static const auto instance = create();
		return instance;
	}
}
