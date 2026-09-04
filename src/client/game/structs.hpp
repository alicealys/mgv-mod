#pragma once
#include <d3d11.h>
#include <d3d11_1.h>

namespace game
{
	// https://github.com/rlabrecque/SteamworksSDK/tree/f4d127e335a66a1615c0870830d14dcee76ed8aa/public/steam

	struct raw_steam_id final
	{
		unsigned int account_id : 32;
		unsigned int account_instance : 20;
		unsigned int account_type : 4;
		int universe : 8;
	};

	typedef union
	{
		raw_steam_id raw;
		unsigned long long bits;
	} steam_id;

	struct ISteamUser;

	enum { k_iSteamUserCallbacks = 100 };
	enum { k_iSteamGameServerCallbacks = 200 };
	enum { k_iSteamFriendsCallbacks = 300 };
	enum { k_iSteamBillingCallbacks = 400 };
	enum { k_iSteamMatchmakingCallbacks = 500 };
	enum { k_iSteamContentServerCallbacks = 600 };
	enum { k_iSteamUtilsCallbacks = 700 };
	enum { k_iSteamAppsCallbacks = 1000 };
	enum { k_iSteamUserStatsCallbacks = 1100 };
	enum { k_iSteamNetworkingCallbacks = 1200 };
	enum { k_iSteamNetworkingSocketsCallbacks = 1220 };
	enum { k_iSteamNetworkingMessagesCallbacks = 1250 };
	enum { k_iSteamNetworkingUtilsCallbacks = 1280 };
	enum { k_iSteamRemoteStorageCallbacks = 1300 };
	enum { k_iSteamGameServerItemsCallbacks = 1500 };
	enum { k_iSteamGameCoordinatorCallbacks = 1700 };
	enum { k_iSteamGameServerStatsCallbacks = 1800 };
	enum { k_iSteam2AsyncCallbacks = 1900 };
	enum { k_iSteamGameStatsCallbacks = 2000 };
	enum { k_iSteamHTTPCallbacks = 2100 };
	enum { k_iSteamScreenshotsCallbacks = 2300 };
	enum { k_iSteamStreamLauncherCallbacks = 2600 };
	enum { k_iSteamControllerCallbacks = 2800 };
	enum { k_iSteamUGCCallbacks = 3400 };
	enum { k_iSteamStreamClientCallbacks = 3500 };
	enum { k_iSteamMusicCallbacks = 4000 };
	enum { k_iSteamGameNotificationCallbacks = 4400 };
	enum { k_iSteamHTMLSurfaceCallbacks = 4500 };
	enum { k_iSteamVideoCallbacks = 4600 };
	enum { k_iSteamInventoryCallbacks = 4700 };
	enum { k_ISteamParentalSettingsCallbacks = 5000 };
	enum { k_iSteamGameSearchCallbacks = 5200 };
	enum { k_iSteamPartiesCallbacks = 5300 };
	enum { k_iSteamSTARCallbacks = 5500 };
	enum { k_iSteamRemotePlayCallbacks = 5700 };
	enum { k_iSteamChatCallbacks = 5900 };
	enum { k_iSteamTimelineCallbacks = 6000 };

	typedef unsigned __int64 SteamAPICall_t;
	typedef unsigned __int8 uint8;
	typedef unsigned __int16 uint16;
	typedef unsigned __int32 uint32;
	typedef unsigned __int64 uint64;

	struct LobbyDataUpdate_t
	{
		enum { k_iCallback = k_iSteamMatchmakingCallbacks + 5 };

		uint64 m_ulSteamIDLobby;		// steamID of the Lobby
		uint64 m_ulSteamIDMember;		// steamID of the member whose data changed, or the room itself
		uint8 m_bSuccess;				// true if we lobby data was successfully changed; 
		// will only be false if RequestLobbyData() was called on a lobby that no longer exists
	};

	struct LobbyMatchList_t
	{
		enum { k_iCallback = k_iSteamMatchmakingCallbacks + 10 };
		unsigned int num_lobbies;		// Number of lobbies that matched search criteria and we have SteamIDs for
	};

	class CCallbackBase
	{
	public:
		CCallbackBase() { m_nCallbackFlags = 0; m_iCallback = 0; }
		// don't add a virtual destructor because we export this binary interface across dll's
		virtual void Run(void* pvParam) = 0;
		virtual void Run(void* pvParam, bool bIOFailure, SteamAPICall_t hSteamAPICall) = 0;
		int GetICallback() { return m_iCallback; }
		virtual int GetCallbackSizeBytes() = 0;

