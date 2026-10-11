#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/game.hpp"

#include "command.hpp"
#include "scheduler.hpp"
#include "console.hpp"
#include "session.hpp"

#include <utils/hook.hpp>
#include <utils/string.hpp>

namespace session
{
	session_info_t session_info{};

	namespace
	{
		const char* get_session_state_name(const int state)
		{
			switch (state)
			{
			case 0:
				return "none";
			case 2:
			case 3:
				return "host";
			case 4:
				return "client connect";
			case 5:
				return "client init";
			case 6:
			case 7:
				return "client established";
			}

			return "unknown";
		}

		void print_status()
		{
			const auto main_session = *game::s_pSession;
			if (!main_session)
			{
				return;
			}

			const auto steam_friends = game::get_steam_interfaces()->steamFriends;
			const auto is_host = main_session->sessionInterface.__vftable->IsHost(&main_session->sessionInterface);
			const auto state = main_session->__vftable->GetState(main_session);
			const auto all_members = &main_session->allMembers;

			printf("is host: %i\n", is_host);
			printf("state: %s (%i)\n", get_session_state_name(state), state);
			printf("ping: %ims\n", get_rtt(main_session));

			printf("num flags ping  steam_id                         name                            \n");
			printf("--- ----- ----- -------------------------------- --------------------------------\n");

			for (auto i = 0u; i < all_members->size; i++)
			{
				const auto member = all_members->members[i];
				if (member == nullptr || member->flags == 0)
				{
					continue;
				}

				game::steam_id steam_id{};
				steam_id.bits = member->sessionUserId->userId;

				const auto name = steam_friends->__vftable->GetFriendPersonaName(steam_friends, steam_id);
				const auto ping = member->sppSocket != nullptr
					? member->sppSocket->rtt_time
					: -1;

				printf("%3i %5i %5i %32lli %32s", i, member->flags, ping, steam_id.bits, name);
			}
		}

		void run_frame()
		{
			static auto prev_state = 0u;

			const auto main_session = *game::s_pSession;
			if (main_session == nullptr)
			{
				session_info = {};
				return;
			}

			const auto state = get_state(main_session);
			if (state != prev_state)
			{
				console::debug("[session] state updated: %i\n", state);
			}

			session_info.active = true;
			session_info.state = state;
			session_info.is_host = main_session->sessionInterface.__vftable->IsHost(&main_session->sessionInterface);
			const auto host = main_session->sessionInterface.__vftable->GetMemberInterfaceAtIndex(&main_session->sessionInterface, 0);

			switch (state)
			{
			case 2:
			case 3:
			case 6:
			case 7:
				session_info.is_connected = host != nullptr;
				break;
			default:
				session_info.is_connected = false;
				break;
			}

			prev_state = state;
		}
	}

	int get_rtt(game::fox::nt::impl::SessionImpl2* session)
	{
		if (session == nullptr || session->sppSocket == nullptr)
		{
			return 0;
		}

		return session->sppSocket->rtt_time;
	}

	bool is_host(game::fox::nt::impl::SessionImpl2* session)
	{
		if (session == nullptr)
		{
			return false;
		}

		return session->sessionInterface.__vftable->IsHost(&session->sessionInterface);
	}

	unsigned int get_state(game::fox::nt::impl::SessionImpl2* session)
	{
		if (session == nullptr)
		{
			return 0;
		}

		return session->__vftable->GetState(session);
	}

	bool is_host()
	{
		const auto main_session = *game::s_pSession;
		if (main_session == nullptr)
		{
			return false;
		}

		return main_session->sessionInterface.__vftable->IsHost(&main_session->sessionInterface);
	}

	class component final : public component_interface
	{
	public:
		void pre_load() override
		{

		}

		void start() override
		{
			scheduler::loop(run_frame, scheduler::session);

			command::add("status", []
			{
				scheduler::once(print_status, scheduler::session);
			});
		}
	};
}

REGISTER_COMPONENT(session::component)
