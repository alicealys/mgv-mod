#include <std_include.hpp>

#include "base.hpp"

#include "steam_networking.hpp"

namespace steam
{
	namespace
	{
		bool is_p2p_packet_available(game::ISteamNetworking*, unsigned int* size, int channel)
		{
			return false;
		}

		bool read_p2p_packet(game::ISteamNetworking*, void* dest, unsigned int size, unsigned int* size2, game::steam_id* remote, int channel)
		{
			return false;
		}

		bool send_p2p_packet(game::ISteamNetworking*, game::steam_id remote, const void* data, unsigned int size, game::EP2PSend send_type, int channel)
		{
			return false;
		}

		bool accept_p2p_session_with_user(game::ISteamNetworking*, game::steam_id)
		{
			return false;
		}

		bool close_p2p_channel_with_user(game::ISteamNetworking*, game::steam_id, int channel)
		{
			return false;
		}

		bool close_p2p_session_with_user(game::ISteamNetworking*, game::steam_id)
		{
			return false;
		}

		bool get_p2p_session_state(game::ISteamNetworking*, game::steam_id, game::P2PSessionState_t* state)
		{
			return false;
		}
	}

	game::ISteamNetworking* steam_networking::create()
	{
		static game::ISteamNetworking instance{};
		static game::ISteamNetworking_vtbl vtable{};

		init_vtable(vtable);

		instance.__vftable = &vtable;
		instance.__vftable->IsP2PPacketAvailable = is_p2p_packet_available;
		instance.__vftable->ReadP2PPacket = read_p2p_packet;
		instance.__vftable->SendP2PPacket = send_p2p_packet;
		instance.__vftable->AcceptP2PSessionWithUser = accept_p2p_session_with_user;
		instance.__vftable->CloseP2PChannelWithUser = close_p2p_channel_with_user;
		instance.__vftable->GetP2PSessionState = get_p2p_session_state;

		return &instance;
	}

	game::ISteamNetworking* steam_networking::get_instance()
	{
		static const auto instance = create();
		return instance;
	}
}
