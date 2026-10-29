#pragma once

namespace session
{
	struct session_info_t
	{
		bool active;
		bool is_host;
		bool is_connected;
		std::int32_t state;
	};

	extern session_info_t session_info;

	bool is_host();
	int get_rtt(game::fox::nt::impl::SessionImpl2* session);
	bool is_host(game::fox::nt::impl::SessionImpl2* session);
	unsigned int get_state(game::fox::nt::impl::SessionImpl2* session);

	const char* get_player_name(const game::steam_id steam_id);
}