	protected:
		enum { k_ECallbackFlagsRegistered = 0x01, k_ECallbackFlagsGameServer = 0x02 };
		uint8 m_nCallbackFlags;
		int m_iCallback;
		friend class CCallbackMgr;

	private:
		CCallbackBase(const CCallbackBase&);
		CCallbackBase& operator=(const CCallbackBase&);
	};

	struct LobbyEnter_t
	{
		enum { k_iCallback = k_iSteamMatchmakingCallbacks + 4 };

		steam_id lobby_id;
		int permissions;
		bool locked;
		int chatroom;
	};

	struct P2PSessionRequest_t
	{
		steam_id remote;
	};

	struct ISteamClient;
	struct ISteamUser;
	struct ISteamGameServer;
	struct ISteamFriends;
	struct ISteamUtils;
	struct ISteamMatchmaking;
	struct ISteamMatchmakingServers;
	struct ISteamUserStats;
	struct ISteamGameServerStats;
	struct ISteamApps;
	struct ISteamNetworking;
	struct ISteamRemoteStorage;
	struct ISteamScreenshots;
	struct ISteamHTTP;
	struct ISteamUnifiedMessages;
	struct ISteamController;
	struct ISteamUGC;
	struct ISteamAppList;
	struct ISteamMusic;
	struct ISteamMusicRemote;

	struct ISteamClient_vtbl
	{
		int(__fastcall* CreateSteamPipe)(ISteamClient*);
		bool(__fastcall* BReleaseSteamPipe)(ISteamClient*, int hSteamPipe);
		int(__fastcall* ConnectToGlobalUser)(ISteamClient*, int hSteamPipe);
		int(__fastcall* CreateLocalUser)(ISteamClient*, int* phSteamPipe, int eAccountType);
		void(__fastcall* ReleaseUser)(ISteamClient*, int hSteamPipe, int hUser);
		ISteamUser* (__fastcall* GetISteamUser)(ISteamClient*, int hSteamUser, int hSteamPipe, const char* pchVersion);
		ISteamGameServer* (__fastcall* GetISteamGameServer)(ISteamClient*, int hSteamUser, int hSteamPipe, const char* pchVersion);
		void(__fastcall* SetLocalIPBinding)(ISteamClient*, unsigned int unIP, unsigned short usPort);
		ISteamFriends* (__fastcall* GetISteamFriends)(ISteamClient*, int hSteamUser, int hSteamPipe, const char* pchVersion);
		ISteamUtils* (__fastcall* GetISteamUtils)(ISteamClient*, int hSteamPipe, const char* pchVersion);
		ISteamMatchmaking* (__fastcall* GetISteamMatchmaking)(ISteamClient*, int hSteamUser, int hSteamPipe, const char* pchVersion);
		ISteamMatchmakingServers* (__fastcall* GetISteamMatchmakingServers)(ISteamClient*, int hSteamUser, int hSteamPipe, const char* pchVersion);
		void* (__fastcall* GetISteamGenericInterface)(ISteamClient*, int hSteamUser, int hSteamPipe, const char* pchVersion);
		ISteamUserStats* (__fastcall* GetISteamUserStats)(ISteamClient*, int hSteamUser, int hSteamPipe, const char* pchVersion);
		ISteamGameServerStats* (__fastcall* GetISteamGameServerStats)(ISteamClient*, int hSteamuser, int hSteamPipe, const char* pchVersion);
		ISteamApps* (__fastcall* GetISteamApps)(ISteamClient*, int hSteamUser, int hSteamPipe, const char* pchVersion);
		ISteamNetworking* (__fastcall* GetISteamNetworking)(ISteamClient*, int hSteamUser, int hSteamPipe, const char* pchVersion);
		ISteamRemoteStorage* (__fastcall* GetISteamRemoteStorage)(ISteamClient*, int hSteamuser, int hSteamPipe, const char* pchVersion);
		ISteamScreenshots* (__fastcall* GetISteamScreenshots)(ISteamClient*, int hSteamuser, int hSteamPipe, const char* pchVersion);
		void(__fastcall* RunFrame)(ISteamClient*);
		unsigned int(__fastcall* GetIPCCallCount)(ISteamClient*);
		void(__fastcall* SetWarningMessageHook)(ISteamClient*, void* pFunction);
		bool(__fastcall* BShutdownIfAllPipesClosed)(ISteamClient*);
		ISteamHTTP* (__fastcall* GetISteamHTTP)(ISteamClient*, int hSteamuser, int hSteamPipe, const char* pchVersion);
		ISteamUnifiedMessages* (__fastcall* GetISteamUnifiedMessages)(ISteamClient*, int hSteamuser, int hSteamPipe, const char* pchVersion);
		ISteamController* (__fastcall* GetISteamController)(ISteamClient*, int hSteamUser, int hSteamPipe, const char* pchVersion);
		ISteamUGC* (__fastcall* GetISteamUGC)(ISteamClient*, int hSteamUser, int hSteamPipe, const char* pchVersion);
		ISteamAppList* (__fastcall* GetISteamAppList)(ISteamClient*, int hSteamUser, int hSteamPipe, const char* pchVersion);
		ISteamMusic* (__fastcall* GetISteamMusic)(ISteamClient*, int hSteamuser, int hSteamPipe, const char* pchVersion);
		ISteamMusicRemote* (__fastcall* GetISteamMusicRemote)(ISteamClient*, int hSteamuser, int hSteamPipe, const char* pchVersion);
	};

