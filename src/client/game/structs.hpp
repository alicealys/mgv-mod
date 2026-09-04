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

	namespace Json
	{
		struct Value
		{
			union u_t
			{
				int integer;
				double value;
				char byte;
				void* ptr;
			};

			u_t u;
			char type;
			char __pad0[8];
		};
	}

	namespace lua
	{
		struct lua_State
		{

		};
	}

	namespace gn
	{
		struct swapchain
		{
			char __pad0[24];
			IDXGISwapChain* swapChain;
		};

		struct CommandList
		{
			char __pad0[4];
			unsigned int resourceId;
			void* unk;
			volatile __int32 lock;
		};

		namespace internal
		{
			namespace dx11
			{
				struct DeviceContext
				{
					char __pad0[4];
					unsigned int resourceId;
					ID3D11DeviceContext* deviceContext;
					ID3DUserDefinedAnnotation* annotation;
					gn::CommandList* commandList;
				};

				struct resource
				{
					volatile __int32 refCount;
					unsigned int resourceId;
					unsigned int a2;
					ID3D11Resource* resource;
				};
			}
		}

		namespace dx11
		{
			struct buffer
			{
				char __pad0[4];
				unsigned int resourceId;
				unsigned int byteWidth;
				unsigned int bindFlags;
				ID3D11Buffer* buffer;
			};
		}

		struct DeviceContext : gn::internal::dx11::DeviceContext
		{

		};

		struct Resource : gn::internal::dx11::resource
		{

		};

		struct Buffer : gn::dx11::buffer
		{
			char* data;
			unsigned int size;
		};
	}

	namespace Vectormath::Aos
	{
		struct Vector2
		{
			union
			{
				float values[2];
			};
		};

		struct Vector3
		{
			union
			{
				float values[4];
				__m128 value;
			};
		};

		struct Vector4
		{
			union
			{
				float values[4];
				__m128 value;
			};
		};

		struct Quat
		{
			float values[4];
		};
	}

	namespace fox
	{
		struct Rgba8;
		struct Path;

		struct SharedStringData
		{
			const char* buffer;
		};

		struct SharedString
		{
			SharedStringData* data;
		};

		struct String : SharedString
		{

		};

		struct pfimpl
		{
			__int32 refCount;
			__int32 pad;
		};

		struct SharedObject
		{
			struct vtable
			{
				void(__fastcall* __destructor)(SharedObject*);
				void(__fastcall* Release)(SharedObject*);
			};
			vtable* __vftable;
			pfimpl pf;
		};

		struct Mutex
		{
			char __pad0[16];
		};

		struct Quark
		{
			struct vtable
			{
				void(__fastcall* __destructor)(fox::Quark*);
				void(__fastcall* Initialize)(fox::Quark*);
				void(__fastcall* Terminate)(fox::Quark*);
				void(__fastcall* GetInterface)(fox::Quark*);
				void(__fastcall* CancelPermit)(fox::Quark*);
				void(__fastcall* GetCreator)(fox::Quark*);
			};

			vtable* __vftable;
			void* a1;
			void* a3;
			void* a4;
		};

		union Color
		{
			float values[4];
			__m128 value;
		};

		struct Buffer
		{
			char* data;
			char* a2;
			size_t offset;
			size_t size;
			size_t capacity;
			int flags;
		};

		static_assert(offsetof(Buffer, data) == 0);
		static_assert(offsetof(Buffer, size) == 24);
		static_assert(offsetof(Buffer, capacity) == 32);
		static_assert(offsetof(Buffer, flags) == 40);
		static_assert(sizeof(Buffer) == 0x30);

		struct StringId_fields
		{
			std::uint32_t l;
			std::uint32_t h;
		};

		struct StringId
		{
			union
			{
				StringId_fields f;
				std::uint64_t id;
			};
		};

		struct Path
		{
			__int64 id;
		};

		struct KernelString
		{
			const char* buffer;
			__int64 unk1;
			__int64 unk2;
			__int64 unk3;
		};

		struct PathId
		{
			std::uint64_t id;
		};

		typedef std::uint32_t KeyCode;

		template <typename T>
		struct EntityPtrBase
		{
			T* ptr;
		};

		struct EntityHandle
		{
			void* a1;
		};

		template <typename T>
		struct Array
		{
			std::uint32_t size;
			std::uint32_t capacity;
			T** array;
		};

		struct Entity
		{

		};

		struct RawKeyboardData
		{
			__int16 makeCode;
			char __pad0[2];
			int key;
			__int16 keyAscii;
			__int16 keyUnicode;
			bool isUp;
			bool unk;
		};

#pragma pack(push, 1)
		struct RawMouseData
		{
			int buttonStates;
			int buttonsDown;
			int buttonsUp;
			__int16 pointX;
			__int16 pointY;
			__int16 deltaX;
			__int16 deltaY;
			__int16 lastX;
			__int16 lastY;
			int buttonData;
		};
#pragma pack(pop)

		struct LuaBase
		{
			struct vftable
			{
				void(__fastcall* __destructor)();
			};

			vftable* __vftable;
			lua::lua_State* state;
			char initialized;
		};

		struct Lua : LuaBase
		{
			struct vftable
			{
				void(__fastcall* __destructor)();
			};

			void* a2;
			void* queue;
			char __pad0[56];
		};

		struct LuaAutoPtr
		{
			fox::Lua* lua;
			int top;
			int a2;
		};

		struct LuaScopedGlobalPolicy
		{
			char __pad0[16];
		};

		struct Script
		{

		};

		struct HashMapBase_unk1
		{
			void** ptr_array1;
			void* ptr1;
		};

		struct HashMapBase
		{
			struct vtable
			{

			};
			vtable* __vftable;
			HashMapBase_unk1* unk1;
			HashMapBase_unk1* unk2;
			int a1;
			short a2_1;
			short a2_2;
			void* end;
			void* ptr6;
			void* unk3;
			void* unk4;
			int unk5_1;
			int unk5_2;
			void* unk6;
		};

		namespace fs
		{
			struct MountPoint
			{

			};
		}

		namespace gk
		{
#pragma pack(push, 1)
			struct FirstPartyAccount
			{
				unsigned __int64 id;
				char name[129];
			};
#pragma pack(pop)
		}

		namespace gr
		{
			struct Scene;

			struct SceneObject;
			struct SceneObject
			{
				struct vtable
				{
					void* f[64];
				};
				vtable* __vftable;
				char __pad0[8];
				SceneObject* obj1;
				SceneObject* obj2;
				__int64 flags1;
				int priority;
				char __pad2[4];
				Scene* scene;
				short unk;
				short flags2;
				char __pad3[64];
			};

			struct SceneObjectList
			{
				SceneObject* obj1;
				SceneObject* obj2;
				int count;
			};

			struct Scene
			{
				Scene* next;
				int index;
				int flags;
				char __pad1[16];
				SharedString id;
				char __pad2[8];
				SceneObjectList** objectList1;
				SceneObjectList* objectList2;
				char __pad3[16];
				void* lock;
			};

			struct TonemapDesc
			{
				float minExposure;
				float maxExposure;
				float exposureCompensation;
				float bloomSize;
				float bloomBrightnessExtraction;
				float bloomWeight;
			};

			struct Camera
			{
				struct AdaptiveAddExpCompParameter
				{
					float param1;
					float param2;
					float param3;
					float param4;
					float param5;
					float param6;
					float param7;
					float param8;
					float param9;
					float param10;
				};

				struct vtable
				{

				};

				vtable* __vftable;
				float f38;
				float f39;
				float f40;
				float f41;
				float f42;
				float f43;
				float f44;
				float f45;
				TonemapDesc tonemapDesc;
				float m2[4];
				float m3[4];
				int view[4];
				float m5[4];
				float m6[4];
				float m7[4];
				float m8[4];
				float m9[4];
				float m10[4];
				float m11[4];
				float m12[4];
				float m13[4];
				unsigned int flags;
				float f29;
				float f30;
				float f31;
				float viewAngleFactor;
				float viewAngle;
				__int64 unk3;
				float f32;
				float f33;
				float f34;
				float f35;
				double d1;
				double d2;
				float f36;
				float f37;
				float fArr1[2];
				float fArr2[2];
				unsigned a1;
				unsigned a2;
				__int64 unk2;
				float f1;
				float f2;
				float f3;
				float f4;
				float f5;
				float f6;
				float f7;
				float f8;
				float f9;
				float f10;
				float f11;
				float f12;
				float f13;
				float f14;
				float f15;
				float f16;
				float f17;
				float f18;
				float f19;
				float f20;
				AdaptiveAddExpCompParameter adaptiveAddExpCompParameter;
			};

			struct Packet2DBuffer;
			struct Draw2D
			{
				struct vtable
				{

				};

				vtable* __vftable;
				char __pad0[16];
				Draw2D* next;
				char __pad1[8];
				int priority;
				char __pad2[20];
				Packet2DBuffer* packetBuffer;
				Camera* camera;
				int flags;
				char __pad3[8];
			};

			struct Viewport;
			struct Viewport
			{
				struct vtable
				{

				};

				vtable* __vftable;
				char __pad0[40];
				Viewport* next;
				char __pad1[1336];
				Camera camera;
			};

			struct Render;
			struct Render
			{
				struct vtable
				{

				};
				vtable* __vftable;
				Render* next;
				char __pad1[4];
				unsigned int flags;
				char __pad0[40];
				Mutex mutex;
				char __pad4[64];
				SharedString name;
				char __pad2[8];
				Viewport* viewportList;
				char __pad3[56];
			};

			struct RenderWork
			{
				char __pad0[32];
				Render* renderList;
				Render* defaultRender;
				char __pad1[32];
			};


			struct ResourceId
			{
				union
				{
					struct
					{
						unsigned int type : 7;
						unsigned int unk2 : 10;
						unsigned int index : 15;
					} fields;
					unsigned int data;
				};
			};

			struct Texture
			{
				char __pad0[24];
				ResourceId id;
			};

			struct RenderParameter
			{
				void* unk1;
				void* unk2;
				void* unk3;
				void* unk4;
				void* unk5;
				unsigned int a1;
				unsigned int a2;
				unsigned int a3;
				unsigned int a4;
				unsigned int a5;
				unsigned int a6;
				unsigned int a7;
				unsigned int a8;
				void* unk6;
				void* unk7;
				void* unk8;
				unsigned int a9;
				char a10;
				char a11;
				char a12;
				char a13;
				char a14;
				char a15;
			};

			namespace dg
			{
				struct StringFontMetricsCache
				{
					char a1;
					char a2;
					__int16 count;
					int stringWidth;
					__int16* glyphs;
				};

				struct _TextureGlyphData
				{
					unsigned short character;
					unsigned short a1_2;
					unsigned short a2_1;
					unsigned short a2_2;
					unsigned char a3_1;
					unsigned char a3_2;
					unsigned char a3_3;
					unsigned char horizontalSpace;
					unsigned char width;
					unsigned char height;
					char horizontalShift;
					char verticalShift;
					float a5;
					float a6;
					float a7;
					float a8;
				};

				struct _TextureAreaInfo
				{
					int a1;
					short width;
					short height;
					short a3_1;
					short a3_2;
					short a4_1;
					short a4_2;
				};

				struct ImageGlyphManager
				{
					struct vtable
					{
						void(__fastcall* __destructor)(ImageGlyphManager*, char);
					};

					vtable* __vftable;
					_TextureGlyphData* imageGlyphs;
					HashMapBase hashMap;
					int numGlyphs;
					int numUnk;
					char __pad2[256];
				};

				struct ImageAreaManager
				{
					struct vtable
					{
						void(__fastcall* __destructor)(ImageAreaManager*, char);
					};

					vtable* __vftable;
					_TextureAreaInfo areas[2048];
					char states[2048];
					int count;
					int a2;
					HashMapBase hashMap;
				};

				struct FontTextureRender
				{
					struct vtable
					{
						void(__fastcall* __destructor)(FontTextureRender*);
					};

					vtable* __vftable;
					unsigned int pixel_width;
					unsigned int pixel_height;
					unsigned int fontTextureHandle;
					char __pad1[4];
					void* unk1;
					char __pad2[16];
					void* unk2;
					char __pad3[16];
					ImageGlyphManager* imageGlyphManager;
					ImageAreaManager* imageAreaManager;
					char __pad4[1072];
				};

				struct FontSystem_unk2
				{
					char __pad0[10];
					char c1;
					char __pad1[53];
					__int16 s1;
					char c2;
				};

				struct MemoryManager_unk1
				{
					size_t unk1;
					void* unk2;
					size_t unk3;
					size_t unk4;
				};

				struct MemoryManager
				{
					MemoryManager_unk1* unk1;
					size_t size;
				};

				struct FontData_Glyph
				{
					unsigned int character;
					unsigned short xOffset;
					unsigned short yOffset;
					unsigned char width;
					unsigned char height;
					unsigned char layer;
					unsigned char horizontalSpace;
					unsigned char horizontalShift;
					char verticalShift;
					unsigned short unk1;
					unsigned int unk2;
				};

				struct FontData
				{
					struct vtable
					{

					};

					vtable* __vftable;
					unsigned char unk1_1;
					unsigned char unk1_2;
					unsigned char unk1_3;
					unsigned char unk1_4;
					short unk2;
					short glyphCount;
					int glyphDataSize;
					unsigned char spacing;
					unsigned char unk3_2;
					unsigned char unk3_3;
					unsigned char unk3_4;
					FontData_Glyph* glyphs;
					char unk4;
					char widthExp;
					char heightExp;
					char unk5;
					int fontDataSize;
					void* fontDataBuffer;
					MemoryManager* memoryManager;
					float width;
					float height;
					short defaultCharacter;
					unsigned char fontIndex;
					unsigned char unk7;
				};

				struct FontSystem
				{
					/*
					0: default
					1: FontSystem_LatinFont
					2: FontSystem_KanjiFont
					3: FontSystem_Slot3
					4: FontSystem_Slot4
					5: FontSystem_Slot5
					6: FontSystem_Slot6
					7: FontSystem_Slot7
					8:
					*/

					char __pad0[8];
					FontData* fonts[8];
					MemoryManager* memoryManager;
					FontTextureRender* fontTextureRender;
					FontSystem_unk2* unk2;
				};

				struct DynamicVertexBuffer_unk1
				{
					Array<gn::Buffer> bufferArray;
					unsigned int a2;
					unsigned int count;
				};

				struct DynamicVertexBuffer
				{
					struct Cluster
					{
						unsigned int count;
						gn::Resource** resources;
						char __pad0[8];
					};

					char __pad0[16];
					Cluster clusters[2];
					DynamicVertexBuffer_unk1* unk1;
					unsigned int count;
					unsigned int a4;
					gn::Buffer* buffer;
					Array<void*> unkArray;
					void* ptr1;
					unsigned int a1;
					unsigned int a2;
				};

				struct DynamicIndexBuffer
				{
					char __pad0[0x78];
				};

				struct SubCommandContext
				{

				};

				struct BuildDraw2DParameters
				{
					char __pad0[8];
					Draw2D** drawList;
					SubCommandContext* commandContext;
					DynamicVertexBuffer* vertexBuffer;
					void* ptr2;
					void* ptr3;
					Camera* camera;
					char __pad1[4];
					float f1;
					int viewX;
					int viewY;
					int viewWidth;
					int viewHeight;
					char __pad2[8];
					void* ptr4;
				};

				struct FontTextureMetrics
				{
					float f1;
					float f2;
					float f3;
					float f4;
					float f5;
					float f6;
					float f7;
					float f8;
					float f9;
				};

				struct DgTextureStreamer
				{

				};

#pragma pack(push, 1)
				struct ShadowConstantRegister
				{
					struct Buffer
					{
						struct vector
						{
							float vec[4];
						};

						gn::Buffer* bufferInstance;
						vector* vectors;
						void* unk2;
						int count;
						int a2;
					};

					Buffer buffers[8];
					void* data;
					unsigned int bufferCount;
					unsigned int vectorCount;
					unsigned int flags;
					unsigned int unkCount;
					unsigned int a1;
					void* unk1;
					unsigned int a2;
				};
#pragma pack(pop)

				struct CommandListNode;
				struct CommandListNode
				{
					fox::gr::dg::CommandListNode* node1;
					fox::gr::dg::CommandListNode* node2;
					gn::CommandList* commandList;
					unsigned int flags;
				};

				struct MaterialResource_unk1
				{
					union
					{
						struct
						{
							unsigned char textureCount1 : 4;
							unsigned char textureCount2 : 4;
						} fields;
						unsigned char data;
					};
				};

				struct MaterialResource
				{
					char __pad0[32];
					fox::gr::ResourceId shader;
					unsigned char numConsts;
					fox::gr::dg::MaterialResource_unk1 unkFields;
					char __pad2[10];
					float consts[8][4];
					fox::gr::ResourceId textures[8];
				};

				struct MaterialManager
				{
					struct vtable
					{

					};

					vtable* __vftable;
					fox::gr::dg::MaterialResource* materials;
				};

				struct ShaderTechnique
				{
					char __pad0[80];
				};

				struct ShaderTechniqueManager
				{
					struct vtable
					{

					};

					vtable* __vftable;
					ShaderTechnique* shaderTechniques;
				};

				struct RenderResourceContext
				{
					char __pad0[0x398];
				};

				struct MacroPacketBuffer
				{
					char __pad0[0x80];
				};

				struct RenderStateContext
				{
					unsigned char flags1[8];
					short w1;
					short w2;
					short w3;
					short w4;
					unsigned int flags4;
					char __pad0[4];
					void* unk1;
					void* unk2;
					float f1;
					char __pad1[20];
					float f2;
					float f3;
					float f4;
					float f5;
					unsigned int a1;
					char __pad2[36];
					unsigned int flags2;
					unsigned int flags3;
					unsigned int a5;
				};

				static_assert(offsetof(RenderStateContext, flags2) == 0x78);

				struct CommandBuffer
				{
					char __pad0[8];
					gn::DeviceContext* deviceContext;
					char flags;
					char __pad1[7];
					fox::gr::dg::CommandListNode* commandList;
					char __pad2[8];
					fox::gr::dg::ShadowConstantRegister* shadowConstantRegister;
					fox::gr::dg::RenderStateContext* renderStateContext;
					char __pad3[8];
					fox::gr::ResourceId material;
					char __pad4[556];
				};

				static_assert(offsetof(CommandBuffer, shadowConstantRegister) == 40);
				static_assert(offsetof(CommandBuffer, material) == 64);

				struct DgDx11;
				struct DgDx11
				{
					struct vtable
					{
						void(__fastcall* meth_001)(fox::gr::dg::DgDx11*);
						void(__fastcall* EndInstance)(fox::gr::dg::DgDx11*);
						void(__fastcall* SetupShaderResources)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_004)(fox::gr::dg::DgDx11*);
						void(__fastcall* Wait)(fox::gr::dg::DgDx11*);
						void(__fastcall* Kick)(fox::gr::dg::DgDx11*);
						void(__fastcall* Start)(fox::gr::dg::DgDx11*);
						void(__fastcall* End)(fox::gr::dg::DgDx11*);
						void(__fastcall* SkipRendering)(fox::gr::dg::DgDx11*);
						void(__fastcall* DestroyRenderInfo)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_011)(fox::gr::dg::DgDx11*);
						void(__fastcall* EndRender)(fox::gr::dg::DgDx11*);
						void(__fastcall* InitViewport)(fox::gr::dg::DgDx11*);
						void(__fastcall* EndViewport)(fox::gr::dg::DgDx11*);
						void(__fastcall* RestoreViewport)(fox::gr::dg::DgDx11*);
						void(__fastcall* SetViewportDirect)(fox::gr::dg::DgDx11*);
						void(__fastcall* SetGamma)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_018)(fox::gr::dg::DgDx11*);
						void(__fastcall* ValidateVideoOutSettings)(fox::gr::dg::DgDx11*);
						void(__fastcall* SetVideoOutSettings)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_021)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_022)(fox::gr::dg::DgDx11*);
						void(__fastcall* CreateRenderTarget)(fox::gr::dg::DgDx11*);
						void(__fastcall* RestoreRenderTarget)(fox::gr::dg::DgDx11*);
						void(__fastcall* CreateRenderBuffer)(fox::gr::dg::DgDx11*);
						void(__fastcall* SetViewportScissor)(fox::gr::dg::DgDx11*);
						void(__fastcall* BeginRenderBuffer)(fox::gr::dg::DgDx11*);
						void(__fastcall* EndRenderBuffer)(fox::gr::dg::DgDx11*);
						void(__fastcall* GetCurrentRenderBuffer)(fox::gr::dg::DgDx11*);
						void(__fastcall* ResolveRenderTexture)(fox::gr::dg::DgDx11*);
						void(__fastcall* GetPrimaryDepthTarget)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_032)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_033)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_034)(fox::gr::dg::DgDx11*);
						void(__fastcall* SetShader)(fox::gr::dg::DgDx11*);
						void(__fastcall* SetMatrix)(fox::gr::dg::DgDx11*);
						void(__fastcall* SetVector)(fox::gr::dg::DgDx11*);
						void(__fastcall* SetVectors)(fox::gr::dg::DgDx11*);
						void(__fastcall* SetSkinningParam)(fox::gr::dg::DgDx11*);
						void(__fastcall* CreateShaderFileResource)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_041)(fox::gr::dg::DgDx11*);
						void(__fastcall* SetShaderObject)(fox::gr::dg::DgDx11*);
						void(__fastcall* CreateInputLayoutResource)(fox::gr::dg::DgDx11*);
						void(__fastcall* SetInputLayout)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_045)(fox::gr::dg::DgDx11*);
						void(__fastcall* CreateRenderStateResource)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_047)(fox::gr::dg::DgDx11*);
						void(__fastcall* UpdateStatus)(fox::gr::dg::DgDx11*);
						void(__fastcall* SetupRenderStateByFrame)(fox::gr::dg::DgDx11*);
						void(__fastcall* CreateVertexBufferResource)(fox::gr::dg::DgDx11*);
						void(__fastcall* CreateIndexBufferResource)(fox::gr::dg::DgDx11*);
						void(__fastcall* SetVertexBuffer)(fox::gr::dg::DgDx11*);
						void(__fastcall* SetIndexBuffer)(fox::gr::dg::DgDx11*);
						void(__fastcall* CreateVertexStreamResource)(fox::gr::dg::DgDx11*);
						void(__fastcall* SetVertexStream)(fox::gr::dg::DgDx11*);
						void(__fastcall* DummyCreateTexture)(fox::gr::dg::DgDx11*);
						void(__fastcall* CreateTexture2D)(fox::gr::dg::DgDx11*);
						void(__fastcall* CreateTexture3D)(fox::gr::dg::DgDx11*);
						void(__fastcall* CreateTextureCube)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_060)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_061)(fox::gr::dg::DgDx11*);
						void(__fastcall* SetTexture)(fox::gr::dg::DgDx11*);
						void(__fastcall* SetVertexTexture)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_064)(fox::gr::dg::DgDx11*);
						void(__fastcall* SetMaterial)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_066)(fox::gr::dg::DgDx11*);
						void(__fastcall* CreateModelResource)(fox::gr::dg::DgDx11*);
						void(__fastcall* CreateCloneResource)(fox::gr::dg::DgDx11*);
						void(__fastcall* CreateModel)(fox::gr::dg::DgDx11*);
						void(__fastcall* DestroyModel)(fox::gr::dg::DgDx11*);
						void(__fastcall* StartModelObject)(fox::gr::dg::DgDx11*);
						void(__fastcall* EndModelObject)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_073)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_074)(fox::gr::dg::DgDx11*);
						void(__fastcall* EndModelDebug)(fox::gr::dg::DgDx11*);
						void(__fastcall* GetModelDebugInfo)(fox::gr::dg::DgDx11*);
						void(__fastcall* CreateClone)(fox::gr::dg::DgDx11*);
						void(__fastcall* DestroyClone)(fox::gr::dg::DgDx11*);
						void(__fastcall* GetCloneMaterials)(fox::gr::dg::DgDx11*);
						void(__fastcall* ValidateClone)(fox::gr::dg::DgDx11*);
						void(__fastcall* GetCloneModelMaxSize)(fox::gr::dg::DgDx11*);
						void(__fastcall* PerformanceEventBegin)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_083)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_084)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_085)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_086)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_087)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_088)(fox::gr::dg::DgDx11*);
						void(__fastcall* InitShadow)(fox::gr::dg::DgDx11*);
						void(__fastcall* QuitShadow)(fox::gr::dg::DgDx11*);
						void(__fastcall* StartShadow)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_092)(fox::gr::dg::DgDx11*);
						void(__fastcall* EndShadow)(fox::gr::dg::DgDx11*);
						void(__fastcall* InitGBuffer)(fox::gr::dg::DgDx11*);
						void(__fastcall* QuitGBuffer)(fox::gr::dg::DgDx11*);
						void(__fastcall* StartGeometryPass)(fox::gr::dg::DgDx11*);
						void(__fastcall* EndGeometryPass)(fox::gr::dg::DgDx11*);
						void(__fastcall* StartGeometryMaskPass)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_099)(fox::gr::dg::DgDx11*);
						void(__fastcall* StartGeometryMaskPass1)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_101)(fox::gr::dg::DgDx11*);
						void(__fastcall* StartGeometryDecalPass)(fox::gr::dg::DgDx11*);
						void(__fastcall* EndGeometryDecalPass)(fox::gr::dg::DgDx11*);
						void(__fastcall* SetupDeferredShading)(fox::gr::dg::DgDx11*);
						void(__fastcall* SetupDeferredShadingTexture)(fox::gr::dg::DgDx11*);
						void(__fastcall* StartDeferredShading)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_107)(fox::gr::dg::DgDx11*);
						void(__fastcall* DrawDeferredShading)(fox::gr::dg::DgDx11*);
						void(__fastcall* StartDeferredRendering)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_110)(fox::gr::dg::DgDx11*);
						void(__fastcall* StartGeometryVelocityPass)(fox::gr::dg::DgDx11*);
						void(__fastcall* EndGeometryVelocityPass)(fox::gr::dg::DgDx11*);
						void(__fastcall* StartGeometryMaskedVelocityPass)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_114)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_115)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_116)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_117)(fox::gr::dg::DgDx11*);
						void(__fastcall* StartShrinkBuffer)(fox::gr::dg::DgDx11*);
						void(__fastcall* EndShrinkBuffer)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_120)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_121)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_122)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_123)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_124)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_125)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_126)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_127)(fox::gr::dg::DgDx11*);
						void(__fastcall* InitLineIntegralSSAO)(fox::gr::dg::DgDx11*);
						void(__fastcall* QuitLineIntegralSSAO)(fox::gr::dg::DgDx11*);
						void(__fastcall* ResetLineIntegralSSAO)(fox::gr::dg::DgDx11*);
						void(__fastcall* StartLineIntegralSSAO)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_132)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_133)(fox::gr::dg::DgDx11*);
						void(__fastcall* InitPostFilter)(fox::gr::dg::DgDx11*);
						void(__fastcall* QuitPostFilter)(fox::gr::dg::DgDx11*);
						void(__fastcall* StartPostFilter)(fox::gr::dg::DgDx11*);
						void(__fastcall* EndPostFilter)(fox::gr::dg::DgDx11*);
						void(__fastcall* InitMotionBlur)(fox::gr::dg::DgDx11*);
						void(__fastcall* QuitMotionBlur)(fox::gr::dg::DgDx11*);
						void(__fastcall* ResetMotionBlur)(fox::gr::dg::DgDx11*);
						void(__fastcall* StartMotionBlur)(fox::gr::dg::DgDx11*);
						void(__fastcall* DrawMotionBlur)(fox::gr::dg::DgDx11*);
						void(__fastcall* EndMotionBlur)(fox::gr::dg::DgDx11*);
						void(__fastcall* InitScreenSpaceVelocity)(fox::gr::dg::DgDx11*);
						void(__fastcall* QuitScreenSpaceVelocity)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_146)(fox::gr::dg::DgDx11*);
						void(__fastcall* StartScreenSpaceVelocity)(fox::gr::dg::DgDx11*);
						void(__fastcall* DrawScreenSpaceVelocity)(fox::gr::dg::DgDx11*);
						void(__fastcall* EndScreenSpaceVelocity)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_150)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_151)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_152)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_153)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_154)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_155)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_156)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_157)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_158)(fox::gr::dg::DgDx11*);
						void(__fastcall* GetBackBufferWidth)(fox::gr::dg::DgDx11*);
						void(__fastcall* GetBackBufferHeight)(fox::gr::dg::DgDx11*);
						void(__fastcall* DrawFullScreenTriangle)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_162)(fox::gr::dg::DgDx11*);
						void(__fastcall* ResolvePrimaryBufferReplica)(fox::gr::dg::DgDx11*);
						void(__fastcall* GetPrimaryBufferReplicaAsTexture)(fox::gr::dg::DgDx11*);
						void(__fastcall* GetPrimaryBufferAsTexture)(fox::gr::dg::DgDx11*);
						void(__fastcall* GetMacroPacketBuffer)(fox::gr::dg::DgDx11*);
						void(__fastcall* BuildCommandFromOverlayModelMacroPackets)(fox::gr::dg::DgDx11*);
						void(__fastcall* GetRenderCondition)(fox::gr::dg::DgDx11*);
						void(__fastcall* SetRenderCondition)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_170)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_171)(fox::gr::dg::DgDx11*);
						void(__fastcall* CreateSubCommandContext)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_173)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_174)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_175)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_176)(fox::gr::dg::DgDx11*);
						void(__fastcall* InitTemporaryOutput)(fox::gr::dg::DgDx11*);
						void(__fastcall* meth_178)(fox::gr::dg::DgDx11*);
					};

					vtable* __vftable;
					char __pad0[140];
					TonemapDesc tonemapDesc;
					char __pad5[52];
					DynamicVertexBuffer* dynamicVertexBuffer;
					DynamicIndexBuffer* dynamicIndexBuffer;
					RenderParameter* renderParameter;
					unsigned int a6;
					unsigned int a7;
					void* unk4;
					char __pad1[32];
					MacroPacketBuffer* macroPacketBuffer;
					ShadowConstantRegister* shadowConstantRegister;
					RenderStateContext* renderStateContext;
					RenderResourceContext* renderResourceContext;
					void* unk2;
					gn::DeviceContext* deviceContext;
					void* unk3;
					void* commandListCluster;
					char __pad3[32];
					unsigned int a1;
					unsigned int a2;
					unsigned int a3;
					unsigned int a4;
					unsigned int a5;
					char __pad4[116];
				};

				struct Dg;
				struct Dg
				{
					struct vtable
					{
						void(__fastcall* meth_001)(fox::gr::dg::Dg*);
						void(__fastcall* EndInstance)(fox::gr::dg::Dg*);
						void(__fastcall* SetupShaderResources)(fox::gr::dg::Dg*);
						void(__fastcall* meth_004)(fox::gr::dg::Dg*);
						void(__fastcall* Wait)(fox::gr::dg::Dg*);
						void(__fastcall* Kick)(fox::gr::dg::Dg*);
						void(__fastcall* Start)(fox::gr::dg::Dg*);
						void(__fastcall* End)(fox::gr::dg::Dg*);
						void(__fastcall* SkipRendering)(fox::gr::dg::Dg*);
						void(__fastcall* DestroyRenderInfo)(fox::gr::dg::Dg*);
						void(__fastcall* meth_011)(fox::gr::dg::Dg*);
						void(__fastcall* EndRender)(fox::gr::dg::Dg*);
						void(__fastcall* InitViewport)(fox::gr::dg::Dg*);
						void(__fastcall* EndViewport)(fox::gr::dg::Dg*);
						void(__fastcall* RestoreViewport)(fox::gr::dg::Dg*);
						void(__fastcall* SetViewportDirect)(fox::gr::dg::Dg*);
						void(__fastcall* SetGamma)(fox::gr::dg::Dg*);
						void(__fastcall* meth_018)(fox::gr::dg::Dg*);
						void(__fastcall* ValidateVideoOutSettings)(fox::gr::dg::Dg*);
						void(__fastcall* SetVideoOutSettings)(fox::gr::dg::Dg*);
						void(__fastcall* meth_021)(fox::gr::dg::Dg*);
						void(__fastcall* meth_022)(fox::gr::dg::Dg*);
						void(__fastcall* CreateRenderTarget)(fox::gr::dg::Dg*);
						void(__fastcall* RestoreRenderTarget)(fox::gr::dg::Dg*);
						void(__fastcall* CreateRenderBuffer)(fox::gr::dg::Dg*);
						void(__fastcall* SetViewportScissor)(fox::gr::dg::Dg*);
						void(__fastcall* BeginRenderBuffer)(fox::gr::dg::Dg*);
						void(__fastcall* EndRenderBuffer)(fox::gr::dg::Dg*);
						void(__fastcall* GetCurrentRenderBuffer)(fox::gr::dg::Dg*);
						void(__fastcall* ResolveRenderTexture)(fox::gr::dg::Dg*);
						void(__fastcall* GetPrimaryDepthTarget)(fox::gr::dg::Dg*);
						void(__fastcall* meth_032)(fox::gr::dg::Dg*);
						void(__fastcall* meth_033)(fox::gr::dg::Dg*);
						void(__fastcall* meth_034)(fox::gr::dg::Dg*);
						void(__fastcall* SetShader)(fox::gr::dg::Dg*);
						void(__fastcall* SetMatrix)(fox::gr::dg::Dg*);
						void(__fastcall* SetVector)(fox::gr::dg::Dg*);
						void(__fastcall* SetVectors)(fox::gr::dg::Dg*);
						void(__fastcall* SetSkinningParam)(fox::gr::dg::Dg*);
						void(__fastcall* CreateShaderFileResource)(fox::gr::dg::Dg*);
						void(__fastcall* meth_041)(fox::gr::dg::Dg*);
						void(__fastcall* SetShaderObject)(fox::gr::dg::Dg*);
						void(__fastcall* CreateInputLayoutResource)(fox::gr::dg::Dg*);
						void(__fastcall* SetInputLayout)(fox::gr::dg::Dg*);
						void(__fastcall* meth_045)(fox::gr::dg::Dg*);
						void(__fastcall* CreateRenderStateResource)(fox::gr::dg::Dg*);
						void(__fastcall* meth_047)(fox::gr::dg::Dg*);
						void(__fastcall* UpdateStatus)(fox::gr::dg::Dg*);
						void(__fastcall* SetupRenderStateByFrame)(fox::gr::dg::Dg*);
						void(__fastcall* CreateVertexBufferResource)(fox::gr::dg::Dg*);
						void(__fastcall* CreateIndexBufferResource)(fox::gr::dg::Dg*);
						void(__fastcall* SetVertexBuffer)(fox::gr::dg::Dg*);
						void(__fastcall* SetIndexBuffer)(fox::gr::dg::Dg*);
						void(__fastcall* CreateVertexStreamResource)(fox::gr::dg::Dg*);
						void(__fastcall* SetVertexStream)(fox::gr::dg::Dg*);
						void(__fastcall* DummyCreateTexture)(fox::gr::dg::Dg*);
						void(__fastcall* CreateTexture2D)(fox::gr::dg::Dg*);
						void(__fastcall* CreateTexture3D)(fox::gr::dg::Dg*);
						void(__fastcall* CreateTextureCube)(fox::gr::dg::Dg*);
						void(__fastcall* meth_060)(fox::gr::dg::Dg*);
						void(__fastcall* meth_061)(fox::gr::dg::Dg*);
						void(__fastcall* SetTexture)(fox::gr::dg::Dg*);
						void(__fastcall* SetVertexTexture)(fox::gr::dg::Dg*);
						void(__fastcall* meth_064)(fox::gr::dg::Dg*);
						void(__fastcall* SetMaterial)(fox::gr::dg::Dg*);
						void(__fastcall* meth_066)(fox::gr::dg::Dg*);
						void(__fastcall* CreateModelResource)(fox::gr::dg::Dg*);
						void(__fastcall* CreateCloneResource)(fox::gr::dg::Dg*);
						void(__fastcall* CreateModel)(fox::gr::dg::Dg*);
						void(__fastcall* DestroyModel)(fox::gr::dg::Dg*);
						void(__fastcall* StartModelObject)(fox::gr::dg::Dg*);
						void(__fastcall* EndModelObject)(fox::gr::dg::Dg*);
						void(__fastcall* meth_073)(fox::gr::dg::Dg*);
						void(__fastcall* meth_074)(fox::gr::dg::Dg*);
						void(__fastcall* EndModelDebug)(fox::gr::dg::Dg*);
						void(__fastcall* GetModelDebugInfo)(fox::gr::dg::Dg*);
						void(__fastcall* CreateClone)(fox::gr::dg::Dg*);
						void(__fastcall* DestroyClone)(fox::gr::dg::Dg*);
						void(__fastcall* GetCloneMaterials)(fox::gr::dg::Dg*);
						void(__fastcall* ValidateClone)(fox::gr::dg::Dg*);
						void(__fastcall* GetCloneModelMaxSize)(fox::gr::dg::Dg*);
						void(__fastcall* PerformanceEventBegin)(fox::gr::dg::Dg*);
						void(__fastcall* meth_083)(fox::gr::dg::Dg*);
						void(__fastcall* meth_084)(fox::gr::dg::Dg*);
						void(__fastcall* meth_085)(fox::gr::dg::Dg*);
						void(__fastcall* meth_086)(fox::gr::dg::Dg*);
						void(__fastcall* meth_087)(fox::gr::dg::Dg*);
						void(__fastcall* meth_088)(fox::gr::dg::Dg*);
						void(__fastcall* InitShadow)(fox::gr::dg::Dg*);
						void(__fastcall* QuitShadow)(fox::gr::dg::Dg*);
						void(__fastcall* StartShadow)(fox::gr::dg::Dg*);
						void(__fastcall* meth_092)(fox::gr::dg::Dg*);
						void(__fastcall* EndShadow)(fox::gr::dg::Dg*);
						void(__fastcall* InitGBuffer)(fox::gr::dg::Dg*);
						void(__fastcall* QuitGBuffer)(fox::gr::dg::Dg*);
						void(__fastcall* StartGeometryPass)(fox::gr::dg::Dg*);
						void(__fastcall* EndGeometryPass)(fox::gr::dg::Dg*);
						void(__fastcall* StartGeometryMaskPass)(fox::gr::dg::Dg*);
						void(__fastcall* meth_099)(fox::gr::dg::Dg*);
						void(__fastcall* StartGeometryMaskPass1)(fox::gr::dg::Dg*);
						void(__fastcall* meth_101)(fox::gr::dg::Dg*);
						void(__fastcall* StartGeometryDecalPass)(fox::gr::dg::Dg*);
						void(__fastcall* EndGeometryDecalPass)(fox::gr::dg::Dg*);
						void(__fastcall* SetupDeferredShading)(fox::gr::dg::Dg*);
						void(__fastcall* SetupDeferredShadingTexture)(fox::gr::dg::Dg*);
						void(__fastcall* StartDeferredShading)(fox::gr::dg::Dg*);
						void(__fastcall* meth_107)(fox::gr::dg::Dg*);
						void(__fastcall* DrawDeferredShading)(fox::gr::dg::Dg*);
						void(__fastcall* StartDeferredRendering)(fox::gr::dg::Dg*);
						void(__fastcall* meth_110)(fox::gr::dg::Dg*);
						void(__fastcall* StartGeometryVelocityPass)(fox::gr::dg::Dg*);
						void(__fastcall* EndGeometryVelocityPass)(fox::gr::dg::Dg*);
						void(__fastcall* StartGeometryMaskedVelocityPass)(fox::gr::dg::Dg*);
						void(__fastcall* meth_114)(fox::gr::dg::Dg*);
						void(__fastcall* meth_115)(fox::gr::dg::Dg*);
						void(__fastcall* meth_116)(fox::gr::dg::Dg*);
						void(__fastcall* meth_117)(fox::gr::dg::Dg*);
						void(__fastcall* StartShrinkBuffer)(fox::gr::dg::Dg*);
						void(__fastcall* EndShrinkBuffer)(fox::gr::dg::Dg*);
						void(__fastcall* meth_120)(fox::gr::dg::Dg*);
						void(__fastcall* meth_121)(fox::gr::dg::Dg*);
						void(__fastcall* meth_122)(fox::gr::dg::Dg*);
						void(__fastcall* meth_123)(fox::gr::dg::Dg*);
						void(__fastcall* meth_124)(fox::gr::dg::Dg*);
						void(__fastcall* meth_125)(fox::gr::dg::Dg*);
						void(__fastcall* meth_126)(fox::gr::dg::Dg*);
						void(__fastcall* meth_127)(fox::gr::dg::Dg*);
						void(__fastcall* InitLineIntegralSSAO)(fox::gr::dg::Dg*);
						void(__fastcall* QuitLineIntegralSSAO)(fox::gr::dg::Dg*);
						void(__fastcall* ResetLineIntegralSSAO)(fox::gr::dg::Dg*);
						void(__fastcall* StartLineIntegralSSAO)(fox::gr::dg::Dg*);
						void(__fastcall* meth_132)(fox::gr::dg::Dg*);
						void(__fastcall* meth_133)(fox::gr::dg::Dg*);
						void(__fastcall* InitPostFilter)(fox::gr::dg::Dg*);
						void(__fastcall* QuitPostFilter)(fox::gr::dg::Dg*);
						void(__fastcall* StartPostFilter)(fox::gr::dg::Dg*);
						void(__fastcall* EndPostFilter)(fox::gr::dg::Dg*);
						void(__fastcall* InitMotionBlur)(fox::gr::dg::Dg*);
						void(__fastcall* QuitMotionBlur)(fox::gr::dg::Dg*);
						void(__fastcall* ResetMotionBlur)(fox::gr::dg::Dg*);
						void(__fastcall* StartMotionBlur)(fox::gr::dg::Dg*);
						void(__fastcall* DrawMotionBlur)(fox::gr::dg::Dg*);
						void(__fastcall* EndMotionBlur)(fox::gr::dg::Dg*);
						void(__fastcall* InitScreenSpaceVelocity)(fox::gr::dg::Dg*);
						void(__fastcall* QuitScreenSpaceVelocity)(fox::gr::dg::Dg*);
						void(__fastcall* meth_146)(fox::gr::dg::Dg*);
						void(__fastcall* StartScreenSpaceVelocity)(fox::gr::dg::Dg*);
						void(__fastcall* DrawScreenSpaceVelocity)(fox::gr::dg::Dg*);
						void(__fastcall* EndScreenSpaceVelocity)(fox::gr::dg::Dg*);
						void(__fastcall* meth_150)(fox::gr::dg::Dg*);
						void(__fastcall* meth_151)(fox::gr::dg::Dg*);
						void(__fastcall* meth_152)(fox::gr::dg::Dg*);
						void(__fastcall* meth_153)(fox::gr::dg::Dg*);
						void(__fastcall* meth_154)(fox::gr::dg::Dg*);
						void(__fastcall* meth_155)(fox::gr::dg::Dg*);
						void(__fastcall* meth_156)(fox::gr::dg::Dg*);
						void(__fastcall* meth_157)(fox::gr::dg::Dg*);
						void(__fastcall* meth_158)(fox::gr::dg::Dg*);
						void(__fastcall* GetBackBufferWidth)(fox::gr::dg::Dg*);
						void(__fastcall* GetBackBufferHeight)(fox::gr::dg::Dg*);
						void(__fastcall* DrawFullScreenTriangle)(fox::gr::dg::Dg*);
						void(__fastcall* meth_162)(fox::gr::dg::Dg*);
						void(__fastcall* ResolvePrimaryBufferReplica)(fox::gr::dg::Dg*);
						void(__fastcall* GetPrimaryBufferReplicaAsTexture)(fox::gr::dg::Dg*);
						void(__fastcall* GetPrimaryBufferAsTexture)(fox::gr::dg::Dg*);
						void(__fastcall* GetMacroPacketBuffer)(fox::gr::dg::Dg*);
						void(__fastcall* BuildCommandFromOverlayModelMacroPackets)(fox::gr::dg::Dg*);
						void(__fastcall* GetRenderCondition)(fox::gr::dg::Dg*);
						void(__fastcall* SetRenderCondition)(fox::gr::dg::Dg*);
						void(__fastcall* meth_170)(fox::gr::dg::Dg*);
						void(__fastcall* meth_171)(fox::gr::dg::Dg*);
						void(__fastcall* CreateSubCommandContext)(fox::gr::dg::Dg*);
						void(__fastcall* meth_173)(fox::gr::dg::Dg*);
						void(__fastcall* meth_174)(fox::gr::dg::Dg*);
						void(__fastcall* meth_175)(fox::gr::dg::Dg*);
						void(__fastcall* meth_176)(fox::gr::dg::Dg*);
						void(__fastcall* InitTemporaryOutput)(fox::gr::dg::Dg*);
						void(__fastcall* meth_178)(fox::gr::dg::Dg*);
					};

					vtable* __vftable;
					char __pad0[140];
					fox::gr::TonemapDesc tonemapDesc;
					char __pad1[140];
				};

				namespace plugins
				{
					struct Draw2DRenderer
					{
						char __pad0[720];
						Vectormath::Aos::Vector4 viewVec1;
						Vectormath::Aos::Vector4 viewVec2;
						BuildDraw2DParameters* parameters;
						CommandBuffer* commandBuffer;
						RenderStateContext* renderStateContext;
						Camera* defaultCamera;
						Camera* camera;
						ResourceId shader;
						gn::Buffer* buffer;
						unsigned int size;
						unsigned int bufferSizeAllocated;
						unsigned int bufferSizeUsed;
						char __pad2[4];
						unsigned short w1;
						char unk1;
						char __pad3[5];
						DynamicVertexBuffer* vertexBuffer;
						void* ptr1;
						ResourceId unkResource;
						char __pad4[36];
						char unk2;
						char __pad5[51];
						_TextureGlyphData* glyphData;
						char __pad6[8];
					};

					static_assert(offsetof(Draw2DRenderer, glyphData) == 0x3B0);
				}
			}

			struct Packet2D
			{
				Packet2D(unsigned char type_, unsigned char size_)
					: type(type_), size(size_)
				{
				}

				template <typename T>
				T* next()
				{
					return reinterpret_cast<T*>(reinterpret_cast<size_t>(this) + this->size);
				}

				unsigned char type{};
				unsigned char flags{};
				unsigned short size{};
			};

			struct Packet2DBuffer
			{
				void* a1;
				void* a2;
				Packet2D* packet;
				void* a4;
				int packetSize;
				int flags;
				int a6;
			};

			struct _fp16
			{
				unsigned short v[4];
			};

			struct Material
			{
				struct vtable
				{
					void(__fastcall* __destructor)(Material*, char);
				};

				vtable* __vftable;
				int unk;
				char __pad0[4];
				game::fox::gr::ResourceId resource;
			};

			static_assert(offsetof(Material, resource) == 0x10);

			struct MaterialParameter
			{

			};

			struct Packet2DLine : Packet2D
			{
				Packet2DLine() : Packet2D(1, 24) {}
				char __pad0[20]{};
			};

			struct Packet2DTriangle : Packet2D
			{
				Packet2DTriangle() : Packet2D(2, 36) {}
				char __pad0[32]{};
			};

			struct Packet2DQuad : Packet2D
			{
				Packet2DQuad() : Packet2D(3, 44) {}
				char __pad0[40]{};
			};

			struct Packet2DBox : Packet2D
			{
				Packet2DBox() : Packet2D(4, 20) {}
				unsigned int color{};
				unsigned __int16 f1{};
				unsigned __int16 f2{};
				unsigned __int16 f3{};
				unsigned __int16 f4{};
				unsigned __int16 f5{};
			};

			struct Packet2DSprite : Packet2D
			{
				Packet2DSprite() : Packet2D(5, 28) {}
				char __pad0[24]{};
			};

			struct Packet2DSprite2D : Packet2D
			{
				Packet2DSprite2D() : Packet2D(6, 32) {}
				char __pad0[28]{};
			};

			struct Packet2DRSprite : Packet2D
			{
				Packet2DRSprite() : Packet2D(7, 28) {}
				char __pad0[24]{};
			};

			struct Packet2DString : Packet2D
			{
				Packet2DString() : Packet2D(8, 32) {}
				fox::gr::dg::StringFontMetricsCache* fontMetricsCache{};
				unsigned short glyphUnk{};
				unsigned short glyphHeight{};
				unsigned short glyphWidth{};
				unsigned short flags{};
				unsigned int fontType{};
				unsigned short glyphSpacing{};
				unsigned short a9{};
			};

			struct Packet2DString2D : Packet2D
			{
				Packet2DString2D() : Packet2D(9, 48) {}
				char __pad0[44]{};
			};

			struct Packet2DCube : Packet2D
			{
				Packet2DCube() : Packet2D(10, 28) {}
				char __pad0[24]{};
			};

			struct Packet2DLineStrip : Packet2D
			{
				Packet2DLineStrip() : Packet2D(11, 8) {}
				char __pad0[4]{};
			};

			struct Packet2DVertex : Packet2D
			{
				Packet2DVertex() : Packet2D(0, 16) {}
				unsigned int color{};
				unsigned short v[5]{};
			};

			template <size_t Count>
			struct Packet2DTriangleStrip : Packet2D
			{
				Packet2DTriangleStrip() : Packet2D(12, 8)
				{
					this->size += Count * sizeof(Packet2DVertex);
				}
				int count = Count;
				Packet2DVertex vertices[Count]{};
			};

			struct Packet2DViewport : Packet2D
			{
				Packet2DViewport() : Packet2D(13, 12) {}
				_fp16 v{};
			};

			struct Packet2DViewmap : Packet2D
			{
				Packet2DViewmap() : Packet2D(14, 28) {}
				float v[3][3]{};
			};

			struct Packet2DWorldCoords : Packet2D
			{
				Packet2DWorldCoords() : Packet2D(15, 4) {}
			};

			struct Packet2DScreenCoords : Packet2D
			{
				Packet2DScreenCoords() : Packet2D(16, 4) {}
			};

			struct Packet2DMatrix : Packet2D
			{
				Packet2DMatrix() : Packet2D(17, 44) {}
				float v1[3]{};
				float v2[3]{};
				float quat[4]{};
			};

			struct Packet2DRotation : Packet2D
			{
				Packet2DRotation() : Packet2D(18, 20) {}
				float quat[4]{};
			};

			struct Packet2DTranslation : Packet2D
			{
				Packet2DTranslation() : Packet2D(19, 16) {}
				float x{};
				float y{};
				float z{};
			};

			struct Packet2DScale : Packet2D
			{
				Packet2DScale() : Packet2D(20, 16) {}
				float x{};
				float y{};
				float z{};
			};

			struct Packet2DBillboard : Packet2D
			{
				Packet2DBillboard() : Packet2D(21, 8) {}
				float f1{};
				float f2{};
			};

			struct Packet2DPerspective : Packet2D
			{
				Packet2DPerspective() : Packet2D(22, 24) {}
				float f1{};
				float f2{};
				float f3{};
				float f4{};
				float f5{};
			};

			struct Packet2DFlat : Packet2D
			{
				Packet2DFlat() : Packet2D(23, 4) {}
			};

			struct Packet2DDepthMode : Packet2D
			{
				Packet2DDepthMode() : Packet2D(24, 4) {}
			};

			struct Packet2DCullMode : Packet2D
			{
				Packet2DCullMode() : Packet2D(25, 4) {}
			};

			struct Packet2DTexture : Packet2D
			{
				Packet2DTexture() : Packet2D(26, 8) {}
				int id{};
			};

			struct Packet2DAlpha : Packet2D
			{
				Packet2DAlpha() : Packet2D(27, 4) {}
			};

			struct Packet2DColor : Packet2D
			{
				Packet2DColor() : Packet2D(28, 12) {}
				_fp16 rgba{};
			};

			struct Packet2DStencil : Packet2D
			{
				Packet2DStencil() : Packet2D(29, 16) {}
				unsigned char a1{};
				unsigned char a2{};
				unsigned char a3{};
				unsigned char a4{};
				unsigned char a5{};
				unsigned char a6{};
				unsigned char a7{};
				unsigned char a8{};
				int a9{};
			};

			struct Packet2DClearStencil : Packet2D
			{
				Packet2DClearStencil() : Packet2D(30, 8) {}
				int a1{};
			};

			struct Packet2DMaterial : Packet2D
			{
				Packet2DMaterial() : Packet2D(32, 16) {}
				Material* material{};
			};

			struct Packet2DMaterialWork : Packet2D
			{
				Packet2DMaterialWork() : Packet2D(33, 24) {}
				char __pad0[20]{};
			};

			struct Packet2DUserMatrix : Packet2D
			{
				Packet2DUserMatrix() : Packet2D(34, 68) {}
				char __pad0[64]{};
			};

			struct Packet2DPush : Packet2D
			{
				Packet2DPush() : Packet2D(38, 4) {}
			};

			struct Packet2DPop : Packet2D
			{
				Packet2DPop() : Packet2D(39, 4) {}
			};

			struct Packet2DResolve : Packet2D
			{
				Packet2DResolve() : Packet2D(40, 8) {}
				char __pad0[4]{};
			};

			struct Packet2DCopyRenderTarget : Packet2D
			{
				Packet2DCopyRenderTarget() : Packet2D(41, 12) {}
				char __pad0[8]{};
			};

			struct Packet2DDrawIndices : Packet2D
			{
				Packet2DDrawIndices() : Packet2D(45, 24) {}
				char __pad0[20]{};
			};

			struct Packet2DUserVertexBuffer : Packet2D
			{
				Packet2DUserVertexBuffer() : Packet2D(46, 24) {}
				char __pad0[20]{};
			};

			struct Packet2DBeginRenderToTemporary : Packet2D
			{
				Packet2DBeginRenderToTemporary() : Packet2D(47, 16) {}
				char __pad0[12]{};
			};

			struct Packet2DEndRenderToTemporary : Packet2D
			{
				Packet2DEndRenderToTemporary() : Packet2D(48, 4) {}
			};

			struct Packet2DSetTemporaryTexture : Packet2D
			{
				Packet2DSetTemporaryTexture() : Packet2D(49, 8) {}
				char __pad0[4]{};
			};
		}

		struct MessageBox2;

		namespace impl
		{
			struct TimeSystemImpl;

			struct TimeSystemImpl_vtbl
			{
				unsigned __int64(__fastcall* GetCurrentTickTime)(TimeSystemImpl* this_);
				double(__fastcall* GetSecondWithTickTime)(TimeSystemImpl* this_, __int64);
				double(__fastcall* GetSecond)(TimeSystemImpl* this_);
				unsigned __int64(__fastcall* GetTickTimeFrequency)(TimeSystemImpl* this_);
				void(__fastcall* __destructor)(TimeSystemImpl* this_);
			};

			struct TimeSystemImpl
			{
				TimeSystemImpl_vtbl* __vftable;
				char __pad0[8];
				double deltaGameTime;
				char __pad1[8];
				double gameTimeRate;
				double frameTime;
				double elapsedTimeSinceStartup;
				int frameIndex;
			};

			static_assert(offsetof(TimeSystemImpl, deltaGameTime) == 16);
			static_assert(offsetof(TimeSystemImpl, gameTimeRate) == 32);
			static_assert(offsetof(TimeSystemImpl, frameTime) == 40);
			static_assert(offsetof(TimeSystemImpl, elapsedTimeSinceStartup) == 48);
			static_assert(offsetof(TimeSystemImpl, frameIndex) == 56);

			namespace message2
			{
				struct MessageBox2Impl;
				struct MessageBox2Impl
				{
					struct vtable
					{
						void(__fastcall* SendMessageToSubscribers)(fox::impl::message2::MessageBox2Impl*);
						void(__fastcall* SendMessageTo)(fox::impl::message2::MessageBox2Impl*);
						void(__fastcall* ResendMessage)(fox::impl::message2::MessageBox2Impl*);
						void(__fastcall* meth_004)(fox::impl::message2::MessageBox2Impl*);
						void(__fastcall* __destructor)(fox::impl::message2::MessageBox2Impl*);
					};

					vtable* __vftable;
					__int64 unk1;
					__int64 unk2;
					unsigned int a1;
					char a2;
					char __pad1[3];
					unsigned int flags;
					char __pad0[4];
				};

				struct MessageSystem2Impl;
				struct MessageSystem2Impl
				{
					struct vtable
					{
						fox::MessageBox2* (__fastcall* CreateMessageBox)(fox::impl::message2::MessageSystem2Impl*);
						void(__fastcall* DeleteMessageBox)(fox::impl::message2::MessageSystem2Impl*);
						void(__fastcall* Subscribe)(fox::impl::message2::MessageSystem2Impl*);
						void(__fastcall* SendMessage1)(fox::impl::message2::MessageSystem2Impl*);
						void(__fastcall* SendMessageToSubscribers)(fox::impl::message2::MessageSystem2Impl*);
						void(__fastcall* DeliverMessages)(fox::impl::message2::MessageSystem2Impl*);
						void(__fastcall* __destructor)(fox::impl::message2::MessageSystem2Impl*);
					};

					vtable* __vftable;
					char __pad0[9064];
				};
			}
		}

		struct MessageBox2 : fox::impl::message2::MessageBox2Impl
		{

		};

		struct MessageSystem2 : fox::impl::message2::MessageSystem2Impl
		{

		};

		struct MessageBox2DelegateInterface;
		struct MessageBox2DelegateInterface
		{
			struct vtable
			{
				void(__fastcall* ReceiveMessage)(fox::MessageBox2DelegateInterface*);
				void(__fastcall* __destructor)(fox::MessageBox2DelegateInterface*);
			};

			vtable* __vftable;
		};

		struct QuarkRecreationCallbackInterface;
		struct QuarkRecreationCallbackInterface
		{
			struct vtable
			{
				void(__fastcall* meth_001)(fox::QuarkRecreationCallbackInterface*);
				void(__fastcall* __destructor)(fox::QuarkRecreationCallbackInterface*);
			};

			vtable* __vftable;
		};

		namespace concurrent
		{
			namespace impl
			{
				struct QueueBase
				{
					struct vtable
					{

					};

					vtable* __vftable;
					char __pad0[64];
				};
			}
		}

		namespace uix
		{
			struct PrefabRecordCallFunc;
		}

		namespace ui
		{
			struct LineDraw;

			struct SoundControl;

			struct TextUnit
			{
				char* text;
				unsigned int a2;
				unsigned int flags;
				unsigned __int16 textLength;
				unsigned __int16 a5;
				float textWidth;
				float textHeight;
				unsigned int paletteColor;
			};

			static_assert(offsetof(TextUnit, textWidth) == 20);
			static_assert(offsetof(TextUnit, textHeight) == 24);
			static_assert(offsetof(TextUnit, paletteColor) == 28);

			struct ModelNode
			{

			};

			struct ModelNodeText;

			struct ModelNodeText_vtbl
			{
				void(__fastcall* __destructor)(ModelNodeText*);
				void(__fastcall* GetPacketBuffer)(ModelNodeText*);
				void(__fastcall* InitializePacketBuffer)(ModelNodeText*);
				void(__fastcall* ReleasePacketBuffer)(ModelNodeText*);
				void(__fastcall* UpdatePacket)(ModelNodeText*);
				void* (__fastcall* GetBoundingBox)(ModelNodeText*);
				void(__fastcall* nullsub1)(ModelNodeText*);
				void(__fastcall* nullsub2)(ModelNodeText*);
				void(__fastcall* nullsub3)(ModelNodeText*);
			};

#pragma pack(push, 1)
			struct ModelNodeText
			{
				fox::ui::ModelNodeText_vtbl* __vftable;
				char __pad0[106];
				char f0;
				char __pad1[21];
				void* f1;
				short flags;
				char enableTextScroll;
				char __pad2[1];
				int f4;
				void* f5;
				void* f6;
				void* f7;
				void* f8;
				int f9;
				int f10;
				int packetBufferSize;
				char __pad3[4];
				fox::gr::Packet2DBuffer* packetBuffer;
				void* f12;
				char textAlign;
				char f13;
				char f14;
				char f15;
				short f16;
				char __pad4[2];
				float displayAreaOffsetX;
				float displayAreaOffsetY;
				float displayAreaWidth;
				float displayAreaHeight;
				Vectormath::Aos::Vector4 displaySizes;
				void* f20;
				int f21;
				char __pad5[4];
				void* f22;
				void* f23;
				int f24;
				char __pad6[4];
				void* f25;
				void* f26;
				fox::ui::TextUnit* textUnit;
				int f28;
				char __pad7[4];
				void* f29;
				void* f30;
				int lineWidthsCount;
				int f31;
				float* lineWidths;
				int lineHeightsCount;
				int f33;
				float* lineHeights;
				float lineHeight;
				float lineWidth;
				void* f36;
				void* f37;
				void* f38;
				void* f39;
				void* f40;
				void* f41;
				float scrollSpeed;
				float textOffsetX;
				int textScrollUnk2;
				int textScrollUnk3;
			};
#pragma pack(pop)

			static_assert(offsetof(fox::ui::ModelNodeText, __pad0) == 8);
			static_assert(offsetof(fox::ui::ModelNodeText, f0) == 114);
			static_assert(offsetof(fox::ui::ModelNodeText, __pad1) == 115);
			static_assert(offsetof(fox::ui::ModelNodeText, f1) == 136);
			static_assert(offsetof(fox::ui::ModelNodeText, flags) == 144);
			//static_assert(offsetof(fox::ui::ModelNodeText, f3) == 146);
			static_assert(offsetof(fox::ui::ModelNodeText, __pad2) == 147);
			static_assert(offsetof(fox::ui::ModelNodeText, f4) == 148);
			static_assert(offsetof(fox::ui::ModelNodeText, f5) == 152);
			static_assert(offsetof(fox::ui::ModelNodeText, f6) == 160);
			static_assert(offsetof(fox::ui::ModelNodeText, f7) == 168);
			static_assert(offsetof(fox::ui::ModelNodeText, f8) == 176);
			static_assert(offsetof(fox::ui::ModelNodeText, f9) == 184);
			static_assert(offsetof(fox::ui::ModelNodeText, f10) == 188);
			static_assert(offsetof(fox::ui::ModelNodeText, __pad3) == 196);
			static_assert(offsetof(fox::ui::ModelNodeText, packetBuffer) == 200);
			static_assert(offsetof(fox::ui::ModelNodeText, f12) == 208);
			//static_assert(offsetof(fox::ui::ModelNodeText, f13) == 216);
			static_assert(offsetof(fox::ui::ModelNodeText, f14) == 218);
			static_assert(offsetof(fox::ui::ModelNodeText, f15) == 219);
			static_assert(offsetof(fox::ui::ModelNodeText, f16) == 220);
			static_assert(offsetof(fox::ui::ModelNodeText, __pad4) == 222);
			static_assert(offsetof(fox::ui::ModelNodeText, f20) == 256);
			static_assert(offsetof(fox::ui::ModelNodeText, f21) == 264);
			static_assert(offsetof(fox::ui::ModelNodeText, __pad5) == 268);
			static_assert(offsetof(fox::ui::ModelNodeText, f22) == 272);
			static_assert(offsetof(fox::ui::ModelNodeText, f23) == 280);
			static_assert(offsetof(fox::ui::ModelNodeText, f24) == 288);
			static_assert(offsetof(fox::ui::ModelNodeText, __pad6) == 292);
			static_assert(offsetof(fox::ui::ModelNodeText, f25) == 296);
			static_assert(offsetof(fox::ui::ModelNodeText, f26) == 304);
			static_assert(offsetof(fox::ui::ModelNodeText, textUnit) == 312);
			static_assert(offsetof(fox::ui::ModelNodeText, f28) == 320);
			static_assert(offsetof(fox::ui::ModelNodeText, __pad7) == 324);
			static_assert(offsetof(fox::ui::ModelNodeText, f29) == 328);
			static_assert(offsetof(fox::ui::ModelNodeText, f30) == 336);
			//static_assert(offsetof(fox::ui::ModelNodeText, f35) == 376);
			static_assert(offsetof(fox::ui::ModelNodeText, f36) == 384);
			static_assert(offsetof(fox::ui::ModelNodeText, f37) == 392);
			static_assert(offsetof(fox::ui::ModelNodeText, f38) == 400);
			static_assert(offsetof(fox::ui::ModelNodeText, f39) == 408);
			static_assert(offsetof(fox::ui::ModelNodeText, f40) == 416);
			static_assert(offsetof(fox::ui::ModelNodeText, f41) == 424);
			//static_assert(offsetof(fox::ui::ModelNodeText, f42) == 432);
			//static_assert(offsetof(fox::ui::ModelNodeText, f43) == 440);

			static_assert(sizeof(ModelNodeText) == 0x1C0);

			struct ModelNodeLine
			{

			};

			struct ModelNodeMesh
			{

			};

			struct Model;

			struct ComponentTraversalInfo;


			struct Model
			{
				struct vtable
				{
					void* (__fastcall* Model)(fox::ui::Model* this_, void*, unsigned int);
					void* (__fastcall* Release)(fox::ui::Model* this_, void*);
					void* (__fastcall* GetComponentInfo)(fox::ui::Model* this_, fox::ui::ModelNode const*);
					void* (__fastcall* GetModelNodeCommon1)(fox::ui::Model* this_, unsigned int);
					void* (__fastcall* GetModelNodeCommon2)(fox::ui::Model* this_, fox::StringId);
					void* (__fastcall* SetupDrawPriority)(fox::ui::Model* this_, char);
					void* (__fastcall* GetType)(fox::ui::Model* this_);
					void* (__fastcall* EnableScaleInheritance)(fox::ui::Model* this_);
					void* (__fastcall* EnableRotationInheritance)(fox::ui::Model* this_);
					void* (__fastcall* EnableTranslationInheritance)(fox::ui::Model* this_);
					void* (__fastcall* EnableColorRGBInheritance)(fox::ui::Model* this_);
					void* (__fastcall* EnableColorAlphaInheritance)(fox::ui::Model* this_);
					void* (__fastcall* DisableScaleInheritance)(fox::ui::Model* this_);
					void* (__fastcall* DisableRotationInheritance)(fox::ui::Model* this_);
					void* (__fastcall* DisableTranslationInheritance)(fox::ui::Model* this_);
					void* (__fastcall* DisableColorRGBInheritance)(fox::ui::Model* this_);
					void* (__fastcall* DisableColorAlphaInheritance)(fox::ui::Model* this_);
					void* (__fastcall* SetTranslate)(fox::ui::Model* this_, Vectormath::Aos::Vector3*);
					void* (__fastcall* SetScale)(fox::ui::Model* this_, Vectormath::Aos::Vector3*);
					void* (__fastcall* SetQuaternion)(fox::ui::Model* this_, Vectormath::Aos::Quat*);
					void* (__fastcall* SetColor)(fox::ui::Model* this_, fox::Color*);
					void* (__fastcall* SetVisible)(fox::ui::Model* this_, bool);
					void* (__fastcall* GetTranslate)(fox::ui::Model* this_);
					void* (__fastcall* GetScale)(fox::ui::Model* this_);
					void* (__fastcall* GetQuaternion)(fox::ui::Model* this_);
					void* (__fastcall* GetColor)(fox::ui::Model* this_);
					void* (__fastcall* GetVisible)(fox::ui::Model* this_);
					void* (__fastcall* IsInitialized)(fox::ui::Model* this_);
					void* (__fastcall* UpdateComponent)(fox::ui::Model* this_, fox::ui::ComponentTraversalInfo*);
					void* (__fastcall* GetWorldTransform)(fox::ui::Model* this_, fox::ui::ModelNode const*, fox::ui::ComponentTraversalInfo*);
					void* (__fastcall* GetDrawPriorityForChild)(fox::ui::Model* this_);
					void* (__fastcall* IsValid)(fox::ui::Model* this_);
				};

				vtable* __vftable;
				char __pad0[24];
				int id;
				char __pad1[156];
				__int64 sceneName;
				fox::gr::Draw2D* draw2d;
				void* unk;
				fox::gr::Packet2DBuffer* packetBuffer;
				char __pad2[24];
			};

			struct WindowInterface;
			struct TriggerPool;
			struct LayoutComponent;
			struct Layout;
			struct GraphState;

			struct ModelNodeCommon
			{
				char __pad0[108];
				std::uint32_t hash;
			};

			struct Animation;

			struct Font
			{
				char __pad0[8];
				fox::gr::Texture* texture;
				char __pad1[64];
			};

			struct RawDaemon
			{

			};

			struct FontManager
			{
				struct FontGroup
				{
					Font* font;
					float width;
					float height;
					float spacing;
					float f3;
					float f4;
					char __pad0[16];
				};
			};
		}

		namespace math
		{
			struct Vector2
			{
				float x;
				float y;
			};
		}

		namespace nio
		{
			struct Object_vtbl;

#pragma pack(push, 4)
			struct Object
			{
				Object_vtbl* __vftable;
				std::uint32_t a2;
				std::uint32_t a3;
				std::uint32_t a4;
			};
#pragma pack(pop)

			template <typename T>
			struct ObjectPtr
			{
				T* ptr;
			};

			struct MpSocket
			{

			};

			struct SteamUdpSocket
			{
				struct SteamUdpAddress
				{
					struct vtable
					{

					};

					vtable* __vftable;
					steam_id remote;
				};
			};

			namespace impl
			{
				struct SppSocketImpl_mgo
				{
					char __pad1[248];
					int error;
					char __pad2[280];
					__int16 next_seq;
					__int16 last_seq;
					__int8 a2;
					__int8 a3;
					__int8 error_count;
					char __pad3[85];
					void* a1;
					char __pad4[4728];
					int rtt_time;
				};

				struct SppSocketImpl_tpp
				{
					char __pad0[5336];
					int rtt_time;
				};

				union SppSocketImpl
				{
					SppSocketImpl_tpp tpp;
					SppSocketImpl_mgo mgo;
				};
			}
		};

		namespace nt
		{
			struct SessionUserId;

			struct SessionUserId_vtbl
			{

			};

			struct SessionUserId
			{
				SessionUserId_vtbl* __vftable;
				void* a1;
				std::uint64_t userId;
			};

			struct SteamSessionUserId;

			struct SteamSessionUserId_vtbl
			{

			};

			struct SteamSessionUserId
			{
				SteamSessionUserId_vtbl* __vftable;
				std::uint8_t type;
				std::uint64_t userId;
			};

			static_assert(sizeof(SteamSessionUserId) == 0x18);

			struct Member;

			struct Member_SessionInterface;

			struct Member_SessionInterface
			{
				struct vtable
				{
					int(__fastcall* GetIndex)(Member_SessionInterface* this_);
					void* (__fastcall* GetIntAnimationController)(Member_SessionInterface* this_);
					void(__fastcall* GetSessionIdString)(Member_SessionInterface* this_, char*, void*);
					void(__fastcall* __destructor)(Member_SessionInterface* this_);
				};

				vtable* __vftable;
			};

			struct Member
			{
				fox::nio::Object object;
				fox::nt::Member_SessionInterface sessionInterface;
				void* a1;
				char index;
				fox::nio::impl::SppSocketImpl* sppSocket;
				void* sPtr2;
				std::uint8_t a5;
				int flags;
				fox::Array<fox::EntityHandle> entityHandles;
				fox::Array<fox::nio::ObjectPtr<fox::nio::MpSocket>> mpSockets;
				void* syncActivator;
				fox::nt::SteamSessionUserId* sessionUserId;
				void* sPtr3;
			};

			static_assert(offsetof(Member, sessionUserId) == 0x70);
			static_assert(sizeof(Member) == 0x80);

			struct Group
			{
				Member** members;
				void* a2;
				void* a3;
				unsigned int size;
			};

			enum SessionNotify_t
			{
				NOTIFY_SESSION_CREATE = 0,
				NOTIFY_SESSION_CLOSE = 1,
				NOTIFY_SESSION_DELETE = 2,
				NOTIFY_UNK3 = 3, // error?/update
				NOTIFY_JOIN_MEMBER = 4,
				NOTIFY_DELETE_MEMBER = 5,
				NOTIFY_COUNT = 6,
			};

			namespace impl
			{
				struct SessionIdle;

				struct SessionIdle_vtbl
				{

				};

				struct SessionIdle_SessionInterface;

				struct SessionIdle_SessionInterface_vtbl
				{

				};

				struct SessionIdle_SessionInterface
				{
					SessionIdle_SessionInterface_vtbl* __vftable;
				};

				struct SessionIdle_MpPortAllocator;

				struct SessionIdle_MpPortAllocator_vtbl
				{

				};

				struct SessionIdle_MpPortAllocator
				{
					SessionIdle_MpPortAllocator_vtbl* __vftable;
				};

				struct SessionIdle
				{
					SessionIdle_vtbl* __vftable;
					void* a2;
					void* a3;
					SessionIdle_MpPortAllocator* mpPortAllocator;
					SessionIdle_SessionInterface sessionInterface;
					SessionIdle* session1;
					void* a7;
					void* a8;
					void* a9;
					fox::nt::Member* hostMember;
					Group memberGroup1;
					Group memberGroup2;
					unsigned int a18_2;
					unsigned int flags;
					char sessionIndex;
					void* a20;
					int a21_1;
					int a21_2;
					void* a22;
					int a23_1;
					int a23_2;
					void* sPtr5;
					void* sPtr6;
					void* sPtr7;
					void* sPtr8;
					void* sPtr9;
					void* a29;
					void* a30;
					void* a31;
					void* a32;
				};

				struct SessionImpl2;

				struct SessionImpl2_vtbl_mgo
				{
					void* (__fastcall* __destructor)(SessionImpl2* this_);
					void(__fastcall* Release)(SessionImpl2* this_);
					unsigned int(__fastcall* GetState)(SessionImpl2* this_);
					Group* (__fastcall* GetPeerMembers)(SessionImpl2* this_);
					void(__fastcall* Initialize)(SessionImpl2* this_, void*);
					void(__fastcall* Terminate)(SessionImpl2* this_);
					Member* (__fastcall* GetLocalMember)(SessionImpl2* this_);
					Member* (__fastcall* GetHostMember)(SessionImpl2* this_);
					Member* (__fastcall* DeleteMember)(SessionImpl2* this_, Member* member);
					unsigned __int64(__fastcall* GetSppTimeInMsec)(SessionImpl2* this_);
					bool(__fastcall* IsEnabled)(SessionImpl2* this_);
					void(__fastcall* Close)(SessionImpl2* this_);
					void(__fastcall* SetHeartBeat)(SessionImpl2* this_, bool, float, float);
					void(__fastcall* PrepareP2PConnection)(SessionImpl2* this_, void* sessionReserveManager);
					void(__fastcall* Start)(SessionImpl2* this_);
					void(__fastcall* EnableAccept)(SessionImpl2* this_, bool);
					void(__fastcall* DisconnectPreparingMembers)(SessionImpl2* this_);
					void* (__fastcall* GetP2pConnectionManager)(SessionImpl2* this_);
					void(__fastcall* SetP2pConnectionManager)(SessionImpl2* this_, void*);
					void(__fastcall* FixFrameTime)(SessionImpl2* this_);
					void(__fastcall* Update)(SessionImpl2* this_);
					unsigned __int64(__fastcall* GetResult)(SessionImpl2* this_);
					void(__fastcall* InitAcceptedMember)(SessionImpl2* this_, void*, void*);
					Group* (__fastcall* GetAllMembers)(SessionImpl2* this_);
				};

				struct SessionImpl2_vtbl_tpp
				{
					void* (__fastcall* __destructor)(SessionImpl2* this_);
					void(__fastcall* Release)(SessionImpl2* this_);
					unsigned int(__fastcall* GetState)(SessionImpl2* this_);
					Group* (__fastcall* GetPeerMembers)(SessionImpl2* this_);
					void(__fastcall* Initialize)(SessionImpl2* this_, void*);
					void(__fastcall* Terminate)(SessionImpl2* this_);
					Member* (__fastcall* GetLocalMember)(SessionImpl2* this_);
					Member* (__fastcall* GetHostMember)(SessionImpl2* this_);
					Member* (__fastcall* DeleteMember)(SessionImpl2* this_, Member* member);
					unsigned __int64(__fastcall* GetSppTimeInMsec)(SessionImpl2* this_);
					bool(__fastcall* IsEnabled)(SessionImpl2* this_);
					void(__fastcall* SetHeartBeat)(SessionImpl2* this_, bool, float, float);
					void(__fastcall* PrepareP2PConnection)(SessionImpl2* this_, void* sessionReserveManager);
					void(__fastcall* Start)(SessionImpl2* this_);
					void(__fastcall* EnableAccept)(SessionImpl2* this_, bool);
					void(__fastcall* DisconnectPreparingMembers)(SessionImpl2* this_);
					void(__fastcall* FixFrameTime)(SessionImpl2* this_);
					void(__fastcall* Update)(SessionImpl2* this_);
					void* (__fastcall* GetP2pConnectionManager)(SessionImpl2* this_);
					unsigned __int64(__fastcall* GetResult)(SessionImpl2* this_);
					void(__fastcall* InitAcceptedMember)(SessionImpl2* this_, void*, void*);
					Group* (__fastcall* GetAllMembers)(SessionImpl2* this_);
				};

				union SessionImpl2_vtbl
				{
					SessionImpl2_vtbl_tpp tpp;
					SessionImpl2_vtbl_mgo mgo;
				};

				struct SessionImpl2_SessionInterface;

				struct SessionImpl2_SessionInterface_vtbl
				{
					Member_SessionInterface* (__fastcall* GetLocalMemberInterface)(SessionImpl2_SessionInterface* this_);
					Member_SessionInterface* (__fastcall* GetHostMemberInterface)(SessionImpl2_SessionInterface* this_);
					Member_SessionInterface* (__fastcall* GetMemberInterfaceAtIndex)(SessionImpl2_SessionInterface* this_, int);
					int(__fastcall* GetMemberCount)(SessionImpl2_SessionInterface* this_);
					unsigned int(__fastcall* GetOriginalValueCount)(SessionImpl2_SessionInterface* this_);
					bool(__fastcall* IsHost)(SessionImpl2_SessionInterface* this_);
					unsigned int(__fastcall* GetInvisibleFlagOfDebugDraw)(SessionImpl2_SessionInterface* this_);
					bool(__fastcall* IsOnline)(SessionImpl2_SessionInterface* this_);
					void(__fastcall* PrepareP2PConnection)(SessionImpl2_SessionInterface* this_, void*);
					bool(__fastcall* IsConnecting)(SessionImpl2_SessionInterface* this_);
					unsigned int(__fastcall* GetLastError)(SessionImpl2_SessionInterface* this_);
					unsigned int(__fastcall* GetLastConnectionManagerError)(SessionImpl2_SessionInterface* this_);
					unsigned int(__fastcall* __destructor)(SessionImpl2_SessionInterface* this_);
				};

				struct SessionImpl2_SessionInterface
				{
					SessionImpl2_SessionInterface_vtbl* __vftable;
				};

				struct SessionImpl2_MpPortAllocator;

				struct SessionImpl2_MpPortAllocator_vtbl
				{

				};

				struct SessionImpl2_MpPortAllocator
				{
					SessionImpl2_MpPortAllocator_vtbl* __vftable;
				};

				struct SessionImpl2
				{
					fox::nt::impl::SessionImpl2_vtbl* __vftable /*VFT*/;
					void* a2;
					void* a3;
					fox::nt::impl::SessionImpl2_MpPortAllocator* mpPortAllocator;
					fox::nt::impl::SessionImpl2_SessionInterface sessionInterface;
					fox::nt::impl::SessionImpl2* session1;
					void* sPtr1;
					void* sPtr2;
					void* sPtr3;
					fox::nt::Member* hostMember;
					fox::nt::Group allMembers;
					fox::nt::Group peerMembers;
					unsigned int state;
					char sessionIndex;
					void* a4;
					int a5;
					int a6;
					void* a7;
					int a8;
					int a9;
					fox::nio::impl::SppSocketImpl* sppSocket;
					void* sPtr6;
					void* sPtr7;
					void* sPtr8;
					void* sPtr9;
					char a10_1;
					char started;
					char acceptEnabled;
					char a10_4;
					int lastError;
				};

				static_assert(sizeof(SessionImpl2) == 232);

				struct GameSocketImpl;
				struct GameSocketImpl
				{
					struct Peer
					{

					};

					struct vtable
					{
						void(__fastcall* RequestToSend)(GameSocketImpl*, int, const void*, unsigned int);
						void(__fastcall* RequestToSendToMember)(GameSocketImpl*, char, int, const void*, unsigned int);
						void(__fastcall* RequestToSendToMembers)(GameSocketImpl*, int, int, const void*, unsigned int);
						unsigned int(__fastcall* GetPacketCount)(GameSocketImpl*, unsigned int);
						unsigned int(__fastcall* GetPacketSize)(GameSocketImpl*, unsigned int, unsigned int);
						void* (__fastcall* GetPacket)(GameSocketImpl*, unsigned int, unsigned int);
						unsigned char(__fastcall* GetPacketSender)(GameSocketImpl*, unsigned int, unsigned int);
						void(__fastcall* SetInterval)(GameSocketImpl*, int, unsigned char, float);
						void(__fastcall* __destructor)(GameSocketImpl*, char);
					};

					vtable* __vftable;
					short a1;
					short a2;
					char a3_1;
					char a3_2;
					short a4;
					int a5;
					int a6;
					void* buf1;
					void* buf2;
				};
			}

			struct Session : impl::SessionImpl2
			{
			};

			template <typename T>
			struct ObserverContainer
			{

			};

			template <typename T>
			struct ObserverBase
			{
				struct vtable
				{
					void(__fastcall* NotifyImpl)(ObserverBase<T>*, fox::nt::impl::SessionImpl2*, int, unsigned __int8* a4);
					void(__fastcall* __destructor)(ObserverBase<T>*);
				};
				vtable* __vftable;
				ObserverContainer<T>* container;
			};
		}

		namespace gm
		{
			enum PeerType
			{
				PEER_LOCAL = 0,
				PEER_HOST = 1,
				PEER_AUTHORITY = 2,
				PEER_ALL = 3,
				PEER_DIRECT = 4,
			};

			enum NetType
			{

			};

			struct GameObjectInterface;
			struct GameObjectFactoryInterface;

			struct GameObjectMessageSystem
			{
				struct vtable
				{
					void(__fastcall* __destructor)(GameObjectMessageSystem*);
					void(__fastcall* SendSignal)(GameObjectMessageSystem*, int* result, __int64 objectId, int peerType, const void* buffer, unsigned __int16 size, int a7, char memberIndex);
					void(__fastcall* SendToSessionId)(GameObjectMessageSystem*);
					void(__fastcall* SerialProcessSignals)(GameObjectMessageSystem*);
				};

				vtable* __vftable;
			};

			namespace impl
			{
				struct GameObjectMessageSystemImpl
				{
					struct vtable
					{

					};

					vtable* __vftable;
					fox::nt::ObserverBase<fox::nt::Session> sessionObserver;
					GameObjectMessageSystem messageSystem;
					fox::nt::impl::GameSocketImpl* sockets[3];
					char __pad1[104];
					Mutex mutex;
					char __pad2[184];
				};

				struct GameObjectExecutionImpl;
				struct GameObjectExecutionImpl
				{
					struct vtable
					{
						void(__fastcall* SetExecutionPriority)(fox::gm::impl::GameObjectExecutionImpl*);
						void(__fastcall* GetExecutionPriority)(fox::gm::impl::GameObjectExecutionImpl*);
						void(__fastcall* ProcessSignal)(fox::gm::impl::GameObjectExecutionImpl*);
						void(__fastcall* IsParallel)(fox::gm::impl::GameObjectExecutionImpl*);
						void(__fastcall* __destructor)(fox::gm::impl::GameObjectExecutionImpl*);
					};

					vtable* __vftable;
					unsigned int a1;
					unsigned int a2;
					unsigned int a3;
					unsigned int a4;
					unsigned short a5_1;
					unsigned short a5_2;
					unsigned int a6;
					fox::gm::GameObjectInterface* gameObjectInterface;
					void* unk1;
					unsigned a7;
					char __pad1[4];
				};


				struct GameObjectFactoryControllerImpl;
				struct GameObjectFactoryControllerImpl
				{
					struct vtable
					{
						void(__fastcall* GetFactoryForTypeId)(fox::gm::impl::GameObjectFactoryControllerImpl*);
						void(__fastcall* GetFactoryWithTypeIndex)(fox::gm::impl::GameObjectFactoryControllerImpl*);
						void(__fastcall* __destructor)(fox::gm::impl::GameObjectFactoryControllerImpl*);
					};

					vtable* __vftable;
					fox::gm::GameObjectFactoryInterface* factories[128];
				};


				struct GameObjectImpl
				{
					struct vtable
					{

					};

					vtable* __vftable;
					char __pad0[24];
					fox::gm::GameObjectInterface* gameObjectInterface;
					char __pad1[24];
				};

				struct GameObjectTypeCollector
				{
					struct vtable
					{

					};

					vtable* __vftable;
					fox::gm::impl::GameObjectImpl* gameObject;
					char __pad0[56];
				};

				struct GameObjectControllerImpl;
				struct GameObjectControllerImpl
				{
					struct vtable
					{
						void(__fastcall* GameObjectTypeWasRegistered)(fox::gm::impl::GameObjectControllerImpl*, unsigned int, fox::StringId);
						void(__fastcall* AddGameObjectImpl)(fox::gm::impl::GameObjectControllerImpl*);
						void(__fastcall* AddGameObjectLocator)(fox::gm::impl::GameObjectControllerImpl*);
						void(__fastcall* DeleteGameObject)(fox::gm::impl::GameObjectControllerImpl*);
						fox::gm::GameObjectInterface* (__fastcall* GetGameObjectWithId)(fox::gm::impl::GameObjectControllerImpl*);
						void(__fastcall* GetGameObjectIdWithInstanceName)(fox::gm::impl::GameObjectControllerImpl*);
						void(__fastcall* Update)(fox::gm::impl::GameObjectControllerImpl*);
						void(__fastcall* GetGameObjectLocatorCountToBeAdded)(fox::gm::impl::GameObjectControllerImpl*);
						void(__fastcall* __destructor)(fox::gm::impl::GameObjectControllerImpl*);
					};

					vtable* __vftable;
					fox::MessageBox2* messageBox;
					fox::MessageBox2DelegateInterface* messageBox2DelegateInterface;
					fox::QuarkRecreationCallbackInterface* quarkRecreationCallbackInterface;
					__int64 unk1;
					__int64 unk2;
					fox::gm::impl::GameObjectTypeCollector* gameObjectTypeCollectors[128];
					fox::concurrent::impl::QueueBase gameObjectLocatorQueue;
				};

			}

			struct GameObjectFactoryInterface
			{
				struct vtable
				{
					void(__fastcall* __destructor)(fox::gm::GameObjectFactoryInterface*);
					void(__fastcall* GetGameObjectTypeId)(fox::gm::GameObjectFactoryInterface*);
					void(__fastcall* GetGameObjectTypeIndex)(fox::gm::GameObjectFactoryInterface*);
					fox::gm::GameObjectInterface* (__fastcall* CreateGameObject)(fox::gm::GameObjectFactoryInterface*);
					void(__fastcall* DeleteGameObject)(fox::gm::GameObjectFactoryInterface*);
				};

				vtable* __vftable;
			};

			struct GameObjectInterface
			{
				struct ExecutionDesc
				{
					unsigned short a1;
					unsigned int a2;
					unsigned int a3;
					unsigned int a4;
					char __pad0[8];
				};

				struct unk1
				{
					char __pad0[40];
					fox::gm::impl::GameObjectExecutionImpl* execution;
				};

				struct vtable
				{
					void(__fastcall* AllocResources)(fox::gm::GameObjectInterface*);
					void(__fastcall* FreeResources)(fox::gm::GameObjectInterface*);
					void(__fastcall* meth_003)(fox::gm::GameObjectInterface*);
					void(__fastcall* TerminateGameObject)(fox::gm::GameObjectInterface*);
					void(__fastcall* Activate)(fox::gm::GameObjectInterface*);
					void(__fastcall* Deactivate)(fox::gm::GameObjectInterface*);
					void(__fastcall* AddLocators)(fox::gm::GameObjectInterface*);
					void(__fastcall* RemoveLocators)(fox::gm::GameObjectInterface*);
					void(__fastcall* GetExecutionDesc)(fox::gm::GameObjectInterface*);
					void(__fastcall* ExecuteSerially)(fox::gm::GameObjectInterface*);
					void(__fastcall* ExecuteInParallel)(fox::gm::GameObjectInterface*);
					void(__fastcall* ExecuteLast)(fox::gm::GameObjectInterface*);
					void(__fastcall* ExecuteAtInactive)(fox::gm::GameObjectInterface*);
					void(__fastcall* meth_014)(fox::gm::GameObjectInterface*);
					void(__fastcall* ProcessSignal)(fox::gm::GameObjectInterface*);
					void(__fastcall* meth_0016)(fox::gm::GameObjectInterface*);
					void(__fastcall* ProcessLuaCommand)(fox::gm::GameObjectInterface*);
					void(__fastcall* GetGameObjectIdWithName)(fox::gm::GameObjectInterface*);
					void(__fastcall* GetNameIdWithGameObjectId)(fox::gm::GameObjectInterface*);
					void(__fastcall* GetNameStringIdWithGameObjectId)(fox::gm::GameObjectInterface*);
					void(__fastcall* meth_021)(fox::gm::GameObjectInterface*);
					void(__fastcall* meth_022)(fox::gm::GameObjectInterface*);
					void(__fastcall* meth_023)(fox::gm::GameObjectInterface*);
					void(__fastcall* __destructor)(fox::gm::GameObjectInterface*);
				};

				vtable* __vftable;
				unk1* unk1;
				char __pad0[184];
			};
		}

		namespace ncl
		{
#pragma pack(push, 8)
			struct NclMessageBase
			{
				struct vtable
				{
					void(__fastcall* __destructor)(fox::ncl::NclMessageBase*);
				};

				vtable* __vftable;
				fox::String msgid;
				int a1;
				int a2;
				fox::String crypto_type;
				fox::String str4;
			};

			struct NclJsonMessage
			{
				struct vtable
				{
					void(__fastcall* __destructor)(fox::ncl::NclJsonMessage*);
					__int64(__fastcall* Serialize)(fox::ncl::NclJsonMessage*, fox::Buffer*);
					__int64(__fastcall* Deserialize)(fox::ncl::NclJsonMessage*, fox::Buffer*);
					char(__fastcall* Pack)(fox::ncl::NclJsonMessage*);
					char(__fastcall* Unpack)(fox::ncl::NclJsonMessage*);
					int(__fastcall* meth_06)(fox::ncl::NclJsonMessage*);
				};

				vtable* __vftable;
				Json::Value json;
				fox::ncl::NclMessageBase base;
			};

			struct NclJsonMessageBase
			{
				struct vtable
				{
					void(__fastcall* __destructor)(fox::ncl::NclJsonMessageBase*);
				};

				vtable* __vftable;
				int rqid;
				NclJsonMessage jsonMessage;
			};

			struct NclJsonMessageResult : NclJsonMessageBase
			{
				struct vtable
				{

				};

				vtable* __vftable;
				fox::String result;
			};

			struct NclJsonMessageResult__shifted0x10
			{
				struct vtable
				{

				};

				NclJsonMessage jsonMessage;
				vtable* __vftable;
				fox::String result;
			};
#pragma pack(pop)

#pragma pack(push, 1)
			struct NclDaemon
			{
				char __pad0[56];
				char isLogin;
				char __pad1[7];
				fox::SharedString sessionKey;
				unsigned char key[16];
				char __pad2[96];
				fox::String ip1;
				fox::String ip2;
			};
#pragma pack(pop)

			static_assert(offsetof(NclDaemon, key) == 72);

			struct NclCryptBlowfish
			{
				struct vtable
				{

				};

				fox::ncl::NclCryptBlowfish::vtable* __vftable;
				char __pad0[4168];
			};

#pragma pack(push, 1)
			struct NclHttpCodec
			{
				struct vtable
				{
					void(__fastcall* __destructor)(fox::ncl::NclHttpCodec*);
					void(__fastcall* Release)(fox::ncl::NclHttpCodec*);
					void(__fastcall* SetMessage)(fox::ncl::NclHttpCodec*, fox::ncl::NclJsonMessageBase*, fox::ncl::NclJsonMessageResult*);
					void(__fastcall* Post)(fox::ncl::NclHttpCodec*);
				};

				fox::ncl::NclHttpCodec::vtable* __vftable;
				void* ptr1;
				fox::ncl::NclCryptBlowfish* blow;
				fox::ncl::NclJsonMessageBase* messageBase;
				fox::ncl::NclJsonMessageResult* messageResult;
				void* ptr5;
				void* callback;
				void* ptr7;
				void* ptr8;
				char a1;
				__int16 a2;
				char __pad0[5];
				void* ptr10;
				int a3;
				char __pad1[4];
				void* ptr12;
			};
#pragma pack(pop)
		}

		struct QuarkSystemTable
		{
		};
	}
}
