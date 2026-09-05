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

	typedef unsigned __int8 uint8;
	typedef unsigned __int16 uint16;
	typedef unsigned __int32 uint32;
	typedef unsigned __int64 uint64;
	typedef __int16 int16;
	typedef __int32 int32;
	typedef __int64 int64;
	typedef int64 lint64;
	typedef uint64 ulint64;
	typedef __int64 intp;
	typedef short int16;
	typedef int int32;
	enum ERegisterActivationCodeResult {};
	typedef struct {} ValvePackingSentinel_t;
	typedef int32 HSteamPipe;
	typedef int32 HSteamUser;
	enum ESteamControllerPad {};
	enum EControllerSource {};
	enum EControllerSourceMode {};
	enum EControllerActionOrigin {};
	typedef uint64 ControllerHandle_t;
	typedef uint64 ControllerActionSetHandle_t;
	typedef uint64 ControllerDigitalActionHandle_t;
	typedef uint64 ControllerAnalogActionHandle_t;
	typedef struct {} ControllerDigitalActionData_t;
	typedef struct {} ControllerAnalogActionData_t;
	enum EFriendRelationship {};
	typedef int16 FriendsGroupID_t;
	enum EPersonaState {};
	enum EFriendFlags {};
	enum EUserRestriction {};
	enum EOverlayToStoreFlag {};
	enum EPersonaChange {};
	enum EGCResults {};
	typedef uint32 HHTMLBrowser;
	typedef uint32 HTTPRequestHandle;
	typedef uint32 HTTPCookieContainerHandle;
	typedef uint64 SteamItemInstanceID_t;
	typedef int32 SteamItemDef_t;
	enum ESteamItemFlags {};
	typedef int32 SteamInventoryResult_t;
	enum ELobbyType {};
	enum ELobbyComparison {};
	enum ELobbyDistanceFilter {};
	typedef int HServerQuery;
	enum EChatMemberStateChange {};
	enum AudioPlayback_Status {};
	enum EP2PSessionError {};
	enum EP2PSend {};
	typedef uint32 SNetSocket_t;
	typedef uint32 SNetListenSocket_t;
	enum ESNetSocketState {};
	enum ESNetSocketConnectionType {};
	enum EOverlayGradientDirection {};
	typedef uint64 UGCHandle_t;
	typedef uint64 PublishedFileUpdateHandle_t;
	typedef uint64 PublishedFileId_t;
	typedef uint64 UGCFileWriteStreamHandle_t;
	enum EResolveConflict {};
	enum ERemoteStoragePlatform {};
	enum ERemoteStoragePublishedFileVisibility {};
	enum EWorkshopFileType {};
	enum EWorkshopVote {};
	enum EWorkshopFileAction {};
	enum EWorkshopEnumerationType {};
	enum EWorkshopVideoProvider {};
	enum EUGCReadAction {};
	typedef uint32 ScreenshotHandle;
	typedef uint64 UGCQueryHandle_t;
	typedef uint64 UGCUpdateHandle_t;
	enum EUGCMatchingUGCType {};
	enum EUserUGCList {};
	enum EUserUGCListSortOrder {};
	enum EUGCQuery {};
	enum EItemUpdateStatus {};
	enum EItemState {};
	enum EItemStatistic {};
	enum EItemPreviewType {};
	typedef uint64 ClientUnifiedMessageHandle;
	typedef uint64 SteamLeaderboard_t;
	typedef uint64 SteamLeaderboardEntries_t;
	enum ELeaderboardDataRequest {};
	enum ELeaderboardSortMethod {};
	enum ELeaderboardDisplayType {};
	enum ELeaderboardUploadScoreMethod {};
	enum ESteamAPICallFailure {};
	enum EGamepadTextInputMode {};
	enum EGamepadTextInputLineMode {};
	enum ECheckFileSignature {};
	enum EMatchMakingServerResponse {};
	enum EResult {};
	enum EVoiceResult {};
	enum EDenyReason {};
	typedef uint32 HAuthTicket;
	enum EBeginAuthSessionResult {};
	enum EAuthSessionResponse {};
	enum EUserHasLicenseForAppResult {};
	enum EAccountType {};
	enum EAppReleaseState {};
	enum EAppOwnershipFlags {};
	enum EAppType {};
	enum ESteamUserStatType {};
	enum EChatEntryType {};
	enum EChatRoomEnterResponse {};
	enum EChatSteamIDInstanceFlags {};
	enum EMarketingMessageFlags {};
	enum ENotificationPosition {};
	enum EBroadcastUploadResult {};
	enum ELaunchOptionType {};
	enum EVRHMDType {};
	enum EHTTPMethod {};
	enum EHTTPStatusCode {};
	typedef uint64 GID_t;
	typedef uint64 JobID_t;
	typedef GID_t TxnID_t;
	typedef uint32 PackageId_t;
	typedef uint32 BundleId_t;
	typedef uint32 AppId_t;
	typedef uint64 AssetClassId_t;
	typedef uint32 PhysicalItemId_t;
	typedef uint32 DepotId_t;
	typedef uint32 RTime32;
	typedef uint32 CellID_t;
	typedef uint64 SteamAPICall_t;
	typedef uint32 AccountID_t;
	typedef uint32 PartnerId_t;
	typedef uint64 ManifestId_t;
	enum EUniverse {};
	typedef uint8 Salt_t;
	typedef char compile_time_assert_type;
	enum EServerMode {};
	typedef void* SteamAPIWarningMessageHook_t;
	typedef void* SteamAPI_CheckCallbackRegistered_t;
	typedef struct {} FriendGameInfo_t;

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

	struct CGameID
	{

	};

	struct EHTMLMouseButton
	{

	};

	struct EHTMLKeyModifiers
	{

	};

	struct MatchMakingKeyValuePair_t
	{

	};

	struct gameserveritem_t
	{

	};

	struct HServerListRequest
	{

	};

	struct P2PSessionState_t
	{

	};

	struct CellPadData
	{

	};

	struct SteamParamStringArray_t
	{

	};

	struct SteamUGCDetails_t
	{

	};

	struct LeaderboardEntry_t
	{

	};

	struct ISteamAppList;
	struct ISteamApps;
	struct ISteamAppTicket;
	struct ISteamClient;
	struct ISteamController;
	struct ISteamFriends;
	struct ISteamGameCoordinator;
	struct ISteamGameServer;
	struct ISteamGameServerStats;
	struct ISteamHTMLSurface;
	struct ISteamHTTP;
	struct ISteamInventory;
	struct ISteamMatchmaking;
	struct ISteamMatchmakingServerListResponse;
	struct ISteamMatchmakingPingResponse;
	struct ISteamMatchmakingPlayersResponse;
	struct ISteamMatchmakingRulesResponse;
	struct ISteamMatchmakingServers;
	struct ISteamMusic;
	struct ISteamMusicRemote;
	struct ISteamNetworking;
	struct ISteamPS3OverlayRenderHost;
	struct ISteamPS3OverlayRender;
	struct ISteamRemoteStorage;
	struct ISteamScreenshots;
	struct ISteamUGC;
	struct ISteamUnifiedMessages;
	struct ISteamUser;
	struct ISteamUserStats;
	struct ISteamUtils;
	struct ISteamVideo;

	struct ISteamAppList_vtbl
	{
		uint32(__fastcall* GetNumInstalledApps)(ISteamAppList*);
		uint32(__fastcall* GetInstalledApps)(ISteamAppList*, AppId_t* pvecAppID, uint32 unMaxAppIDs);
		int(__fastcall* GetAppName)(ISteamAppList*);
		int(__fastcall* GetAppInstallDir)(ISteamAppList*, AppId_t nAppID, char* pchDirectory, int cchNameMax);
		int(__fastcall* GetAppBuildId)(ISteamAppList*, AppId_t nAppID);
	};

	struct ISteamAppList
	{
		ISteamAppList_vtbl* __vftable;
	};

	struct ISteamApps_vtbl
	{
		bool(__fastcall* BIsSubscribed)(ISteamApps*);
		bool(__fastcall* BIsLowViolence)(ISteamApps*);
		bool(__fastcall* BIsCybercafe)(ISteamApps*);
		bool(__fastcall* BIsVACBanned)(ISteamApps*);
		const char* (__fastcall* GetCurrentGameLanguage)(ISteamApps*);
		const char* (__fastcall* GetAvailableGameLanguages)(ISteamApps*);
		bool(__fastcall* BIsSubscribedApp)(ISteamApps*, AppId_t appID);
		bool(__fastcall* BIsDlcInstalled)(ISteamApps*, AppId_t appID);
		uint32(__fastcall* GetEarliestPurchaseUnixTime)(ISteamApps*, AppId_t nAppID);
		bool(__fastcall* BIsSubscribedFromFreeWeekend)(ISteamApps*);
		int(__fastcall* GetDLCCount)(ISteamApps*);
		bool(__fastcall* BGetDLCDataByIndex)(ISteamApps*, int iDLC, AppId_t* pAppID, bool* pbAvailable, char* pchName, int cchNameBufferSize);
		void(__fastcall* InstallDLC)(ISteamApps*, AppId_t nAppID);
		void(__fastcall* UninstallDLC)(ISteamApps*, AppId_t nAppID);
		void(__fastcall* RequestAppProofOfPurchaseKey)(ISteamApps*, AppId_t nAppID);
		bool(__fastcall* GetCurrentBetaName)(ISteamApps*, char* pchName, int cchNameBufferSize);
		bool(__fastcall* MarkContentCorrupt)(ISteamApps*, bool bMissingFilesOnly);
		uint32(__fastcall* GetInstalledDepots)(ISteamApps*, AppId_t appID, DepotId_t* pvecDepots, uint32 cMaxDepots);
		uint32(__fastcall* GetAppInstallDir)(ISteamApps*, AppId_t appID, char* pchFolder, uint32 cchFolderBufferSize);
		bool(__fastcall* BIsAppInstalled)(ISteamApps*, AppId_t appID);
		steam_id*(__fastcall* GetAppOwner)(ISteamApps*, steam_id*);
		const char* (__fastcall* GetLaunchQueryParam)(ISteamApps*, const char* pchKey);
		bool(__fastcall* GetDlcDownloadProgress)(ISteamApps*, AppId_t nAppID, uint64* punBytesDownloaded, uint64* punBytesTotal);
		int(__fastcall* GetAppBuildId)(ISteamApps*);
		void(__fastcall* RequestAllProofOfPurchaseKeys)(ISteamApps*);
	};

	struct ISteamApps
	{
		ISteamApps_vtbl* __vftable;
	};

	struct ISteamAppTicket_vtbl
	{
		uint32(__fastcall* GetAppOwnershipTicketData)(ISteamAppTicket*, uint32 nAppID, void* pvBuffer, uint32 cbBufferLength, uint32* piAppId, uint32* piSteamId, uint32* piSignature, uint32* pcbSignature);
	};

	struct ISteamAppTicket
	{
		ISteamAppTicket_vtbl* __vftable;
	};

	struct ISteamClient_vtbl
	{
		HSteamPipe(__fastcall* CreateSteamPipe)(ISteamClient*);
		bool(__fastcall* BReleaseSteamPipe)(ISteamClient*, HSteamPipe hSteamPipe);
		HSteamUser(__fastcall* ConnectToGlobalUser)(ISteamClient*, HSteamPipe hSteamPipe);
		HSteamUser(__fastcall* CreateLocalUser)(ISteamClient*, HSteamPipe* phSteamPipe, EAccountType eAccountType);
		void(__fastcall* ReleaseUser)(ISteamClient*, HSteamPipe hSteamPipe, HSteamUser hUser);
		ISteamUser* (__fastcall* GetISteamUser)(ISteamClient*, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		ISteamGameServer* (__fastcall* GetISteamGameServer)(ISteamClient*, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		void(__fastcall* SetLocalIPBinding)(ISteamClient*, uint32 unIP, uint16 usPort);
		ISteamFriends* (__fastcall* GetISteamFriends)(ISteamClient*, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		ISteamUtils* (__fastcall* GetISteamUtils)(ISteamClient*, HSteamPipe hSteamPipe, const char* pchVersion);
		ISteamMatchmaking* (__fastcall* GetISteamMatchmaking)(ISteamClient*, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		ISteamMatchmakingServers* (__fastcall* GetISteamMatchmakingServers)(ISteamClient*, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		void* (__fastcall* GetISteamGenericInterface)(ISteamClient*, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		ISteamUserStats* (__fastcall* GetISteamUserStats)(ISteamClient*, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		ISteamGameServerStats* (__fastcall* GetISteamGameServerStats)(ISteamClient*, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion);
		ISteamApps* (__fastcall* GetISteamApps)(ISteamClient*, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		ISteamNetworking* (__fastcall* GetISteamNetworking)(ISteamClient*, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		ISteamRemoteStorage* (__fastcall* GetISteamRemoteStorage)(ISteamClient*, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion);
		ISteamScreenshots* (__fastcall* GetISteamScreenshots)(ISteamClient*, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion);
		void(__fastcall* RunFrame)(ISteamClient*);
		uint32(__fastcall* GetIPCCallCount)(ISteamClient*);
		void(__fastcall* SetWarningMessageHook)(ISteamClient*, SteamAPIWarningMessageHook_t pFunction);
		bool(__fastcall* BShutdownIfAllPipesClosed)(ISteamClient*);
		ISteamHTTP* (__fastcall* GetISteamHTTP)(ISteamClient*, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion);
		ISteamUnifiedMessages* (__fastcall* GetISteamUnifiedMessages)(ISteamClient*, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion);
		ISteamController* (__fastcall* GetISteamController)(ISteamClient*, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		ISteamUGC* (__fastcall* GetISteamUGC)(ISteamClient*, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		ISteamAppList* (__fastcall* GetISteamAppList)(ISteamClient*, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion);
		ISteamMusic* (__fastcall* GetISteamMusic)(ISteamClient*, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion);
		ISteamMusicRemote* (__fastcall* GetISteamMusicRemote)(ISteamClient*, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion);
		ISteamHTMLSurface* (__fastcall* GetISteamHTMLSurface)(ISteamClient*, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion);
		void(__fastcall* DEPRECATED_Set_SteamAPI_CPostAPIResultInProcess)(ISteamClient*);
		void(__fastcall* DEPRECATED_Remove_SteamAPI_CPostAPIResultInProcess)(ISteamClient*);
		void(__fastcall* Set_SteamAPI_CCheckCallbackRegisteredInProcess)(ISteamClient*, SteamAPI_CheckCallbackRegistered_t func);
		ISteamInventory* (__fastcall* GetISteamInventory)(ISteamClient*, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion);
		ISteamVideo* (__fastcall* GetISteamVideo)(ISteamClient*, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion);
	};

	struct ISteamClient
	{
		ISteamClient_vtbl* __vftable;
	};

	struct ISteamController_vtbl
	{
		bool(__fastcall* Init)(ISteamController*);
		bool(__fastcall* Shutdown)(ISteamController*);
		void(__fastcall* RunFrame)(ISteamController*);
		int(__fastcall* GetConnectedControllers)(ISteamController*, ControllerHandle_t* handlesOut);
		bool(__fastcall* ShowBindingPanel)(ISteamController*, ControllerHandle_t controllerHandle);
		ControllerActionSetHandle_t(__fastcall* GetActionSetHandle)(ISteamController*, const char* pszActionSetName);
		void(__fastcall* ActivateActionSet)(ISteamController*, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetHandle);
		ControllerActionSetHandle_t(__fastcall* GetCurrentActionSet)(ISteamController*, ControllerHandle_t controllerHandle);
		ControllerDigitalActionHandle_t(__fastcall* GetDigitalActionHandle)(ISteamController*, const char* pszActionName);
		ControllerDigitalActionData_t(__fastcall* GetDigitalActionData)(ISteamController*, ControllerHandle_t controllerHandle, ControllerDigitalActionHandle_t digitalActionHandle);
		int(__fastcall* GetDigitalActionOrigins)(ISteamController*, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetHandle, ControllerDigitalActionHandle_t digitalActionHandle, EControllerActionOrigin* originsOut);
		ControllerAnalogActionHandle_t(__fastcall* GetAnalogActionHandle)(ISteamController*, const char* pszActionName);
		ControllerAnalogActionData_t(__fastcall* GetAnalogActionData)(ISteamController*, ControllerHandle_t controllerHandle, ControllerAnalogActionHandle_t analogActionHandle);
		int(__fastcall* GetAnalogActionOrigins)(ISteamController*, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetHandle, ControllerAnalogActionHandle_t analogActionHandle, EControllerActionOrigin* originsOut);
		void(__fastcall* StopAnalogActionMomentum)(ISteamController*, ControllerHandle_t controllerHandle, ControllerAnalogActionHandle_t eAction);
		void(__fastcall* TriggerHapticPulse)(ISteamController*, ControllerHandle_t controllerHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec);
		void(__fastcall* TriggerRepeatedHapticPulse)(ISteamController*, ControllerHandle_t controllerHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec, unsigned short usOffMicroSec, unsigned short unRepeat, unsigned int nFlags);
	};

	struct ISteamController
	{
		ISteamController_vtbl* __vftable;
	};

	struct ISteamFriends_vtbl
	{
		const char* (__fastcall* GetPersonaName)(ISteamFriends*);
		SteamAPICall_t(__fastcall* SetPersonaName)(ISteamFriends*, const char* pchPersonaName);
		EPersonaState(__fastcall* GetPersonaState)(ISteamFriends*);
		int(__fastcall* GetFriendCount)(ISteamFriends*, int iFriendFlags);
		steam_id*(__fastcall* GetFriendByIndex)(ISteamFriends*, steam_id*, int iFriend, int iFriendFlags);
		EFriendRelationship(__fastcall* GetFriendRelationship)(ISteamFriends*, steam_id steamIDFriend);
		EPersonaState(__fastcall* GetFriendPersonaState)(ISteamFriends*, steam_id steamIDFriend);
		const char* (__fastcall* GetFriendPersonaName)(ISteamFriends*, steam_id steamIDFriend);
		bool(__fastcall* GetFriendGamePlayed)(ISteamFriends*);
		const char* (__fastcall* GetFriendPersonaNameHistory)(ISteamFriends*, steam_id steamIDFriend, int iPersonaName);
		int(__fastcall* GetFriendSteamLevel)(ISteamFriends*, steam_id steamIDFriend);
		const char* (__fastcall* GetPlayerNickname)(ISteamFriends*, steam_id steamIDPlayer);
		int(__fastcall* GetFriendsGroupCount)(ISteamFriends*);
		FriendsGroupID_t(__fastcall* GetFriendsGroupIDByIndex)(ISteamFriends*, int iFG);
		const char* (__fastcall* GetFriendsGroupName)(ISteamFriends*, FriendsGroupID_t friendsGroupID);
		int(__fastcall* GetFriendsGroupMembersCount)(ISteamFriends*, FriendsGroupID_t friendsGroupID);
		void(__fastcall* GetFriendsGroupMembersList)(ISteamFriends*, FriendsGroupID_t friendsGroupID, steam_id* pOutSteamIDMembers, int nMembersCount);
		bool(__fastcall* HasFriend)(ISteamFriends*, steam_id steamIDFriend, int iFriendFlags);
		int(__fastcall* GetClanCount)(ISteamFriends*);
		steam_id*(__fastcall* GetClanByIndex)(ISteamFriends*, steam_id*, int iClan);
		const char* (__fastcall* GetClanName)(ISteamFriends*, steam_id steamIDClan);
		const char* (__fastcall* GetClanTag)(ISteamFriends*, steam_id steamIDClan);
		bool(__fastcall* GetClanActivityCounts)(ISteamFriends*, steam_id steamIDClan, int* pnOnline, int* pnInGame, int* pnChatting);
		SteamAPICall_t(__fastcall* DownloadClanActivityCounts)(ISteamFriends*, steam_id* psteamIDClans, int cClansToRequest);
		int(__fastcall* GetFriendCountFromSource)(ISteamFriends*, steam_id steamIDSource);
		steam_id*(__fastcall* GetFriendFromSourceByIndex)(ISteamFriends*, steam_id*, steam_id steamIDSource, int iFriend);
		bool(__fastcall* IsUserInSource)(ISteamFriends*, steam_id steamIDUser, steam_id steamIDSource);
		void(__fastcall* SetInGameVoiceSpeaking)(ISteamFriends*, steam_id steamIDUser, bool bSpeaking);
		void(__fastcall* ActivateGameOverlay)(ISteamFriends*, const char* pchDialog);
		void(__fastcall* ActivateGameOverlayToUser)(ISteamFriends*, const char* pchDialog, steam_id steamID);
		void(__fastcall* ActivateGameOverlayToWebPage)(ISteamFriends*, const char* pchURL);
		void(__fastcall* ActivateGameOverlayToStore)(ISteamFriends*, AppId_t nAppID, EOverlayToStoreFlag eFlag);
		void(__fastcall* SetPlayedWith)(ISteamFriends*, steam_id steamIDUserPlayedWith);
		void(__fastcall* ActivateGameOverlayInviteDialog)(ISteamFriends*, steam_id steamIDLobby);
		int(__fastcall* GetSmallFriendAvatar)(ISteamFriends*, steam_id steamIDFriend);
		int(__fastcall* GetMediumFriendAvatar)(ISteamFriends*, steam_id steamIDFriend);
		int(__fastcall* GetLargeFriendAvatar)(ISteamFriends*, steam_id steamIDFriend);
		bool(__fastcall* RequestUserInformation)(ISteamFriends*, steam_id steamIDUser, bool bRequireNameOnly);
		SteamAPICall_t(__fastcall* RequestClanOfficerList)(ISteamFriends*, steam_id steamIDClan);
		steam_id*(__fastcall* GetClanOwner)(ISteamFriends*, steam_id*, steam_id steamIDClan);
		int(__fastcall* GetClanOfficerCount)(ISteamFriends*, steam_id steamIDClan);
		steam_id*(__fastcall* GetClanOfficerByIndex)(ISteamFriends*, steam_id*, steam_id steamIDClan, int iOfficer);
		uint32(__fastcall* GetUserRestrictions)(ISteamFriends*);
		bool(__fastcall* SetRichPresence)(ISteamFriends*, const char* pchKey, const char* pchValue);
		void(__fastcall* ClearRichPresence)(ISteamFriends*);
		const char* (__fastcall* GetFriendRichPresence)(ISteamFriends*, steam_id steamIDFriend, const char* pchKey);
		int(__fastcall* GetFriendRichPresenceKeyCount)(ISteamFriends*, steam_id steamIDFriend);
		const char* (__fastcall* GetFriendRichPresenceKeyByIndex)(ISteamFriends*, steam_id steamIDFriend, int iKey);
		void(__fastcall* RequestFriendRichPresence)(ISteamFriends*, steam_id steamIDFriend);
		bool(__fastcall* InviteUserToGame)(ISteamFriends*, steam_id steamIDFriend, const char* pchConnectString);
		int(__fastcall* GetCoplayFriendCount)(ISteamFriends*);
		steam_id*(__fastcall* GetCoplayFriend)(ISteamFriends*, steam_id*, int iCoplayFriend);
		int(__fastcall* GetFriendCoplayTime)(ISteamFriends*, steam_id steamIDFriend);
		AppId_t(__fastcall* GetFriendCoplayGame)(ISteamFriends*, steam_id steamIDFriend);
		SteamAPICall_t(__fastcall* JoinClanChatRoom)(ISteamFriends*, steam_id steamIDClan);
		bool(__fastcall* LeaveClanChatRoom)(ISteamFriends*, steam_id steamIDClan);
		int(__fastcall* GetClanChatMemberCount)(ISteamFriends*, steam_id steamIDClan);
		steam_id*(__fastcall* GetChatMemberByIndex)(ISteamFriends*, steam_id*, steam_id steamIDClan, int iUser);
		bool(__fastcall* SendClanChatMessage)(ISteamFriends*, steam_id steamIDClanChat, const char* pchText);
		int(__fastcall* GetClanChatMessage)(ISteamFriends*);
		bool(__fastcall* IsClanChatAdmin)(ISteamFriends*, steam_id steamIDClanChat, steam_id steamIDUser);
		bool(__fastcall* IsClanChatWindowOpenInSteam)(ISteamFriends*, steam_id steamIDClanChat);
		bool(__fastcall* OpenClanChatWindowInSteam)(ISteamFriends*, steam_id steamIDClanChat);
		bool(__fastcall* CloseClanChatWindowInSteam)(ISteamFriends*, steam_id steamIDClanChat);
		bool(__fastcall* SetListenForFriendsMessages)(ISteamFriends*, bool bInterceptEnabled);
		bool(__fastcall* ReplyToFriendMessage)(ISteamFriends*, steam_id steamIDFriend, const char* pchMsgToSend);
		int(__fastcall* GetFriendMessage)(ISteamFriends*, steam_id steamIDFriend, int iMessageID, void* pvData, int cubData, EChatEntryType* peChatEntryType);
		SteamAPICall_t(__fastcall* GetFollowerCount)(ISteamFriends*, steam_id steamID);
		SteamAPICall_t(__fastcall* IsFollowing)(ISteamFriends*, steam_id steamID);
		SteamAPICall_t(__fastcall* EnumerateFollowingList)(ISteamFriends*, uint32 unStartIndex);
	};

	struct ISteamFriends
	{
		ISteamFriends_vtbl* __vftable;
	};

	struct ISteamGameCoordinator_vtbl
	{
		EGCResults(__fastcall* SendMessage1)(ISteamGameCoordinator*, uint32 unMsgType, const void* pubData, uint32 cubData);
		bool(__fastcall* IsMessageAvailable)(ISteamGameCoordinator*, uint32* pcubMsgSize);
		EGCResults(__fastcall* RetrieveMessage)(ISteamGameCoordinator*, uint32* punMsgType, void* pubDest, uint32 cubDest, uint32* pcubMsgSize);
	};

	struct ISteamGameCoordinator
	{
		ISteamGameCoordinator_vtbl* __vftable;
	};

	struct ISteamGameServer_vtbl
	{
		bool(__fastcall* InitGameServer)(ISteamGameServer*, uint32 unIP, uint16 usGamePort, uint16 usQueryPort, uint32 unFlags, AppId_t nGameAppId, const char* pchVersionString);
		void(__fastcall* SetProduct)(ISteamGameServer*, const char* pszProduct);
		void(__fastcall* SetGameDescription)(ISteamGameServer*, const char* pszGameDescription);
		void(__fastcall* SetModDir)(ISteamGameServer*, const char* pszModDir);
		void(__fastcall* SetDedicatedServer)(ISteamGameServer*, bool bDedicated);
		void(__fastcall* LogOn)(ISteamGameServer*, const char* pszToken);
		void(__fastcall* LogOnAnonymous)(ISteamGameServer*);
		void(__fastcall* LogOff)(ISteamGameServer*);
		bool(__fastcall* BLoggedOn)(ISteamGameServer*);
		bool(__fastcall* BSecure)(ISteamGameServer*);
		steam_id*(__fastcall* GetSteamID)(ISteamGameServer*, steam_id*);
		bool(__fastcall* WasRestartRequested)(ISteamGameServer*);
		void(__fastcall* SetMaxPlayerCount)(ISteamGameServer*, int cPlayersMax);
		void(__fastcall* SetBotPlayerCount)(ISteamGameServer*, int cBotplayers);
		void(__fastcall* SetServerName)(ISteamGameServer*, const char* pszServerName);
		void(__fastcall* SetMapName)(ISteamGameServer*, const char* pszMapName);
		void(__fastcall* SetPasswordProtected)(ISteamGameServer*, bool bPasswordProtected);
		void(__fastcall* SetSpectatorPort)(ISteamGameServer*, uint16 unSpectatorPort);
		void(__fastcall* SetSpectatorServerName)(ISteamGameServer*, const char* pszSpectatorServerName);
		void(__fastcall* ClearAllKeyValues)(ISteamGameServer*);
		void(__fastcall* SetKeyValue)(ISteamGameServer*, const char* pKey, const char* pValue);
		void(__fastcall* SetGameTags)(ISteamGameServer*, const char* pchGameTags);
		void(__fastcall* SetGameData)(ISteamGameServer*, const char* pchGameData);
		void(__fastcall* SetRegion)(ISteamGameServer*, const char* pszRegion);
		bool(__fastcall* SendUserConnectAndAuthenticate)(ISteamGameServer*, uint32 unIPClient, const void* pvAuthBlob, uint32 cubAuthBlobSize, steam_id* pSteamIDUser);
		void(__fastcall* CreateUnauthenticatedUserConnection)(ISteamGameServer*, steam_id*);
		void(__fastcall* SendUserDisconnect)(ISteamGameServer*, steam_id steamIDUser);
		bool(__fastcall* BUpdateUserData)(ISteamGameServer*, steam_id steamIDUser, const char* pchPlayerName, uint32 uScore);
		HAuthTicket(__fastcall* GetAuthSessionTicket)(ISteamGameServer*, void* pTicket, int cbMaxTicket, uint32* pcbTicket);
		EBeginAuthSessionResult(__fastcall* BeginAuthSession)(ISteamGameServer*, const void* pAuthTicket, int cbAuthTicket, steam_id steamID);
		void(__fastcall* EndAuthSession)(ISteamGameServer*, steam_id steamID);
		void(__fastcall* CancelAuthTicket)(ISteamGameServer*, HAuthTicket hAuthTicket);
		EUserHasLicenseForAppResult(__fastcall* UserHasLicenseForApp)(ISteamGameServer*, steam_id steamID, AppId_t appID);
		bool(__fastcall* RequestUserGroupStatus)(ISteamGameServer*, steam_id steamIDUser, steam_id steamIDGroup);
		void(__fastcall* GetGameplayStats)(ISteamGameServer*);
		SteamAPICall_t(__fastcall* GetServerReputation)(ISteamGameServer*);
		uint32(__fastcall* GetPublicIP)(ISteamGameServer*);
		bool(__fastcall* HandleIncomingPacket)(ISteamGameServer*, const void* pData, int cbData, uint32 srcIP, uint16 srcPort);
		int(__fastcall* GetNextOutgoingPacket)(ISteamGameServer*, void* pOut, int cbMaxOut, uint32* pNetAdr, uint16* pPort);
		void(__fastcall* EnableHeartbeats)(ISteamGameServer*, bool bActive);
		void(__fastcall* SetHeartbeatInterval)(ISteamGameServer*, int iHeartbeatInterval);
		void(__fastcall* ForceHeartbeat)(ISteamGameServer*);
		SteamAPICall_t(__fastcall* AssociateWithClan)(ISteamGameServer*, steam_id steamIDClan);
		SteamAPICall_t(__fastcall* ComputeNewPlayerCompatibility)(ISteamGameServer*, steam_id steamIDNewPlayer);
	};

	struct ISteamGameServer
	{
		ISteamGameServer_vtbl* __vftable;
	};

	struct ISteamGameServerStats_vtbl
	{
		SteamAPICall_t(__fastcall* RequestUserStats)(ISteamGameServerStats*, steam_id steamIDUser);
		bool(__fastcall* GetUserStat1)(ISteamGameServerStats*, steam_id steamIDUser, const char* pchName, int32* pData);
		bool(__fastcall* GetUserStat2)(ISteamGameServerStats*, steam_id steamIDUser, const char* pchName, float* pData);
		bool(__fastcall* GetUserAchievement)(ISteamGameServerStats*, steam_id steamIDUser, const char* pchName, bool* pbAchieved);
		bool(__fastcall* SetUserStat1)(ISteamGameServerStats*, steam_id steamIDUser, const char* pchName, int32 nData);
		bool(__fastcall* SetUserStat2)(ISteamGameServerStats*, steam_id steamIDUser, const char* pchName, float fData);
		bool(__fastcall* UpdateUserAvgRateStat)(ISteamGameServerStats*, steam_id steamIDUser, const char* pchName, float flCountThisSession, double dSessionLength);
		bool(__fastcall* SetUserAchievement)(ISteamGameServerStats*, steam_id steamIDUser, const char* pchName);
		bool(__fastcall* ClearUserAchievement)(ISteamGameServerStats*, steam_id steamIDUser, const char* pchName);
		SteamAPICall_t(__fastcall* StoreUserStats)(ISteamGameServerStats*, steam_id steamIDUser);
	};

	struct ISteamGameServerStats
	{
		ISteamGameServerStats_vtbl* __vftable;
	};

	struct ISteamHTMLSurface_vtbl
	{
		bool(__fastcall* Init)(ISteamHTMLSurface*);
		bool(__fastcall* Shutdown)(ISteamHTMLSurface*);
		SteamAPICall_t(__fastcall* CreateBrowser)(ISteamHTMLSurface*, const char* pchUserAgent, const char* pchUserCSS);
		void(__fastcall* RemoveBrowser)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle);
		void(__fastcall* LoadURL)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle, const char* pchURL, const char* pchPostData);
		void(__fastcall* SetSize)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle, uint32 unWidth, uint32 unHeight);
		void(__fastcall* StopLoad)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle);
		void(__fastcall* Reload)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle);
		void(__fastcall* GoBack)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle);
		void(__fastcall* GoForward)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle);
		void(__fastcall* AddHeader)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle, const char* pchKey, const char* pchValue);
		void(__fastcall* ExecuteJavascript)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle, const char* pchScript);
		void(__fastcall* MouseUp)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle, EHTMLMouseButton eMouseButton);
		void(__fastcall* MouseDown)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle, EHTMLMouseButton eMouseButton);
		void(__fastcall* MouseDoubleClick)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle, EHTMLMouseButton eMouseButton);
		void(__fastcall* MouseMove)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle, int x, int y);
		void(__fastcall* MouseWheel)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle, int32 nDelta);
		void(__fastcall* KeyDown)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle, uint32 nNativeKeyCode, EHTMLKeyModifiers eHTMLKeyModifiers);
		void(__fastcall* KeyUp)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle, uint32 nNativeKeyCode, EHTMLKeyModifiers eHTMLKeyModifiers);
		void(__fastcall* KeyChar)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle, uint32 cUnicodeChar, EHTMLKeyModifiers eHTMLKeyModifiers);
		void(__fastcall* SetHorizontalScroll)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle, uint32 nAbsolutePixelScroll);
		void(__fastcall* SetVerticalScroll)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle, uint32 nAbsolutePixelScroll);
		void(__fastcall* SetKeyFocus)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle, bool bHasKeyFocus);
		void(__fastcall* ViewSource)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle);
		void(__fastcall* CopyToClipboard)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle);
		void(__fastcall* PasteFromClipboard)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle);
		void(__fastcall* Find)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle, const char* pchSearchStr, bool bCurrentlyInFind, bool bReverse);
		void(__fastcall* StopFind)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle);
		void(__fastcall* GetLinkAtPosition)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle, int x, int y);
		void(__fastcall* SetCookie)(ISteamHTMLSurface*, const char* pchHostname, const char* pchKey, const char* pchValue, const char* pchPath, RTime32 nExpires, bool bSecure, bool bHTTPOnly);
		void(__fastcall* SetPageScaleFactor)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle, float flZoom, int nPointX, int nPointY);
		void(__fastcall* SetBackgroundMode)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle, bool bBackgroundMode);
		void(__fastcall* AllowStartRequest)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle, bool bAllowed);
		void(__fastcall* JSDialogResponse)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle, bool bResult);
		void(__fastcall* FileLoadDialogResponse)(ISteamHTMLSurface*, HHTMLBrowser unBrowserHandle, const char** pchSelectedFiles);
	};

	struct ISteamHTMLSurface
	{
		ISteamHTMLSurface_vtbl* __vftable;
	};

	struct ISteamHTTP_vtbl
	{
		HTTPRequestHandle(__fastcall* CreateHTTPRequest)(ISteamHTTP*, EHTTPMethod eHTTPRequestMethod, const char* pchAbsoluteURL);
		bool(__fastcall* SetHTTPRequestContextValue)(ISteamHTTP*, HTTPRequestHandle hRequest, uint64 ulContextValue);
		bool(__fastcall* SetHTTPRequestNetworkActivityTimeout)(ISteamHTTP*, HTTPRequestHandle hRequest, uint32 unTimeoutSeconds);
		bool(__fastcall* SetHTTPRequestHeaderValue)(ISteamHTTP*, HTTPRequestHandle hRequest, const char* pchHeaderName, const char* pchHeaderValue);
		bool(__fastcall* SetHTTPRequestGetOrPostParameter)(ISteamHTTP*, HTTPRequestHandle hRequest, const char* pchParamName, const char* pchParamValue);
		bool(__fastcall* SendHTTPRequest)(ISteamHTTP*, HTTPRequestHandle hRequest, SteamAPICall_t* pCallHandle);
		bool(__fastcall* SendHTTPRequestAndStreamResponse)(ISteamHTTP*, HTTPRequestHandle hRequest, SteamAPICall_t* pCallHandle);
		bool(__fastcall* DeferHTTPRequest)(ISteamHTTP*, HTTPRequestHandle hRequest);
		bool(__fastcall* PrioritizeHTTPRequest)(ISteamHTTP*, HTTPRequestHandle hRequest);
		bool(__fastcall* GetHTTPResponseHeaderSize)(ISteamHTTP*, HTTPRequestHandle hRequest, const char* pchHeaderName, uint32* unResponseHeaderSize);
		bool(__fastcall* GetHTTPResponseHeaderValue)(ISteamHTTP*, HTTPRequestHandle hRequest, const char* pchHeaderName, uint8* pHeaderValueBuffer, uint32 unBufferSize);
		bool(__fastcall* GetHTTPResponseBodySize)(ISteamHTTP*, HTTPRequestHandle hRequest, uint32* unBodySize);
		bool(__fastcall* GetHTTPResponseBodyData)(ISteamHTTP*, HTTPRequestHandle hRequest, uint8* pBodyDataBuffer, uint32 unBufferSize);
		bool(__fastcall* GetHTTPStreamingResponseBodyData)(ISteamHTTP*, HTTPRequestHandle hRequest, uint32 cOffset, uint8* pBodyDataBuffer, uint32 unBufferSize);
		bool(__fastcall* ReleaseHTTPRequest)(ISteamHTTP*, HTTPRequestHandle hRequest);
		bool(__fastcall* GetHTTPDownloadProgressPct)(ISteamHTTP*, HTTPRequestHandle hRequest, float* pflPercentOut);
		bool(__fastcall* SetHTTPRequestRawPostBody)(ISteamHTTP*, HTTPRequestHandle hRequest, const char* pchContentType, uint8* pubBody, uint32 unBodyLen);
		HTTPCookieContainerHandle(__fastcall* CreateCookieContainer)(ISteamHTTP*, bool bAllowResponsesToModify);
		bool(__fastcall* ReleaseCookieContainer)(ISteamHTTP*, HTTPCookieContainerHandle hCookieContainer);
		bool(__fastcall* SetCookie)(ISteamHTTP*, HTTPCookieContainerHandle hCookieContainer, const char* pchHost, const char* pchUrl, const char* pchCookie);
		bool(__fastcall* SetHTTPRequestCookieContainer)(ISteamHTTP*, HTTPRequestHandle hRequest, HTTPCookieContainerHandle hCookieContainer);
		bool(__fastcall* SetHTTPRequestUserAgentInfo)(ISteamHTTP*, HTTPRequestHandle hRequest, const char* pchUserAgentInfo);
		bool(__fastcall* SetHTTPRequestRequiresVerifiedCertificate)(ISteamHTTP*, HTTPRequestHandle hRequest, bool bRequireVerifiedCertificate);
		bool(__fastcall* SetHTTPRequestAbsoluteTimeoutMS)(ISteamHTTP*, HTTPRequestHandle hRequest, uint32 unMilliseconds);
		bool(__fastcall* GetHTTPRequestWasTimedOut)(ISteamHTTP*, HTTPRequestHandle hRequest, bool* pbWasTimedOut);
	};

	struct ISteamHTTP
	{
		ISteamHTTP_vtbl* __vftable;
	};

	struct ISteamInventory_vtbl
	{
		EResult(__fastcall* GetResultStatus)(ISteamInventory*, SteamInventoryResult_t resultHandle);
		uint32(__fastcall* GetResultTimestamp)(ISteamInventory*, SteamInventoryResult_t resultHandle);
		bool(__fastcall* CheckResultSteamID)(ISteamInventory*, SteamInventoryResult_t resultHandle, steam_id steamIDExpected);
		void(__fastcall* DestroyResult)(ISteamInventory*, SteamInventoryResult_t resultHandle);
		bool(__fastcall* GetAllItems)(ISteamInventory*, SteamInventoryResult_t* pResultHandle);
		bool(__fastcall* GetItemsByID)(ISteamInventory*, SteamInventoryResult_t* pResultHandle, const SteamItemInstanceID_t* pInstanceIDs, uint32 unCountInstanceIDs);
		bool(__fastcall* SerializeResult)(ISteamInventory*, SteamInventoryResult_t resultHandle, void* pOutBuffer, uint32* punOutBufferSize);
		bool(__fastcall* DeserializeResult)(ISteamInventory*, SteamInventoryResult_t* pOutResultHandle, const void* pBuffer, uint32 unBufferSize, bool bRESERVED_MUST_BE_FALSE);
		bool(__fastcall* GenerateItems)(ISteamInventory*, SteamInventoryResult_t* pResultHandle, const SteamItemDef_t* pArrayItemDefs, const uint32* punArrayQuantity, uint32 unArrayLength);
		bool(__fastcall* GrantPromoItems)(ISteamInventory*, SteamInventoryResult_t* pResultHandle);
		bool(__fastcall* AddPromoItem)(ISteamInventory*, SteamInventoryResult_t* pResultHandle, SteamItemDef_t itemDef);
		bool(__fastcall* AddPromoItems)(ISteamInventory*, SteamInventoryResult_t* pResultHandle, const SteamItemDef_t* pArrayItemDefs, uint32 unArrayLength);
		bool(__fastcall* ConsumeItem)(ISteamInventory*, SteamInventoryResult_t* pResultHandle, SteamItemInstanceID_t itemConsume, uint32 unQuantity);
		bool(__fastcall* TransferItemQuantity)(ISteamInventory*, SteamInventoryResult_t* pResultHandle, SteamItemInstanceID_t itemIdSource, uint32 unQuantity, SteamItemInstanceID_t itemIdDest);
		void(__fastcall* SendItemDropHeartbeat)(ISteamInventory*);
		bool(__fastcall* TriggerItemDrop)(ISteamInventory*, SteamInventoryResult_t* pResultHandle, SteamItemDef_t dropListDefinition);
		bool(__fastcall* LoadItemDefinitions)(ISteamInventory*);
	};

	struct ISteamInventory
	{
		ISteamInventory_vtbl* __vftable;
	};

	struct ISteamMatchmaking_vtbl
	{
		int(__fastcall* GetFavoriteGameCount)(ISteamMatchmaking*);
		bool(__fastcall* GetFavoriteGame)(ISteamMatchmaking*, int iGame, AppId_t* pnAppID, uint32* pnIP, uint16* pnConnPort, uint16* pnQueryPort, uint32* punFlags, uint32* pRTime32LastPlayedOnServer);
		int(__fastcall* AddFavoriteGame)(ISteamMatchmaking*, AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer);
		bool(__fastcall* RemoveFavoriteGame)(ISteamMatchmaking*, AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags);
		SteamAPICall_t(__fastcall* RequestLobbyList)(ISteamMatchmaking*);
		void(__fastcall* AddRequestLobbyListStringFilter)(ISteamMatchmaking*, const char* pchKeyToMatch, const char* pchValueToMatch, ELobbyComparison eComparisonType);
		void(__fastcall* AddRequestLobbyListNumericalFilter)(ISteamMatchmaking*, const char* pchKeyToMatch, int nValueToMatch, ELobbyComparison eComparisonType);
		void(__fastcall* AddRequestLobbyListNearValueFilter)(ISteamMatchmaking*, const char* pchKeyToMatch, int nValueToBeCloseTo);
		void(__fastcall* AddRequestLobbyListFilterSlotsAvailable)(ISteamMatchmaking*, int nSlotsAvailable);
		void(__fastcall* AddRequestLobbyListDistanceFilter)(ISteamMatchmaking*, ELobbyDistanceFilter eLobbyDistanceFilter);
		void(__fastcall* AddRequestLobbyListResultCountFilter)(ISteamMatchmaking*, int cMaxResults);
		void(__fastcall* AddRequestLobbyListCompatibleMembersFilter)(ISteamMatchmaking*, steam_id steamIDLobby);
		steam_id(__fastcall* GetLobbyByIndex)(ISteamMatchmaking*, steam_id*, int iLobby);
		SteamAPICall_t(__fastcall* CreateLobby)(ISteamMatchmaking*, ELobbyType eLobbyType, int cMaxMembers);
		SteamAPICall_t(__fastcall* JoinLobby)(ISteamMatchmaking*, steam_id steamIDLobby);
		void(__fastcall* LeaveLobby)(ISteamMatchmaking*, steam_id steamIDLobby);
		bool(__fastcall* InviteUserToLobby)(ISteamMatchmaking*, steam_id steamIDLobby, steam_id steamIDInvitee);
		int(__fastcall* GetNumLobbyMembers)(ISteamMatchmaking*, steam_id steamIDLobby);
		steam_id*(__fastcall* GetLobbyMemberByIndex)(ISteamMatchmaking*, steam_id*, steam_id steamIDLobby, int iMember);
		const char* (__fastcall* GetLobbyData)(ISteamMatchmaking*, steam_id steamIDLobby, const char* pchKey);
		bool(__fastcall* SetLobbyData)(ISteamMatchmaking*, steam_id steamIDLobby, const char* pchKey, const char* pchValue);
		int(__fastcall* GetLobbyDataCount)(ISteamMatchmaking*, steam_id steamIDLobby);
		bool(__fastcall* GetLobbyDataByIndex)(ISteamMatchmaking*, steam_id steamIDLobby, int iLobbyData, char* pchKey, int cchKeyBufferSize, char* pchValue, int cchValueBufferSize);
		bool(__fastcall* DeleteLobbyData)(ISteamMatchmaking*, steam_id steamIDLobby, const char* pchKey);
		const char* (__fastcall* GetLobbyMemberData)(ISteamMatchmaking*, steam_id steamIDLobby, steam_id steamIDUser, const char* pchKey);
		void(__fastcall* SetLobbyMemberData)(ISteamMatchmaking*, steam_id steamIDLobby, const char* pchKey, const char* pchValue);
		bool(__fastcall* SendLobbyChatMsg)(ISteamMatchmaking*, steam_id steamIDLobby, const void* pvMsgBody, int cubMsgBody);
		int(__fastcall* GetLobbyChatEntry)(ISteamMatchmaking*);
		bool(__fastcall* RequestLobbyData)(ISteamMatchmaking*, steam_id steamIDLobby);
		void(__fastcall* SetLobbyGameServer)(ISteamMatchmaking*, steam_id steamIDLobby, uint32 unGameServerIP, uint16 unGameServerPort, steam_id steamIDGameServer);
		bool(__fastcall* GetLobbyGameServer)(ISteamMatchmaking*);
		bool(__fastcall* SetLobbyMemberLimit)(ISteamMatchmaking*, steam_id steamIDLobby, int cMaxMembers);
		int(__fastcall* GetLobbyMemberLimit)(ISteamMatchmaking*, steam_id steamIDLobby);
		bool(__fastcall* SetLobbyType)(ISteamMatchmaking*, steam_id steamIDLobby, ELobbyType eLobbyType);
		bool(__fastcall* SetLobbyJoinable)(ISteamMatchmaking*, steam_id steamIDLobby, bool bLobbyJoinable);
		steam_id*(__fastcall* GetLobbyOwner)(ISteamMatchmaking*, steam_id*, steam_id steamIDLobby);
		bool(__fastcall* SetLobbyOwner)(ISteamMatchmaking*, steam_id steamIDLobby, steam_id steamIDNewOwner);
		bool(__fastcall* SetLinkedLobby)(ISteamMatchmaking*, steam_id steamIDLobby, steam_id steamIDLobbyDependent);
		void(__fastcall* CheckForPSNGameBootInvite)(ISteamMatchmaking*, unsigned int iGameBootAttributes);
	};

	struct ISteamMatchmaking
	{
		ISteamMatchmaking_vtbl* __vftable;
	};

	struct ISteamMatchmakingServerListResponse_vtbl
	{
		void(__fastcall* ServerResponded)(ISteamMatchmakingServerListResponse*, HServerListRequest hRequest, int iServer);
		void(__fastcall* ServerFailedToRespond)(ISteamMatchmakingServerListResponse*, HServerListRequest hRequest, int iServer);
		void(__fastcall* RefreshComplete)(ISteamMatchmakingServerListResponse*, HServerListRequest hRequest, EMatchMakingServerResponse response);
	};

	struct ISteamMatchmakingServerListResponse
	{
		ISteamMatchmakingServerListResponse_vtbl* __vftable;
	};

	struct ISteamMatchmakingPingResponse_vtbl
	{
		void(__fastcall* ServerResponded)(ISteamMatchmakingPingResponse*, gameserveritem_t& server);
		void(__fastcall* ServerFailedToRespond)(ISteamMatchmakingPingResponse*);
	};

	struct ISteamMatchmakingPingResponse
	{
		ISteamMatchmakingPingResponse_vtbl* __vftable;
	};

	struct ISteamMatchmakingPlayersResponse_vtbl
	{
		void(__fastcall* AddPlayerToList)(ISteamMatchmakingPlayersResponse*, const char* pchName, int nScore, float flTimePlayed);
		void(__fastcall* PlayersFailedToRespond)(ISteamMatchmakingPlayersResponse*);
		void(__fastcall* PlayersRefreshComplete)(ISteamMatchmakingPlayersResponse*);
	};

	struct ISteamMatchmakingPlayersResponse
	{
		ISteamMatchmakingPlayersResponse_vtbl* __vftable;
	};

	struct ISteamMatchmakingRulesResponse_vtbl
	{
		void(__fastcall* RulesResponded)(ISteamMatchmakingRulesResponse*, const char* pchRule, const char* pchValue);
		void(__fastcall* RulesFailedToRespond)(ISteamMatchmakingRulesResponse*);
		void(__fastcall* RulesRefreshComplete)(ISteamMatchmakingRulesResponse*);
	};

	struct ISteamMatchmakingRulesResponse
	{
		ISteamMatchmakingRulesResponse_vtbl* __vftable;
	};

	struct ISteamMatchmakingServers_vtbl
	{
		HServerListRequest(__fastcall* RequestInternetServerList)(ISteamMatchmakingServers*, AppId_t iApp, MatchMakingKeyValuePair_t** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse* pRequestServersResponse);
		HServerListRequest(__fastcall* RequestLANServerList)(ISteamMatchmakingServers*, AppId_t iApp, ISteamMatchmakingServerListResponse* pRequestServersResponse);
		HServerListRequest(__fastcall* RequestFriendsServerList)(ISteamMatchmakingServers*, AppId_t iApp, MatchMakingKeyValuePair_t** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse* pRequestServersResponse);
		HServerListRequest(__fastcall* RequestFavoritesServerList)(ISteamMatchmakingServers*, AppId_t iApp, MatchMakingKeyValuePair_t** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse* pRequestServersResponse);
		HServerListRequest(__fastcall* RequestHistoryServerList)(ISteamMatchmakingServers*, AppId_t iApp, MatchMakingKeyValuePair_t** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse* pRequestServersResponse);
		HServerListRequest(__fastcall* RequestSpectatorServerList)(ISteamMatchmakingServers*, AppId_t iApp, MatchMakingKeyValuePair_t** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse* pRequestServersResponse);
		void(__fastcall* ReleaseRequest)(ISteamMatchmakingServers*, HServerListRequest hServerListRequest);
		gameserveritem_t* (__fastcall* GetServerDetails)(ISteamMatchmakingServers*, HServerListRequest hRequest, int iServer);
		void(__fastcall* CancelQuery)(ISteamMatchmakingServers*, HServerListRequest hRequest);
		void(__fastcall* RefreshQuery)(ISteamMatchmakingServers*, HServerListRequest hRequest);
		bool(__fastcall* IsRefreshing)(ISteamMatchmakingServers*, HServerListRequest hRequest);
		int(__fastcall* GetServerCount)(ISteamMatchmakingServers*, HServerListRequest hRequest);
		void(__fastcall* RefreshServer)(ISteamMatchmakingServers*, HServerListRequest hRequest, int iServer);
		HServerQuery(__fastcall* PingServer)(ISteamMatchmakingServers*, uint32 unIP, uint16 usPort, ISteamMatchmakingPingResponse* pRequestServersResponse);
		HServerQuery(__fastcall* PlayerDetails)(ISteamMatchmakingServers*, uint32 unIP, uint16 usPort, ISteamMatchmakingPlayersResponse* pRequestServersResponse);
		HServerQuery(__fastcall* ServerRules)(ISteamMatchmakingServers*, uint32 unIP, uint16 usPort, ISteamMatchmakingRulesResponse* pRequestServersResponse);
		void(__fastcall* CancelServerQuery)(ISteamMatchmakingServers*, HServerQuery hServerQuery);
	};

	struct ISteamMatchmakingServers
	{
		ISteamMatchmakingServers_vtbl* __vftable;
	};

	struct ISteamMusic_vtbl
	{
		bool(__fastcall* BIsEnabled)(ISteamMusic*);
		bool(__fastcall* BIsPlaying)(ISteamMusic*);
		AudioPlayback_Status(__fastcall* GetPlaybackStatus)(ISteamMusic*);
		void(__fastcall* Play)(ISteamMusic*);
		void(__fastcall* Pause)(ISteamMusic*);
		void(__fastcall* PlayPrevious)(ISteamMusic*);
		void(__fastcall* PlayNext)(ISteamMusic*);
		void(__fastcall* SetVolume)(ISteamMusic*, float flVolume);
		float(__fastcall* GetVolume)(ISteamMusic*);
	};

	struct ISteamMusic
	{
		ISteamMusic_vtbl* __vftable;
	};

	struct ISteamMusicRemote_vtbl
	{
		bool(__fastcall* RegisterSteamMusicRemote)(ISteamMusicRemote*, const char* pchName);
		bool(__fastcall* DeregisterSteamMusicRemote)(ISteamMusicRemote*);
		bool(__fastcall* BIsCurrentMusicRemote)(ISteamMusicRemote*);
		bool(__fastcall* BActivationSuccess)(ISteamMusicRemote*, bool bValue);
		bool(__fastcall* SetDisplayName)(ISteamMusicRemote*, const char* pchDisplayName);
		bool(__fastcall* SetPNGIcon_64x64)(ISteamMusicRemote*, void* pvBuffer, uint32 cbBufferLength);
		bool(__fastcall* EnablePlayPrevious)(ISteamMusicRemote*, bool bValue);
		bool(__fastcall* EnablePlayNext)(ISteamMusicRemote*, bool bValue);
		bool(__fastcall* EnableShuffled)(ISteamMusicRemote*, bool bValue);
		bool(__fastcall* EnableLooped)(ISteamMusicRemote*, bool bValue);
		bool(__fastcall* EnableQueue)(ISteamMusicRemote*, bool bValue);
		bool(__fastcall* EnablePlaylists)(ISteamMusicRemote*, bool bValue);
		bool(__fastcall* UpdatePlaybackStatus)(ISteamMusicRemote*, AudioPlayback_Status nStatus);
		bool(__fastcall* UpdateShuffled)(ISteamMusicRemote*, bool bValue);
		bool(__fastcall* UpdateLooped)(ISteamMusicRemote*, bool bValue);
		bool(__fastcall* UpdateVolume)(ISteamMusicRemote*, float flValue);
		bool(__fastcall* CurrentEntryWillChange)(ISteamMusicRemote*);
		bool(__fastcall* CurrentEntryIsAvailable)(ISteamMusicRemote*, bool bAvailable);
		bool(__fastcall* UpdateCurrentEntryText)(ISteamMusicRemote*, const char* pchText);
		bool(__fastcall* UpdateCurrentEntryElapsedSeconds)(ISteamMusicRemote*, int nValue);
		bool(__fastcall* UpdateCurrentEntryCoverArt)(ISteamMusicRemote*, void* pvBuffer, uint32 cbBufferLength);
		bool(__fastcall* CurrentEntryDidChange)(ISteamMusicRemote*);
		bool(__fastcall* QueueWillChange)(ISteamMusicRemote*);
		bool(__fastcall* ResetQueueEntries)(ISteamMusicRemote*);
		bool(__fastcall* SetQueueEntry)(ISteamMusicRemote*, int nID, int nPosition, const char* pchEntryText);
		bool(__fastcall* SetCurrentQueueEntry)(ISteamMusicRemote*, int nID);
		bool(__fastcall* QueueDidChange)(ISteamMusicRemote*);
		bool(__fastcall* PlaylistWillChange)(ISteamMusicRemote*);
		bool(__fastcall* ResetPlaylistEntries)(ISteamMusicRemote*);
		bool(__fastcall* SetPlaylistEntry)(ISteamMusicRemote*, int nID, int nPosition, const char* pchEntryText);
		bool(__fastcall* SetCurrentPlaylistEntry)(ISteamMusicRemote*, int nID);
		bool(__fastcall* PlaylistDidChange)(ISteamMusicRemote*);
	};

	struct ISteamMusicRemote
	{
		ISteamMusicRemote_vtbl* __vftable;
	};

	struct ISteamNetworking_vtbl
	{
		bool(__fastcall* SendP2PPacket)(ISteamNetworking*, steam_id steamIDRemote, const void* pubData, uint32 cubData, EP2PSend eP2PSendType, int nChannel);
		bool(__fastcall* IsP2PPacketAvailable)(ISteamNetworking*, uint32* pcubMsgSize, int nChannel);
		bool(__fastcall* ReadP2PPacket)(ISteamNetworking*, void* pubDest, uint32 cubDest, uint32* pcubMsgSize, steam_id* psteamIDRemote, int nChannel);
		bool(__fastcall* AcceptP2PSessionWithUser)(ISteamNetworking*, steam_id steamIDRemote);
		bool(__fastcall* CloseP2PSessionWithUser)(ISteamNetworking*, steam_id steamIDRemote);
		bool(__fastcall* CloseP2PChannelWithUser)(ISteamNetworking*, steam_id steamIDRemote, int nChannel);
		bool(__fastcall* GetP2PSessionState)(ISteamNetworking*, steam_id steamIDRemote, P2PSessionState_t* pConnectionState);
		bool(__fastcall* AllowP2PPacketRelay)(ISteamNetworking*, bool bAllow);
		SNetListenSocket_t(__fastcall* CreateListenSocket)(ISteamNetworking*, int nVirtualP2PPort, uint32 nIP, uint16 nPort, bool bAllowUseOfPacketRelay);
		SNetSocket_t(__fastcall* CreateP2PConnectionSocket)(ISteamNetworking*, steam_id steamIDTarget, int nVirtualPort, int nTimeoutSec, bool bAllowUseOfPacketRelay);
		SNetSocket_t(__fastcall* CreateConnectionSocket)(ISteamNetworking*, uint32 nIP, uint16 nPort, int nTimeoutSec);
		bool(__fastcall* DestroySocket)(ISteamNetworking*, SNetSocket_t hSocket, bool bNotifyRemoteEnd);
		bool(__fastcall* DestroyListenSocket)(ISteamNetworking*, SNetListenSocket_t hSocket, bool bNotifyRemoteEnd);
		bool(__fastcall* SendDataOnSocket)(ISteamNetworking*, SNetSocket_t hSocket, void* pubData, uint32 cubData, bool bReliable);
		bool(__fastcall* IsDataAvailableOnSocket)(ISteamNetworking*, SNetSocket_t hSocket, uint32* pcubMsgSize);
		bool(__fastcall* RetrieveDataFromSocket)(ISteamNetworking*, SNetSocket_t hSocket, void* pubDest, uint32 cubDest, uint32* pcubMsgSize);
		bool(__fastcall* IsDataAvailable)(ISteamNetworking*, SNetListenSocket_t hListenSocket, uint32* pcubMsgSize, SNetSocket_t* phSocket);
		bool(__fastcall* RetrieveData)(ISteamNetworking*, SNetListenSocket_t hListenSocket, void* pubDest, uint32 cubDest, uint32* pcubMsgSize, SNetSocket_t* phSocket);
		bool(__fastcall* GetSocketInfo)(ISteamNetworking*, SNetSocket_t hSocket, steam_id* pSteamIDRemote, int* peSocketStatus, uint32* punIPRemote, uint16* punPortRemote);
		bool(__fastcall* GetListenSocketInfo)(ISteamNetworking*, SNetListenSocket_t hListenSocket, uint32* pnIP, uint16* pnPort);
		ESNetSocketConnectionType(__fastcall* GetSocketConnectionType)(ISteamNetworking*, SNetSocket_t hSocket);
		int(__fastcall* GetMaxPacketSize)(ISteamNetworking*, SNetSocket_t hSocket);
	};

	struct ISteamNetworking
	{
		ISteamNetworking_vtbl* __vftable;
	};

	struct ISteamPS3OverlayRenderHost_vtbl
	{
		void(__fastcall* DrawTexturedRect)(ISteamPS3OverlayRenderHost*, int x0, int y0, int x1, int y1, float u0, float v0, float u1, float v1, int32 iTextureID, DWORD colorStart, DWORD colorEnd, EOverlayGradientDirection eDirection);
		void(__fastcall* LoadOrUpdateTexture)(ISteamPS3OverlayRenderHost*, int32 iTextureID, bool bIsFullTexture, int x0, int y0, uint32 uWidth, uint32 uHeight, int32 iBytes, char* pData);
		void(__fastcall* DeleteTexture)(ISteamPS3OverlayRenderHost*, int32 iTextureID);
		void(__fastcall* DeleteAllTextures)(ISteamPS3OverlayRenderHost*);
	};

	struct ISteamPS3OverlayRenderHost
	{
		ISteamPS3OverlayRenderHost_vtbl* __vftable;
	};

	struct ISteamPS3OverlayRender_vtbl
	{
		bool(__fastcall* BHostInitialize)(ISteamPS3OverlayRender*, uint32 unScreenWidth, uint32 unScreenHeight, uint32 unRefreshRate, ISteamPS3OverlayRenderHost* pRenderHost, void* CellFontLib);
		void(__fastcall* Render)(ISteamPS3OverlayRender*);
		bool(__fastcall* BHandleCellPadData)(ISteamPS3OverlayRender*, const CellPadData& padData);
		bool(__fastcall* BResetInputState)(ISteamPS3OverlayRender*);
	};

	struct ISteamPS3OverlayRender
	{
		ISteamPS3OverlayRender_vtbl* __vftable;
	};

	struct ISteamRemoteStorage_vtbl
	{
		bool(__fastcall* FileWrite)(ISteamRemoteStorage*, const char* pchFile, const void* pvData, int32 cubData);
		int32(__fastcall* FileRead)(ISteamRemoteStorage*, const char* pchFile, void* pvData, int32 cubDataToRead);
		SteamAPICall_t(__fastcall* FileWriteAsync)(ISteamRemoteStorage*, const char* pchFile, const void* pvData, uint32 cubData);
		SteamAPICall_t(__fastcall* FileReadAsync)(ISteamRemoteStorage*, const char* pchFile, uint32 nOffset, uint32 cubToRead);
		bool(__fastcall* FileReadAsyncComplete)(ISteamRemoteStorage*, SteamAPICall_t hReadCall, void* pvBuffer, uint32 cubToRead);
		bool(__fastcall* FileForget)(ISteamRemoteStorage*, const char* pchFile);
		bool(__fastcall* FileDelete)(ISteamRemoteStorage*, const char* pchFile);
		SteamAPICall_t(__fastcall* FileShare)(ISteamRemoteStorage*, const char* pchFile);
		bool(__fastcall* SetSyncPlatforms)(ISteamRemoteStorage*, const char* pchFile, ERemoteStoragePlatform eRemoteStoragePlatform);
		UGCFileWriteStreamHandle_t(__fastcall* FileWriteStreamOpen)(ISteamRemoteStorage*, const char* pchFile);
		bool(__fastcall* FileWriteStreamWriteChunk)(ISteamRemoteStorage*, UGCFileWriteStreamHandle_t writeHandle, const void* pvData, int32 cubData);
		bool(__fastcall* FileWriteStreamClose)(ISteamRemoteStorage*, UGCFileWriteStreamHandle_t writeHandle);
		bool(__fastcall* FileWriteStreamCancel)(ISteamRemoteStorage*, UGCFileWriteStreamHandle_t writeHandle);
		bool(__fastcall* FileExists)(ISteamRemoteStorage*, const char* pchFile);
		bool(__fastcall* FilePersisted)(ISteamRemoteStorage*, const char* pchFile);
		int32(__fastcall* GetFileSize)(ISteamRemoteStorage*, const char* pchFile);
		int64(__fastcall* GetFileTimestamp)(ISteamRemoteStorage*, const char* pchFile);
		ERemoteStoragePlatform(__fastcall* GetSyncPlatforms)(ISteamRemoteStorage*, const char* pchFile);
		int32(__fastcall* GetFileCount)(ISteamRemoteStorage*);
		const char* (__fastcall* GetFileNameAndSize)(ISteamRemoteStorage*, int iFile, int32* pnFileSizeInBytes);
		bool(__fastcall* GetQuota)(ISteamRemoteStorage*, int32* pnTotalBytes, int32* puAvailableBytes);
		bool(__fastcall* IsCloudEnabledForAccount)(ISteamRemoteStorage*);
		bool(__fastcall* IsCloudEnabledForApp)(ISteamRemoteStorage*);
		void(__fastcall* SetCloudEnabledForApp)(ISteamRemoteStorage*, bool bEnabled);
		SteamAPICall_t(__fastcall* UGCDownload)(ISteamRemoteStorage*, UGCHandle_t hContent, uint32 unPriority);
		bool(__fastcall* GetUGCDownloadProgress)(ISteamRemoteStorage*, UGCHandle_t hContent, int32* pnBytesDownloaded, int32* pnBytesExpected);
		bool(__fastcall* GetUGCDetails)(ISteamRemoteStorage*);
		int32(__fastcall* UGCRead)(ISteamRemoteStorage*, UGCHandle_t hContent, void* pvData, int32 cubDataToRead, uint32 cOffset, EUGCReadAction eAction);
		int32(__fastcall* GetCachedUGCCount)(ISteamRemoteStorage*);
		UGCHandle_t(__fastcall* GetCachedUGCHandle)(ISteamRemoteStorage*, int32 iCachedContent);
		void(__fastcall* GetFileListFromServer)(ISteamRemoteStorage*);
		bool(__fastcall* FileFetch)(ISteamRemoteStorage*, const char* pchFile);
		bool(__fastcall* FilePersist)(ISteamRemoteStorage*, const char* pchFile);
		bool(__fastcall* SynchronizeToClient)(ISteamRemoteStorage*);
		bool(__fastcall* SynchronizeToServer)(ISteamRemoteStorage*);
		bool(__fastcall* ResetFileRequestState)(ISteamRemoteStorage*);
		SteamAPICall_t(__fastcall* PublishWorkshopFile)(ISteamRemoteStorage*, const char* pchFile, const char* pchPreviewFile, AppId_t nConsumerAppId, const char* pchTitle, const char* pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t* pTags, EWorkshopFileType eWorkshopFileType);
		PublishedFileUpdateHandle_t(__fastcall* CreatePublishedFileUpdateRequest)(ISteamRemoteStorage*, PublishedFileId_t unPublishedFileId);
		bool(__fastcall* UpdatePublishedFileFile)(ISteamRemoteStorage*, PublishedFileUpdateHandle_t updateHandle, const char* pchFile);
		bool(__fastcall* UpdatePublishedFilePreviewFile)(ISteamRemoteStorage*, PublishedFileUpdateHandle_t updateHandle, const char* pchPreviewFile);
		bool(__fastcall* UpdatePublishedFileTitle)(ISteamRemoteStorage*, PublishedFileUpdateHandle_t updateHandle, const char* pchTitle);
		bool(__fastcall* UpdatePublishedFileDescription)(ISteamRemoteStorage*, PublishedFileUpdateHandle_t updateHandle, const char* pchDescription);
		bool(__fastcall* UpdatePublishedFileVisibility)(ISteamRemoteStorage*, PublishedFileUpdateHandle_t updateHandle, ERemoteStoragePublishedFileVisibility eVisibility);
		bool(__fastcall* UpdatePublishedFileTags)(ISteamRemoteStorage*, PublishedFileUpdateHandle_t updateHandle, SteamParamStringArray_t* pTags);
		SteamAPICall_t(__fastcall* CommitPublishedFileUpdate)(ISteamRemoteStorage*, PublishedFileUpdateHandle_t updateHandle);
		SteamAPICall_t(__fastcall* GetPublishedFileDetails)(ISteamRemoteStorage*, PublishedFileId_t unPublishedFileId, uint32 unMaxSecondsOld);
		SteamAPICall_t(__fastcall* DeletePublishedFile)(ISteamRemoteStorage*, PublishedFileId_t unPublishedFileId);
		SteamAPICall_t(__fastcall* EnumerateUserPublishedFiles)(ISteamRemoteStorage*, uint32 unStartIndex);
		SteamAPICall_t(__fastcall* SubscribePublishedFile)(ISteamRemoteStorage*, PublishedFileId_t unPublishedFileId);
		SteamAPICall_t(__fastcall* EnumerateUserSubscribedFiles)(ISteamRemoteStorage*, uint32 unStartIndex);
		SteamAPICall_t(__fastcall* UnsubscribePublishedFile)(ISteamRemoteStorage*, PublishedFileId_t unPublishedFileId);
		bool(__fastcall* UpdatePublishedFileSetChangeDescription)(ISteamRemoteStorage*, PublishedFileUpdateHandle_t updateHandle, const char* pchChangeDescription);
		SteamAPICall_t(__fastcall* GetPublishedItemVoteDetails)(ISteamRemoteStorage*, PublishedFileId_t unPublishedFileId);
		SteamAPICall_t(__fastcall* UpdateUserPublishedItemVote)(ISteamRemoteStorage*, PublishedFileId_t unPublishedFileId, bool bVoteUp);
		SteamAPICall_t(__fastcall* GetUserPublishedItemVoteDetails)(ISteamRemoteStorage*, PublishedFileId_t unPublishedFileId);
		SteamAPICall_t(__fastcall* EnumerateUserSharedWorkshopFiles)(ISteamRemoteStorage*, steam_id steamId, uint32 unStartIndex, SteamParamStringArray_t* pRequiredTags, SteamParamStringArray_t* pExcludedTags);
		SteamAPICall_t(__fastcall* PublishVideo)(ISteamRemoteStorage*, EWorkshopVideoProvider eVideoProvider, const char* pchVideoAccount, const char* pchVideoIdentifier, const char* pchPreviewFile, AppId_t nConsumerAppId, const char* pchTitle, const char* pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t* pTags);
		SteamAPICall_t(__fastcall* SetUserPublishedFileAction)(ISteamRemoteStorage*, PublishedFileId_t unPublishedFileId, EWorkshopFileAction eAction);
		SteamAPICall_t(__fastcall* EnumeratePublishedFilesByUserAction)(ISteamRemoteStorage*, EWorkshopFileAction eAction, uint32 unStartIndex);
		SteamAPICall_t(__fastcall* EnumeratePublishedWorkshopFiles)(ISteamRemoteStorage*, EWorkshopEnumerationType eEnumerationType, uint32 unStartIndex, uint32 unCount, uint32 unDays, SteamParamStringArray_t* pTags, SteamParamStringArray_t* pUserTags);
		SteamAPICall_t(__fastcall* UGCDownloadToLocation)(ISteamRemoteStorage*, UGCHandle_t hContent, const char* pchLocation, uint32 unPriority);
	};

	struct ISteamRemoteStorage
	{
		ISteamRemoteStorage_vtbl* __vftable;
	};

	struct ISteamScreenshots_vtbl
	{
		ScreenshotHandle(__fastcall* WriteScreenshot)(ISteamScreenshots*, void* pubRGB, uint32 cubRGB, int nWidth, int nHeight);
		ScreenshotHandle(__fastcall* AddScreenshotToLibrary)(ISteamScreenshots*, const char* pchFilename, const char* pchThumbnailFilename, int nWidth, int nHeight);
		void(__fastcall* TriggerScreenshot)(ISteamScreenshots*);
		void(__fastcall* HookScreenshots)(ISteamScreenshots*, bool bHook);
		bool(__fastcall* SetLocation)(ISteamScreenshots*, ScreenshotHandle hScreenshot, const char* pchLocation);
		bool(__fastcall* TagUser)(ISteamScreenshots*, ScreenshotHandle hScreenshot, steam_id steamID);
		bool(__fastcall* TagPublishedFile)(ISteamScreenshots*, ScreenshotHandle hScreenshot, PublishedFileId_t unPublishedFileID);
	};

	struct ISteamScreenshots
	{
		ISteamScreenshots_vtbl* __vftable;
	};

	struct ISteamUGC_vtbl
	{
		UGCQueryHandle_t(__fastcall* CreateQueryUserUGCRequest)(ISteamUGC*, AccountID_t unAccountID, EUserUGCList eListType, EUGCMatchingUGCType eMatchingUGCType, EUserUGCListSortOrder eSortOrder, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage);
		UGCQueryHandle_t(__fastcall* CreateQueryAllUGCRequest)(ISteamUGC*, EUGCQuery eQueryType, EUGCMatchingUGCType eMatchingeMatchingUGCTypeFileType, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage);
		UGCQueryHandle_t(__fastcall* CreateQueryUGCDetailsRequest)(ISteamUGC*, PublishedFileId_t* pvecPublishedFileID, uint32 unNumPublishedFileIDs);
		SteamAPICall_t(__fastcall* SendQueryUGCRequest)(ISteamUGC*, UGCQueryHandle_t handle);
		bool(__fastcall* GetQueryUGCResult)(ISteamUGC*, UGCQueryHandle_t handle, uint32 index, SteamUGCDetails_t* pDetails);
		bool(__fastcall* GetQueryUGCPreviewURL)(ISteamUGC*, UGCQueryHandle_t handle, uint32 index, char* pchURL, uint32 cchURLSize);
		bool(__fastcall* GetQueryUGCMetadata)(ISteamUGC*, UGCQueryHandle_t handle, uint32 index, char* pchMetadata, uint32 cchMetadatasize);
		bool(__fastcall* GetQueryUGCChildren)(ISteamUGC*, UGCQueryHandle_t handle, uint32 index, PublishedFileId_t* pvecPublishedFileID, uint32 cMaxEntries);
		bool(__fastcall* GetQueryUGCStatistic)(ISteamUGC*, UGCQueryHandle_t handle, uint32 index, EItemStatistic eStatType, uint32* pStatValue);
		uint32(__fastcall* GetQueryUGCNumAdditionalPreviews)(ISteamUGC*, UGCQueryHandle_t handle, uint32 index);
		bool(__fastcall* GetQueryUGCAdditionalPreview)(ISteamUGC*, UGCQueryHandle_t handle, uint32 index, uint32 previewIndex, char* pchURLOrVideoID, uint32 cchURLSize, char* pchOriginalFileName, uint32 cchOriginalFileNameSize, EItemPreviewType* pPreviewType);
		uint32(__fastcall* GetQueryUGCNumKeyValueTags)(ISteamUGC*, UGCQueryHandle_t handle, uint32 index);
		bool(__fastcall* GetQueryUGCKeyValueTag)(ISteamUGC*, UGCQueryHandle_t handle, uint32 index, uint32 keyValueTagIndex, char* pchKey, uint32 cchKeySize, char* pchValue, uint32 cchValueSize);
		bool(__fastcall* ReleaseQueryUGCRequest)(ISteamUGC*, UGCQueryHandle_t handle);
		bool(__fastcall* AddRequiredTag)(ISteamUGC*, UGCQueryHandle_t handle, const char* pTagName);
		bool(__fastcall* AddExcludedTag)(ISteamUGC*, UGCQueryHandle_t handle, const char* pTagName);
		bool(__fastcall* SetReturnKeyValueTags)(ISteamUGC*, UGCQueryHandle_t handle, bool bReturnKeyValueTags);
		bool(__fastcall* SetReturnLongDescription)(ISteamUGC*, UGCQueryHandle_t handle, bool bReturnLongDescription);
		bool(__fastcall* SetReturnMetadata)(ISteamUGC*, UGCQueryHandle_t handle, bool bReturnMetadata);
		bool(__fastcall* SetReturnChildren)(ISteamUGC*, UGCQueryHandle_t handle, bool bReturnChildren);
		bool(__fastcall* SetReturnAdditionalPreviews)(ISteamUGC*, UGCQueryHandle_t handle, bool bReturnAdditionalPreviews);
		bool(__fastcall* SetReturnTotalOnly)(ISteamUGC*, UGCQueryHandle_t handle, bool bReturnTotalOnly);
		bool(__fastcall* SetLanguage)(ISteamUGC*, UGCQueryHandle_t handle, const char* pchLanguage);
		bool(__fastcall* SetAllowCachedResponse)(ISteamUGC*, UGCQueryHandle_t handle, uint32 unMaxAgeSeconds);
		bool(__fastcall* SetCloudFileNameFilter)(ISteamUGC*, UGCQueryHandle_t handle, const char* pMatchCloudFileName);
		bool(__fastcall* SetMatchAnyTag)(ISteamUGC*, UGCQueryHandle_t handle, bool bMatchAnyTag);
		bool(__fastcall* SetSearchText)(ISteamUGC*, UGCQueryHandle_t handle, const char* pSearchText);
		bool(__fastcall* SetRankedByTrendDays)(ISteamUGC*, UGCQueryHandle_t handle, uint32 unDays);
		bool(__fastcall* AddRequiredKeyValueTag)(ISteamUGC*, UGCQueryHandle_t handle, const char* pKey, const char* pValue);
		SteamAPICall_t(__fastcall* RequestUGCDetails)(ISteamUGC*, PublishedFileId_t nPublishedFileID, uint32 unMaxAgeSeconds);
		SteamAPICall_t(__fastcall* CreateItem)(ISteamUGC*, AppId_t nConsumerAppId, EWorkshopFileType eFileType);
		UGCUpdateHandle_t(__fastcall* StartItemUpdate)(ISteamUGC*, AppId_t nConsumerAppId, PublishedFileId_t nPublishedFileID);
		bool(__fastcall* SetItemTitle)(ISteamUGC*, UGCUpdateHandle_t handle, const char* pchTitle);
		bool(__fastcall* SetItemDescription)(ISteamUGC*, UGCUpdateHandle_t handle, const char* pchDescription);
		bool(__fastcall* SetItemUpdateLanguage)(ISteamUGC*, UGCUpdateHandle_t handle, const char* pchLanguage);
		bool(__fastcall* SetItemMetadata)(ISteamUGC*, UGCUpdateHandle_t handle, const char* pchMetaData);
		bool(__fastcall* SetItemVisibility)(ISteamUGC*, UGCUpdateHandle_t handle, ERemoteStoragePublishedFileVisibility eVisibility);
		bool(__fastcall* SetItemTags)(ISteamUGC*, UGCUpdateHandle_t updateHandle, const SteamParamStringArray_t* pTags);
		bool(__fastcall* SetItemContent)(ISteamUGC*, UGCUpdateHandle_t handle, const char* pszContentFolder);
		bool(__fastcall* SetItemPreview)(ISteamUGC*, UGCUpdateHandle_t handle, const char* pszPreviewFile);
		bool(__fastcall* RemoveItemKeyValueTags)(ISteamUGC*, UGCUpdateHandle_t handle, const char* pchKey);
		bool(__fastcall* AddItemKeyValueTag)(ISteamUGC*, UGCUpdateHandle_t handle, const char* pchKey, const char* pchValue);
		bool(__fastcall* AddItemPreviewFile)(ISteamUGC*, UGCUpdateHandle_t handle, const char* pszPreviewFile, EItemPreviewType type);
		bool(__fastcall* AddItemPreviewVideo)(ISteamUGC*, UGCUpdateHandle_t handle, const char* pszVideoID);
		bool(__fastcall* UpdateItemPreviewFile)(ISteamUGC*, UGCUpdateHandle_t handle, uint32 index, const char* pszPreviewFile);
		bool(__fastcall* UpdateItemPreviewVideo)(ISteamUGC*, UGCUpdateHandle_t handle, uint32 index, const char* pszVideoID);
		bool(__fastcall* RemoveItemPreview)(ISteamUGC*, UGCUpdateHandle_t handle, uint32 index);
		SteamAPICall_t(__fastcall* SubmitItemUpdate)(ISteamUGC*, UGCUpdateHandle_t handle, const char* pchChangeNote);
		EItemUpdateStatus(__fastcall* GetItemUpdateProgress)(ISteamUGC*, UGCUpdateHandle_t handle, uint64* punBytesProcessed, uint64* punBytesTotal);
		SteamAPICall_t(__fastcall* SetUserItemVote)(ISteamUGC*, PublishedFileId_t nPublishedFileID, bool bVoteUp);
		SteamAPICall_t(__fastcall* GetUserItemVote)(ISteamUGC*, PublishedFileId_t nPublishedFileID);
		SteamAPICall_t(__fastcall* AddItemToFavorites)(ISteamUGC*, AppId_t nAppId, PublishedFileId_t nPublishedFileID);
		SteamAPICall_t(__fastcall* RemoveItemFromFavorites)(ISteamUGC*, AppId_t nAppId, PublishedFileId_t nPublishedFileID);
		SteamAPICall_t(__fastcall* SubscribeItem)(ISteamUGC*, PublishedFileId_t nPublishedFileID);
		SteamAPICall_t(__fastcall* UnsubscribeItem)(ISteamUGC*, PublishedFileId_t nPublishedFileID);
		uint32(__fastcall* GetNumSubscribedItems)(ISteamUGC*);
		uint32(__fastcall* GetSubscribedItems)(ISteamUGC*, PublishedFileId_t* pvecPublishedFileID, uint32 cMaxEntries);
		uint32(__fastcall* GetItemState)(ISteamUGC*, PublishedFileId_t nPublishedFileID);
		bool(__fastcall* GetItemInstallInfo)(ISteamUGC*, PublishedFileId_t nPublishedFileID, uint64* punSizeOnDisk, char* pchFolder, uint32 cchFolderSize, uint32* punTimeStamp);
		bool(__fastcall* GetItemDownloadInfo)(ISteamUGC*, PublishedFileId_t nPublishedFileID, uint64* punBytesDownloaded, uint64* punBytesTotal);
		bool(__fastcall* DownloadItem)(ISteamUGC*, PublishedFileId_t nPublishedFileID, bool bHighPriority);
		bool(__fastcall* BInitWorkshopForGameServer)(ISteamUGC*, DepotId_t unWorkshopDepotID, const char* pszFolder);
		void(__fastcall* SuspendDownloads)(ISteamUGC*, bool bSuspend);
	};

	struct ISteamUGC
	{
		ISteamUGC_vtbl* __vftable;
	};

	struct ISteamUnifiedMessages_vtbl
	{
		ClientUnifiedMessageHandle(__fastcall* SendMethod)(ISteamUnifiedMessages*, const char* pchServiceMethod, const void* pRequestBuffer, uint32 unRequestBufferSize, uint64 unContext);
		bool(__fastcall* GetMethodResponseInfo)(ISteamUnifiedMessages*, ClientUnifiedMessageHandle hHandle, uint32* punResponseSize, EResult* peResult);
		bool(__fastcall* GetMethodResponseData)(ISteamUnifiedMessages*, ClientUnifiedMessageHandle hHandle, void* pResponseBuffer, uint32 unResponseBufferSize, bool bAutoRelease);
		bool(__fastcall* ReleaseMethod)(ISteamUnifiedMessages*, ClientUnifiedMessageHandle hHandle);
		bool(__fastcall* SendNotification)(ISteamUnifiedMessages*, const char* pchServiceNotification, const void* pNotificationBuffer, uint32 unNotificationBufferSize);
	};

	struct ISteamUnifiedMessages
	{
		ISteamUnifiedMessages_vtbl* __vftable;
	};

	struct ISteamUser_vtbl
	{
		HSteamUser(__fastcall* GetHSteamUser)(ISteamUser*);
		bool(__fastcall* BLoggedOn)(ISteamUser*);
		steam_id*(__fastcall* GetSteamID)(ISteamUser*, steam_id*);
		int(__fastcall* InitiateGameConnection)(ISteamUser*, void* pAuthBlob, int cbMaxAuthBlob, steam_id steamIDGameServer, uint32 unIPServer, uint16 usPortServer, bool bSecure);
		void(__fastcall* TerminateGameConnection)(ISteamUser*, uint32 unIPServer, uint16 usPortServer);
		void(__fastcall* TrackAppUsageEvent)(ISteamUser*, CGameID gameID, int eAppUsageEvent, const char* pchExtraInfo);
		bool(__fastcall* GetUserDataFolder)(ISteamUser*, char* pchBuffer, int cubBuffer);
		void(__fastcall* StartVoiceRecording)(ISteamUser*);
		void(__fastcall* StopVoiceRecording)(ISteamUser*);
		EVoiceResult(__fastcall* GetAvailableVoice)(ISteamUser*, uint32* pcbCompressed, uint32* pcbUncompressed, uint32 nUncompressedVoiceDesiredSampleRate);
		EVoiceResult(__fastcall* GetVoice)(ISteamUser*, bool bWantCompressed, void* pDestBuffer, uint32 cbDestBufferSize, uint32* nBytesWritten, bool bWantUncompressed, void* pUncompressedDestBuffer, uint32 cbUncompressedDestBufferSize, uint32* nUncompressBytesWritten, uint32 nUncompressedVoiceDesiredSampleRate);
		EVoiceResult(__fastcall* DecompressVoice)(ISteamUser*, const void* pCompressed, uint32 cbCompressed, void* pDestBuffer, uint32 cbDestBufferSize, uint32* nBytesWritten, uint32 nDesiredSampleRate);
		uint32(__fastcall* GetVoiceOptimalSampleRate)(ISteamUser*);
		HAuthTicket(__fastcall* GetAuthSessionTicket)(ISteamUser*, void* pTicket, int cbMaxTicket, uint32* pcbTicket);
		EBeginAuthSessionResult(__fastcall* BeginAuthSession)(ISteamUser*, const void* pAuthTicket, int cbAuthTicket, steam_id steamID);
		void(__fastcall* EndAuthSession)(ISteamUser*, steam_id steamID);
		void(__fastcall* CancelAuthTicket)(ISteamUser*, HAuthTicket hAuthTicket);
		EUserHasLicenseForAppResult(__fastcall* UserHasLicenseForApp)(ISteamUser*, steam_id steamID, AppId_t appID);
		bool(__fastcall* BIsBehindNAT)(ISteamUser*);
		void(__fastcall* AdvertiseGame)(ISteamUser*, steam_id steamIDGameServer, uint32 unIPServer, uint16 usPortServer);
		SteamAPICall_t(__fastcall* RequestEncryptedAppTicket)(ISteamUser*, void* pDataToInclude, int cbDataToInclude);
		bool(__fastcall* GetEncryptedAppTicket)(ISteamUser*, void* pTicket, int cbMaxTicket, uint32* pcbTicket);
		int(__fastcall* GetGameBadgeLevel)(ISteamUser*, int nSeries, bool bFoil);
		int(__fastcall* GetPlayerSteamLevel)(ISteamUser*);
		SteamAPICall_t(__fastcall* RequestStoreAuthURL)(ISteamUser*, const char* pchRedirectURL);
		bool(__fastcall* BIsPhoneVerified)(ISteamUser*);
		bool(__fastcall* BIsTwoFactorEnabled)(ISteamUser*);
	};

	struct ISteamUser
	{
		ISteamUser_vtbl* __vftable;
	};

	struct ISteamUserStats_vtbl
	{
		bool(__fastcall* RequestCurrentStats)(ISteamUserStats*);
		bool(__fastcall* GetStat1)(ISteamUserStats*, const char* pchName, int32* pData);
		bool(__fastcall* GetStat2)(ISteamUserStats*, const char* pchName, float* pData);
		bool(__fastcall* SetStat1)(ISteamUserStats*, const char* pchName, int32 nData);
		bool(__fastcall* SetStat2)(ISteamUserStats*, const char* pchName, float fData);
		bool(__fastcall* UpdateAvgRateStat)(ISteamUserStats*, const char* pchName, float flCountThisSession, double dSessionLength);
		bool(__fastcall* GetAchievement)(ISteamUserStats*, const char* pchName, bool* pbAchieved);
		bool(__fastcall* SetAchievement)(ISteamUserStats*, const char* pchName);
		bool(__fastcall* ClearAchievement)(ISteamUserStats*, const char* pchName);
		bool(__fastcall* GetAchievementAndUnlockTime)(ISteamUserStats*, const char* pchName, bool* pbAchieved, uint32* punUnlockTime);
		bool(__fastcall* StoreStats)(ISteamUserStats*);
		int(__fastcall* GetAchievementIcon)(ISteamUserStats*, const char* pchName);
		const char* (__fastcall* GetAchievementDisplayAttribute)(ISteamUserStats*, const char* pchName, const char* pchKey);
		bool(__fastcall* IndicateAchievementProgress)(ISteamUserStats*, const char* pchName, uint32 nCurProgress, uint32 nMaxProgress);
		uint32(__fastcall* GetNumAchievements)(ISteamUserStats*);
		const char* (__fastcall* GetAchievementName)(ISteamUserStats*, uint32 iAchievement);
		SteamAPICall_t(__fastcall* RequestUserStats)(ISteamUserStats*, steam_id steamIDUser);
		bool(__fastcall* GetUserStat1)(ISteamUserStats*, steam_id steamIDUser, const char* pchName, int32* pData);
		bool(__fastcall* GetUserStat2)(ISteamUserStats*, steam_id steamIDUser, const char* pchName, float* pData);
		bool(__fastcall* GetUserAchievement)(ISteamUserStats*, steam_id steamIDUser, const char* pchName, bool* pbAchieved);
		bool(__fastcall* GetUserAchievementAndUnlockTime)(ISteamUserStats*, steam_id steamIDUser, const char* pchName, bool* pbAchieved, uint32* punUnlockTime);
		bool(__fastcall* ResetAllStats)(ISteamUserStats*, bool bAchievementsToo);
		SteamAPICall_t(__fastcall* FindOrCreateLeaderboard)(ISteamUserStats*, const char* pchLeaderboardName, ELeaderboardSortMethod eLeaderboardSortMethod, ELeaderboardDisplayType eLeaderboardDisplayType);
		SteamAPICall_t(__fastcall* FindLeaderboard)(ISteamUserStats*, const char* pchLeaderboardName);
		const char* (__fastcall* GetLeaderboardName)(ISteamUserStats*, SteamLeaderboard_t hSteamLeaderboard);
		int(__fastcall* GetLeaderboardEntryCount)(ISteamUserStats*, SteamLeaderboard_t hSteamLeaderboard);
		ELeaderboardSortMethod(__fastcall* GetLeaderboardSortMethod)(ISteamUserStats*, SteamLeaderboard_t hSteamLeaderboard);
		ELeaderboardDisplayType(__fastcall* GetLeaderboardDisplayType)(ISteamUserStats*, SteamLeaderboard_t hSteamLeaderboard);
		SteamAPICall_t(__fastcall* DownloadLeaderboardEntries)(ISteamUserStats*, SteamLeaderboard_t hSteamLeaderboard, ELeaderboardDataRequest eLeaderboardDataRequest, int nRangeStart, int nRangeEnd);
		bool(__fastcall* GetDownloadedLeaderboardEntry)(ISteamUserStats*, SteamLeaderboardEntries_t hSteamLeaderboardEntries, int index, LeaderboardEntry_t* pLeaderboardEntry, int32* pDetails, int cDetailsMax);
		SteamAPICall_t(__fastcall* UploadLeaderboardScore)(ISteamUserStats*, SteamLeaderboard_t hSteamLeaderboard, ELeaderboardUploadScoreMethod eLeaderboardUploadScoreMethod, int32 nScore, const int32* pScoreDetails, int cScoreDetailsCount);
		SteamAPICall_t(__fastcall* AttachLeaderboardUGC)(ISteamUserStats*, SteamLeaderboard_t hSteamLeaderboard, UGCHandle_t hUGC);
		SteamAPICall_t(__fastcall* GetNumberOfCurrentPlayers)(ISteamUserStats*);
		SteamAPICall_t(__fastcall* RequestGlobalAchievementPercentages)(ISteamUserStats*);
		int(__fastcall* GetMostAchievedAchievementInfo)(ISteamUserStats*, char* pchName, uint32 unNameBufLen, float* pflPercent, bool* pbAchieved);
		int(__fastcall* GetNextMostAchievedAchievementInfo)(ISteamUserStats*, int iIteratorPrevious, char* pchName, uint32 unNameBufLen, float* pflPercent, bool* pbAchieved);
		bool(__fastcall* GetAchievementAchievedPercent)(ISteamUserStats*, const char* pchName, float* pflPercent);
		SteamAPICall_t(__fastcall* RequestGlobalStats)(ISteamUserStats*, int nHistoryDays);
		bool(__fastcall* GetGlobalStat1)(ISteamUserStats*, const char* pchStatName, int64* pData);
		bool(__fastcall* GetGlobalStat2)(ISteamUserStats*, const char* pchStatName, double* pData);
		int32(__fastcall* GetGlobalStatHistory1)(ISteamUserStats*, const char* pchStatName, int64* pData, uint32 cubData);
		int32(__fastcall* GetGlobalStatHistory2)(ISteamUserStats*, const char* pchStatName, double* pData, uint32 cubData);
		bool(__fastcall* InstallPS3Trophies)(ISteamUserStats*);
		uint64(__fastcall* GetTrophySpaceRequiredBeforeInstall)(ISteamUserStats*);
		bool(__fastcall* SetUserStatsData)(ISteamUserStats*, const void* pvData, uint32 cubData);
		bool(__fastcall* GetUserStatsData)(ISteamUserStats*, void* pvData, uint32 cubData, uint32* pcubWritten);
	};

	struct ISteamUserStats
	{
		ISteamUserStats_vtbl* __vftable;
	};

	struct ISteamUtils_vtbl
	{
		uint32(__fastcall* GetSecondsSinceAppActive)(ISteamUtils*);
		uint32(__fastcall* GetSecondsSinceComputerActive)(ISteamUtils*);
		EUniverse(__fastcall* GetConnectedUniverse)(ISteamUtils*);
		uint32(__fastcall* GetServerRealTime)(ISteamUtils*);
		const char* (__fastcall* GetIPCountry)(ISteamUtils*);
		bool(__fastcall* GetImageSize)(ISteamUtils*, int iImage, uint32* pnWidth, uint32* pnHeight);
		bool(__fastcall* GetImageRGBA)(ISteamUtils*, int iImage, uint8* pubDest, int nDestBufferSize);
		bool(__fastcall* GetCSERIPPort)(ISteamUtils*, uint32* unIP, uint16* usPort);
		uint8(__fastcall* GetCurrentBatteryPower)(ISteamUtils*);
		uint32(__fastcall* GetAppID)(ISteamUtils*);
		void(__fastcall* SetOverlayNotificationPosition)(ISteamUtils*, ENotificationPosition eNotificationPosition);
		bool(__fastcall* IsAPICallCompleted)(ISteamUtils*, SteamAPICall_t hSteamAPICall, bool* pbFailed);
		ESteamAPICallFailure(__fastcall* GetAPICallFailureReason)(ISteamUtils*, SteamAPICall_t hSteamAPICall);
		bool(__fastcall* GetAPICallResult)(ISteamUtils*, SteamAPICall_t hSteamAPICall, void* pCallback, int cubCallback, int iCallbackExpected, bool* pbFailed);
		void(__fastcall* RunFrame)(ISteamUtils*);
		uint32(__fastcall* GetIPCCallCount)(ISteamUtils*);
		void(__fastcall* SetWarningMessageHook)(ISteamUtils*, SteamAPIWarningMessageHook_t pFunction);
		bool(__fastcall* IsOverlayEnabled)(ISteamUtils*);
		bool(__fastcall* BOverlayNeedsPresent)(ISteamUtils*);
		SteamAPICall_t(__fastcall* CheckFileSignature)(ISteamUtils*, const char* szFileName);
		bool(__fastcall* ShowGamepadTextInput)(ISteamUtils*, EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32 unCharMax, const char* pchExistingText);
		uint32(__fastcall* GetEnteredGamepadTextLength)(ISteamUtils*);
		bool(__fastcall* GetEnteredGamepadTextInput)(ISteamUtils*, char* pchText, uint32 cchText);
		const char* (__fastcall* GetSteamUILanguage)(ISteamUtils*);
		bool(__fastcall* IsSteamRunningInVR)(ISteamUtils*);
		void(__fastcall* SetOverlayNotificationInset)(ISteamUtils*, int nHorizontalInset, int nVerticalInset);
		bool(__fastcall* IsSteamInBigPictureMode)(ISteamUtils*);
		void(__fastcall* StartVRDashboard)(ISteamUtils*);
	};

	struct ISteamUtils
	{
		ISteamUtils_vtbl* __vftable;
	};

	struct ISteamVideo_vtbl
	{
		void(__fastcall* GetVideoURL)(ISteamVideo*, AppId_t unVideoAppID);
		bool(__fastcall* IsBroadcasting)(ISteamVideo*, int* pnNumViewers);
		void(__fastcall* Run1)(ISteamVideo*, void* pvParam);
		void(__fastcall* Run2)(ISteamVideo*, void* pvParam, bool bIOFailure, SteamAPICall_t hSteamAPICall);
		int(__fastcall* GetCallbackSizeBytes)(ISteamVideo*);
		void(__fastcall* Run3)(ISteamVideo*, void* pvParam);
	};

	struct ISteamVideo
	{
		ISteamVideo_vtbl* __vftable;
	};

	struct steam_interfaces_t
	{
		ISteamClient* SteamClient017;
		ISteamUser* SteamUser019;
		ISteamFriends* SteamFriends015;
		ISteamUtils* SteamUtils008;
		ISteamMatchmaking* SteamMatchMaking009;
		ISteamMatchmakingServers* SteamMatchMakingServers002;
		ISteamUserStats* SteamUserState011;
		ISteamApps* SteamApps008;
		ISteamNetworking* SteamNetworking005;
		ISteamRemoteStorage* SteamRemoteStorage013;
		ISteamScreenshots* SteamScreenshots002;
		ISteamHTTP* SteamHTTP002;
		ISteamUnifiedMessages* SteamUnifiedMessages001;
		ISteamController* SteamController003;
		ISteamUGC* SteamUGC008;
		ISteamAppList* SteamAppList001;
		ISteamMusic* SteamMusic001;
		ISteamMusicRemote* SteamMusicRemote001;
		ISteamHTMLSurface* SteamHTMLSurface003;
		ISteamInventory* SteamInventory001;
		ISteamVideo* SteamVideo001;
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