	struct ISteamClient
	{
		ISteamClient_vtbl* __vftable;
	};

	struct /*VFT*/ ISteamUser_vtbl
	{
		int(__fastcall* GetHSteamUser)(ISteamUser* this_);
		bool(__fastcall* LoggedOn)(ISteamUser* this_);
		__int64(__fastcall* GetSteamID)(ISteamUser* this_, steam_id* steamIDUser);
		int(__fastcall* InitiateGameConnection)(ISteamUser* this_, void* pAuthBlob, int cbMaxAuthBlob, steam_id steamIDGameServer, unsigned int unIPServer, unsigned __int16 usPortServer, bool bSecure);
		void(__fastcall* TerminateGameConnection)(ISteamUser* this_, unsigned int unIPServer, unsigned __int16 usPortServer);
		void(__fastcall* TrackAppUsageEvent)(ISteamUser* this_, steam_id gameID, int eAppUsageEvent, const char* pchExtraInfo);
		bool(__fastcall* GetUserDataFolder)(ISteamUser* this_, char* pchBuffer, int cubBuffer);
		void(__fastcall* StartVoiceRecording)(ISteamUser* this_);
		void(__fastcall* StopVoiceRecording)(ISteamUser* this_);
		int(__fastcall* GetAvailableVoice)(ISteamUser* this_, unsigned int* pcbCompressed, unsigned int* pcbUncompressed, unsigned int nUncompressedVoiceDesiredSampleRate);
		int(__fastcall* GetVoice)(ISteamUser* this_, bool bWantCompressed, void* pDestBuffer, unsigned int cbDestBufferSize, unsigned int* nBytesWritten, bool bWantUncompressed, void* pUncompressedDestBuffer, unsigned int cbUncompressedDestBufferSize, unsigned int* nUncompressBytesWritten, unsigned int nUncompressedVoiceDesiredSampleRate);
		int(__fastcall* DecompressVoice)(ISteamUser* this_, void* pCompressed, unsigned int cbCompressed, void* pDestBuffer, unsigned int cbDestBufferSize, unsigned int* nBytesWritten);
		unsigned int(__fastcall* GetVoiceOptimalSampleRate)(ISteamUser* this_);
		unsigned int(__fastcall* GetAuthSessionTicket)(ISteamUser* this_, void* pTicket, int cbMaxTicket, unsigned int* pcbTicket);
		int(__fastcall* BeginAuthSession)(ISteamUser* this_, const void* pAuthTicket, int cbAuthTicket, steam_id steamID);
		void(__fastcall* EndAuthSession)(ISteamUser* this_, steam_id steamID);
		void(__fastcall* CancelAuthTicket)(ISteamUser* this_, unsigned int hAuthTicket);
		unsigned int(__fastcall* UserHasLicenseForApp)(ISteamUser* this_, steam_id steamID, unsigned int appID);
		bool(__fastcall* BIsBehindNAT)(ISteamUser* this_);
		void(__fastcall* AdvertiseGame)(ISteamUser* this_, steam_id steamIDGameServer, unsigned int unIPServer, unsigned __int16 usPortServer);
		unsigned __int64(__fastcall* RequestEncryptedAppTicket)(ISteamUser* this_, void* pUserData, int cbUserData);
		bool(__fastcall* GetEncryptedAppTicket)(ISteamUser* this_, void* pTicket, int cbMaxTicket, unsigned int* pcbTicket);
	};

