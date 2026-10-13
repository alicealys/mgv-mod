#include <std_include.hpp>

#include "base.hpp"

#include "steam_userstats.hpp"

namespace steam
{
	namespace
	{
		bool request_current_stats(game::ISteamUserStats*)
		{
			return true;
		}

		bool set_achievement(game::ISteamUserStats*, const char* name)
		{
			return false;
		}

		bool get_achievement(game::ISteamUserStats*, const char* name, bool* achieved)
		{
			*achieved = false;
			return false;
		}

		const char* get_achievement_display_attribute(game::ISteamUserStats*, const char* name, const char*)
		{
			return "";
		}

		game::SteamAPICall_t find_leaderboard(game::ISteamUserStats*, const char*)
		{
			return {};
		}

		game::SteamAPICall_t attach_leaderboard_ugc(game::ISteamUserStats*, game::SteamLeaderboard_t, game::UGCHandle_t)
		{
			return {};
		}

		game::SteamAPICall_t upload_leaderboard_score(game::ISteamUserStats*, game::SteamLeaderboard_t hSteamLeaderboard, 
			game::ELeaderboardUploadScoreMethod eLeaderboardUploadScoreMethod, int nScore, const int* pScoreDetails, int cScoreDetailsCount)
		{
			return {};
		}

		bool store_stats(game::ISteamUserStats*)
		{
			return false;
		}
	}

	game::ISteamUserStats* steam_userstats::create()
	{
		static game::ISteamUserStats instance{};
		static game::ISteamUserStats_vtbl vtable{};

		init_vtable(vtable);

		instance.__vftable = &vtable;
		instance.__vftable->RequestCurrentStats = request_current_stats;
		instance.__vftable->SetAchievement = set_achievement;
		instance.__vftable->GetAchievement = get_achievement;
		instance.__vftable->GetAchievementDisplayAttribute = get_achievement_display_attribute;
		instance.__vftable->FindLeaderboard = find_leaderboard;
		instance.__vftable->AttachLeaderboardUGC = attach_leaderboard_ugc;
		instance.__vftable->UploadLeaderboardScore = upload_leaderboard_score;
		instance.__vftable->StoreStats = store_stats;

		return &instance;
	}

	game::ISteamUserStats* steam_userstats::get_instance()
	{
		static const auto instance = create();
		return instance;
	}
}