	struct ISteamUser
	{
		ISteamUser_vtbl* __vftable /*VFT*/;
	};

	struct ISteamNetworking;

	struct /*VFT*/ ISteamNetworking_vtbl
	{
		bool(__fastcall* SendP2PPacket)(ISteamNetworking* this_, steam_id steamIDRemote, const void* pubData, unsigned int cubData, int eP2PSendType, int nChannel);
		bool(__fastcall* IsP2PPacketAvailable)(ISteamNetworking* this_, unsigned int* pcubMsgSize, int nChannel);
		bool(__fastcall* ReadP2PPacket)(ISteamNetworking* this_, void* pubDest, unsigned int cubDest, unsigned int* pcubMsgSize, steam_id* psteamIDRemote, int nChannel);
		bool(__fastcall* AcceptP2PSessionWithUser)(ISteamNetworking* this_, steam_id steamIDRemote);
		bool(__fastcall* CloseP2PSessionWithUser)(ISteamNetworking* this_, steam_id steamIDRemote);
		bool(__fastcall* CloseP2PChannelWithUser)(ISteamNetworking* this_, steam_id steamIDRemote, int iVirtualPort);
		bool(__fastcall* GetP2PSessionState)(ISteamNetworking* this_, steam_id steamIDRemote, void* pConnectionState);
		bool(__fastcall* AllowP2PPacketRelay)(ISteamNetworking* this_, bool bAllow);
		unsigned int(__fastcall* CreateListenSocket)(ISteamNetworking* this_, int nVirtualP2PPort, unsigned int nIP, unsigned __int16 nPort, bool bAllowUseOfPacketRelay);
		unsigned int(__fastcall* CreateP2PConnectionSocket)(ISteamNetworking* this_, steam_id steamIDTarget, int nVirtualPort, int nTimeoutSec, bool bAllowUseOfPacketRelay);
		unsigned int(__fastcall* CreateConnectionSocket)(ISteamNetworking* this_, unsigned int nIP, unsigned __int16 nPort, int nTimeoutSec);
		bool(__fastcall* DestroySocket)(ISteamNetworking* this_, unsigned int hSocket, bool bNotifyRemoteEnd);
		bool(__fastcall* DestroyListenSocket)(ISteamNetworking* this_, unsigned int hSocket, bool bNotifyRemoteEnd);
		bool(__fastcall* SendDataOnSocket)(ISteamNetworking* this_, unsigned int hSocket, void* pubData, unsigned int cubData, bool bReliable);
		bool(__fastcall* IsDataAvailableOnSocket)(ISteamNetworking* this_, unsigned int hSocket, unsigned int* pcubMsgSize);
		bool(__fastcall* RetrieveDataFromSocket)(ISteamNetworking* this_, unsigned int hSocket, void* pubDest, unsigned int cubDest, unsigned int* pcubMsgSize);
		bool(__fastcall* IsDataAvailable)(ISteamNetworking* this_, unsigned int hListenSocket, unsigned int* pcubMsgSize, unsigned int* phSocket);
		bool(__fastcall* RetrieveData)(ISteamNetworking* this_, unsigned int hListenSocket, void* pubDest, unsigned int cubDest, unsigned int* pcubMsgSize, unsigned int* phSocket);
		bool(__fastcall* GetSocketInfo)(ISteamNetworking* this_, unsigned int hSocket, steam_id* pSteamIDRemote, int* peSocketStatus, unsigned int* punIPRemote, unsigned __int16* punPortRemote);
		bool(__fastcall* GetListenSocketInfo)(ISteamNetworking* this_, unsigned int hListenSocket, unsigned int* pnIP, unsigned __int16* pnPort);
		int(__fastcall* GetSocketConnectionType)(ISteamNetworking* this_, unsigned int hSocket);
		int(__fastcall* GetMaxPacketSize)(ISteamNetworking* this_, unsigned int hSocket);
	};

	struct ISteamNetworking
	{
		ISteamNetworking_vtbl* __vftable /*VFT*/;
	};

	struct ISteamFriends;

	typedef std::int16_t FriendsGroupID_t;

	struct /*VFT*/ ISteamFriends_vtbl
	{
		const char* (__fastcall* GetPersonaName)(ISteamFriends* this_);
		unsigned __int64(__fastcall* SetPersonaName)(ISteamFriends* this_, const char* pchPersonaName);
		int(__fastcall* GetPersonaState)(ISteamFriends* this_);
		int(__fastcall* GetFriendCount)(ISteamFriends* this_, int eFriendFlags);
		void(__fastcall* GetFriendByIndex)(ISteamFriends* this_, steam_id* out, int iFriend, int iFriendFlags);
		int(__fastcall* GetFriendRelationship)(ISteamFriends* this_, steam_id steamIDFriend);
		int(__fastcall* GetFriendPersonaState)(ISteamFriends* this_, steam_id steamIDFriend);
		const char* (__fastcall* GetFriendPersonaName)(ISteamFriends* this_, steam_id steamIDFriend);
		bool(__fastcall* GetFriendGamePlayed)(ISteamFriends* this_, steam_id steamIDFriend, void* pFriendGameInfo);
		const char* (__fastcall* GetFriendPersonaNameHistory)(ISteamFriends* this_, steam_id steamIDFriend, int iPersonaName);
		int(__fastcall* GetFriendSteamLevel)(ISteamFriends* this_, steam_id steamIDFriend);
		const char* (__fastcall* GetPlayerNickname)(ISteamFriends* this_, steam_id steamIDFriend);
		int(__fastcall* GetFriendsGroupCount)(ISteamFriends* this_);
		FriendsGroupID_t(__fastcall* GetFriendsGroupIDByIndex)(ISteamFriends* this_, int iFG);
		const char* (__fastcall* GetFriendsGroupName)(ISteamFriends* this_, FriendsGroupID_t friendsGroupID);
		int(__fastcall* GetFriendsGroupMembersCount)(ISteamFriends* this_, FriendsGroupID_t friendsGroupID);
		void(__fastcall* GetFriendsGroupMembersList)(ISteamFriends* this_, FriendsGroupID_t friendsGroupID, steam_id* pOutSteamIDMembers, int nMembersCount);
		bool(__fastcall* HasFriend)(ISteamFriends* this_, steam_id steamIDFriend, int eFriendFlags);
		int(__fastcall* GetClanCount)(ISteamFriends* this_);
		steam_id(__fastcall* GetClanByIndex)(ISteamFriends* this_, int iClan);
		const char* (__fastcall* GetClanName)(ISteamFriends* this_, steam_id steamIDClan);
		const char* (__fastcall* GetClanTag)(ISteamFriends* this_, steam_id steamIDClan);
		bool(__fastcall* GetClanActivityCounts)(ISteamFriends* this_, steam_id steamID, int* pnOnline, int* pnInGame, int* pnChatting);
		unsigned __int64(__fastcall* DownloadClanActivityCounts)(ISteamFriends* this_, steam_id groupIDs[], int nIds);
		int(__fastcall* GetFriendCountFromSource)(ISteamFriends* this_, steam_id steamIDSource);
		steam_id(__fastcall* GetFriendFromSourceByIndex)(ISteamFriends* this_, steam_id steamIDSource, int iFriend);
		bool(__fastcall* IsUserInSource)(ISteamFriends* this_, steam_id steamIDUser, steam_id steamIDSource);
		void(__fastcall* SetInGameVoiceSpeaking)(ISteamFriends* this_, steam_id steamIDUser, bool bSpeaking);
		void(__fastcall* ActivateGameOverlay)(ISteamFriends* this_, const char* pchDialog);
		void(__fastcall* ActivateGameOverlayToUser)(ISteamFriends* this_, const char* pchDialog, steam_id steamID);
		void(__fastcall* ActivateGameOverlayToWebPage)(ISteamFriends* this_, const char* pchURL);
		void(__fastcall* ActivateGameOverlayToStore)(ISteamFriends* this_, unsigned int nAppID, unsigned int eFlag);
		void(__fastcall* SetPlayedWith)(ISteamFriends* this_, steam_id steamIDUserPlayedWith);
		void(__fastcall* ActivateGameOverlayInviteDialog)(ISteamFriends* this_, steam_id steamIDLobby);
		int(__fastcall* GetSmallFriendAvatar)(ISteamFriends* this_, steam_id steamIDFriend);
		int(__fastcall* GetMediumFriendAvatar)(ISteamFriends* this_, steam_id steamIDFriend);
		int(__fastcall* GetLargeFriendAvatar)(ISteamFriends* this_, steam_id steamIDFriend);
		bool(__fastcall* RequestUserInformation)(ISteamFriends* this_, steam_id steamIDUser, bool bRequireNameOnly);
		unsigned __int64(__fastcall* RequestClanOfficerList)(ISteamFriends* this_, steam_id steamIDClan);
		steam_id(__fastcall* GetClanOwner)(ISteamFriends* this_, steam_id steamIDClan);
		int(__fastcall* GetClanOfficerCount)(ISteamFriends* this_, steam_id steamIDClan);
		steam_id(__fastcall* GetClanOfficerByIndex)(ISteamFriends* this_, steam_id steamIDClan, int iOfficer);
		int(__fastcall* GetUserRestrictions)(ISteamFriends* this_);
		bool(__fastcall* SetRichPresence)(ISteamFriends* this_, const char* pchKey, const char* pchValue);
		void(__fastcall* ClearRichPresence)(ISteamFriends* this_);
		const char* (__fastcall* GetFriendRichPresence)(ISteamFriends* this_, steam_id steamIDFriend, const char* pchKey);
		int(__fastcall* GetFriendRichPresenceKeyCount)(ISteamFriends* this_, steam_id steamIDFriend);
		const char* (__fastcall* GetFriendRichPresenceKeyByIndex)(ISteamFriends* this_, steam_id steamIDFriend, int iKey);
		void(__fastcall* RequestFriendRichPresence)(ISteamFriends* this_, steam_id steamIDFriend);
		bool(__fastcall* InviteUserToGame)(ISteamFriends* this_, steam_id steamIDFriend, const char* pchConnectString);
		int(__fastcall* GetCoplayFriendCount)(ISteamFriends* this_);
		steam_id(__fastcall* GetCoplayFriend)(ISteamFriends* this_, int iCoplayFriend);
		int(__fastcall* GetFriendCoplayTime)(ISteamFriends* this_, steam_id steamIDFriend);
		unsigned int(__fastcall* GetFriendCoplayGame)(ISteamFriends* this_, steam_id steamIDFriend);
		unsigned __int64(__fastcall* JoinClanChatRoom)(ISteamFriends* this_, steam_id steamIDClan);
		bool(__fastcall* LeaveClanChatRoom)(ISteamFriends* this_, steam_id steamIDClan);
		int(__fastcall* GetClanChatMemberCount)(ISteamFriends* this_, steam_id steamIDClan);
		steam_id(__fastcall* GetChatMemberByIndex)(ISteamFriends* this_, steam_id steamIDClan, int iUser);
		bool(__fastcall* SendClanChatMessage)(ISteamFriends* this_, steam_id steamIDClanChat, const char* pchText);
		int(__fastcall* GetClanChatMessage)(ISteamFriends* this_, steam_id steamIDClanChat, int iMessage, void* prgchText, int cchTextMax, unsigned int* peChatEntryType, steam_id* pSteamIDChatter);
		bool(__fastcall* IsClanChatAdmin)(ISteamFriends* this_, steam_id steamIDClanChat, steam_id steamIDUser);
		bool(__fastcall* IsClanChatWindowOpenInSteam)(ISteamFriends* this_, steam_id steamIDClanChat);
		bool(__fastcall* OpenClanChatWindowInSteam)(ISteamFriends* this_, steam_id steamIDClanChat);
		bool(__fastcall* CloseClanChatWindowInSteam)(ISteamFriends* this_, steam_id steamIDClanChat);
		bool(__fastcall* SetListenForFriendsMessages)(ISteamFriends* this_, bool bInterceptEnabled);
		bool(__fastcall* ReplyToFriendMessage)(ISteamFriends* this_, steam_id steamIDFriend, const char* pchMsgToSend);
		int(__fastcall* GetFriendMessage)(ISteamFriends* this_, steam_id steamIDFriend, int iMessageID, void* pvData, int cubData, unsigned int* peChatEntryType);
		unsigned __int64(__fastcall* GetFollowerCount)(ISteamFriends* this_, steam_id steamID);
		unsigned __int64(__fastcall* IsFollowing)(ISteamFriends* this_, steam_id steamID);
		unsigned __int64(__fastcall* EnumerateFollowingList)(ISteamFriends* this_, unsigned int unStartIndex);
	};

	struct ISteamFriends
	{
		ISteamFriends_vtbl* __vftable /*VFT*/;
	};

	struct ISteamApps;

	struct ISteamApps_vtbl
	{
		bool(__fastcall* BIsSubscribed)(ISteamApps*);
		bool(__fastcall* BIsLowViolence)(ISteamApps*);
		bool(__fastcall* BIsCybercafe)(ISteamApps*);
		bool(__fastcall* BIsVACBanned)(ISteamApps*);
		const char* (__fastcall* GetCurrentGameLanguage)(ISteamApps*);
		const char* (__fastcall* GetAvailableGameLanguages)(ISteamApps*);
		bool(__fastcall* BIsSubscribedApp)(ISteamApps*, unsigned int appID);
		bool(__fastcall* BIsDlcInstalled)(ISteamApps*, unsigned int appID);
		unsigned int(__fastcall* GetEarliestPurchaseUnixTime)(ISteamApps*, unsigned int nAppID);
		bool(__fastcall* BIsSubscribedFromFreeWeekend)(ISteamApps*);
		int(__fastcall* GetDLCCount)(ISteamApps*);
		bool(__fastcall* BGetDLCDataByIndex)(ISteamApps*, int iDLC, unsigned int* pAppID, bool* pbAvailable, char* pchName, int cchNameBufferSize);
		void(__fastcall* InstallDLC)(ISteamApps*, unsigned int nAppID);
		void(__fastcall* UninstallDLC)(ISteamApps*, unsigned int nAppID);
		void(__fastcall* RequestAppProofOfPurchaseKey)(ISteamApps*, unsigned int nAppID);
		bool(__fastcall* GetCurrentBetaName)(ISteamApps*, char* pchName, int cchNameBufferSize);
		bool(__fastcall* MarkContentCorrupt)(ISteamApps*, bool bMissingFilesOnly);
		unsigned int(__fastcall* GetInstalledDepots)(ISteamApps*, unsigned int appID, unsigned int* pvecDepots, unsigned int cMaxDepots);
		unsigned int(__fastcall* GetAppInstallDir)(ISteamApps*, unsigned int appID, char* pchFolder, unsigned int cchFolderBufferSize);
		bool(__fastcall* BIsAppInstalled)(ISteamApps*, unsigned int appID);
		steam_id(__fastcall* GetAppOwner)(ISteamApps*);
		const char* (__fastcall* GetLaunchQueryParam)(ISteamApps*, const char* pchKey);
	};

	struct ISteamApps
	{
		ISteamApps_vtbl* __vftable;
	};

	struct LobbyCreated_t
	{
		enum { k_iCallback = k_iSteamMatchmakingCallbacks + 13 };
		int result;
		steam_id lobby_id;
	};

	struct LobbyChatMsg_t
	{
		steam_id lobby_id;
		steam_id user_id;
		std::uint8_t chat_entry_type;
		std::uint32_t chat_id;
	};

	static_assert(offsetof(LobbyChatMsg_t, chat_id) == 20);

	struct ISteamMatchmaking;

	struct /*VFT*/ ISteamMatchmaking_vtbl
	{
		int(__fastcall* GetFavoriteGameCount)(ISteamMatchmaking* this_);
		bool(__fastcall* GetFavoriteGame)(ISteamMatchmaking* this_, int iGame, unsigned int* pnAppID, unsigned int* pnIP, unsigned __int16* pnConnPort, unsigned __int16* pnQueryPort, unsigned int* punFlags, unsigned int* pRTime32LastPlayedOnServer);
		int(__fastcall* AddFavoriteGame)(ISteamMatchmaking* this_, unsigned int nAppID, unsigned int nIP, unsigned __int16 nConnPort, unsigned __int16 nQueryPort, unsigned int unFlags, unsigned int rTime32LastPlayedOnServer);
		bool(__fastcall* RemoveFavoriteGame)(ISteamMatchmaking* this_, unsigned int nAppID, unsigned int nIP, unsigned __int16 nConnPort, unsigned __int16 nQueryPort, unsigned int unFlags);
		unsigned __int64(__fastcall* RequestLobbyList)(ISteamMatchmaking* this_);
		void(__fastcall* AddRequestLobbyListStringFilter)(ISteamMatchmaking* this_, const char* pchKeyToMatch, const char* pchValueToMatch, int eComparisonType);
		void(__fastcall* AddRequestLobbyListNumericalFilter)(ISteamMatchmaking* this_, const char* pchKeyToMatch, int nValueToMatch, int eComparisonType);
		void(__fastcall* AddRequestLobbyListNearValueFilter)(ISteamMatchmaking* this_, const char* pchKeyToMatch, int nValueToBeCloseTo);
		void(__fastcall* AddRequestLobbyListFilterSlotsAvailable)(ISteamMatchmaking* this_, int nSlotsAvailable);
		void(__fastcall* AddRequestLobbyListDistanceFilter)(ISteamMatchmaking* this_, int eLobbyDistanceFilter);
		void(__fastcall* AddRequestLobbyListResultCountFilter)(ISteamMatchmaking* this_, int cMaxResults);
		void(__fastcall* AddRequestLobbyListCompatibleMembersFilter)(ISteamMatchmaking* this_, steam_id steamID);
		steam_id*(__fastcall* GetLobbyByIndex)(ISteamMatchmaking* this_, steam_id* lobby_id, int iLobby);
		unsigned __int64(__fastcall* CreateLobby)(ISteamMatchmaking* this_, int eLobbyType, int cMaxMembers);
		unsigned __int64(__fastcall* JoinLobby)(ISteamMatchmaking* this_, steam_id steamIDLobby);
		void(__fastcall* LeaveLobby)(ISteamMatchmaking* this_, steam_id steamIDLobby);
		bool(__fastcall* InviteUserToLobby)(ISteamMatchmaking* this_, steam_id steamIDLobby, steam_id steamIDInvitee);
		int(__fastcall* GetNumLobbyMembers)(ISteamMatchmaking* this_, steam_id steamIDLobby);
		void(__fastcall* GetLobbyMemberByIndex)(ISteamMatchmaking* this_, steam_id* steamIDUser, steam_id steamIDLobby, int iMember);
		const char* (__fastcall* GetLobbyData)(ISteamMatchmaking* this_, steam_id steamIDLobby, const char* pchKey);
		bool(__fastcall* SetLobbyData)(ISteamMatchmaking* this_, steam_id steamIDLobby, const char* pchKey, const char* pchValue);
		int(__fastcall* GetLobbyDataCount)(ISteamMatchmaking* this_, steam_id steamIDLobby);
		bool(__fastcall* GetLobbyDataByIndex)(ISteamMatchmaking* this_, steam_id steamIDLobby, int iLobbyData, char* pchKey, int cchKeyBufferSize, char* pchValue, int cchValueBufferSize);
		bool(__fastcall* DeleteLobbyData)(ISteamMatchmaking* this_, steam_id steamIDLobby, const char* pchKey);
		const char* (__fastcall* GetLobbyMemberData)(ISteamMatchmaking* this_, steam_id steamIDLobby, steam_id steamIDUser, const char* pchKey);
		void(__fastcall* SetLobbyMemberData)(ISteamMatchmaking* this_, steam_id steamIDLobby, const char* pchKey, const char* pchValue);
		bool(__fastcall* SendLobbyChatMsg)(ISteamMatchmaking* this_, steam_id steamIDLobby, const void* pvMsgBody, int cubMsgBody);
		int(__fastcall* GetLobbyChatEntry)(ISteamMatchmaking* this_, steam_id steamIDLobby, int iChatID, steam_id* pSteamIDUser, void* pvData, int cubData, int* peChatEntryType);
		bool(__fastcall* RequestLobbyData)(ISteamMatchmaking* this_, steam_id steamIDLobby);
		void(__fastcall* SetLobbyGameServer)(ISteamMatchmaking* this_, steam_id steamIDLobby, unsigned int unGameServerIP, unsigned __int16 unGameServerPort, steam_id steamIDGameServer);
		bool(__fastcall* GetLobbyGameServer)(ISteamMatchmaking* this_, steam_id steamIDLobby, unsigned int* punGameServerIP, unsigned __int16* punGameServerPort, steam_id* psteamIDGameServer);
		bool(__fastcall* SetLobbyMemberLimit)(ISteamMatchmaking* this_, steam_id steamIDLobby, int cMaxMembers);
		int(__fastcall* GetLobbyMemberLimit)(ISteamMatchmaking* this_, steam_id steamIDLobby);
		bool(__fastcall* SetLobbyType)(ISteamMatchmaking* this_, steam_id steamIDLobby, int eLobbyType);
		bool(__fastcall* SetLobbyJoinable)(ISteamMatchmaking* this_, steam_id steamIDLobby, bool bLobbyJoinable);
		steam_id*(__fastcall* GetLobbyOwner)(ISteamMatchmaking* this_, steam_id* owner, steam_id steamIDLobby);
		bool(__fastcall* SetLobbyOwner)(ISteamMatchmaking* this_, steam_id steamIDLobby, steam_id steamIDNewOwner);
		bool(__fastcall* SetLinkedLobby)(ISteamMatchmaking* this_, steam_id steamIDLobby, steam_id steamIDLobby2);
	};

	struct ISteamMatchmaking
	{
		ISteamMatchmaking_vtbl* __vftable /*VFT*/;
	};
}
