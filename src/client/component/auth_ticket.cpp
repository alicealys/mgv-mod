#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/game.hpp"

#include "scheduler.hpp"
#include "console.hpp"
#include "vars.hpp"
#include "backend_server.hpp"
#include "filesystem.hpp"

#include <utils/string.hpp>
#include <utils/hook.hpp>
#include <utils/flags.hpp>
#include <utils/io.hpp>
#include <utils/cryptography.hpp>
#include <utils/http.hpp>
#include <utils/compression.hpp>
#include <utils/properties.hpp>

namespace auth_ticket
{
	namespace
	{
		game::fox::gk::FirstPartyTicketImpl* first_party_ticket = nullptr;

		struct auth_ticket_custom_t
		{
			std::uint64_t account_id;
			char auth_token[32];
		};

		void clear_command_line()
		{
			const auto process_params = NtCurrentTeb()->ProcessEnvironmentBlock->ProcessParameters;
			SecureZeroMemory(process_params->CommandLine.Buffer, process_params->CommandLine.Length);
		}

		std::string get_auth_token_save_path()
		{
			const auto url_hash = backend_server::get_url_hash();
			return std::format("{}\\auth_tokens\\{}", backend_server::get_user_storage_path(), backend_server::get_url_hash());
		}

		std::optional<std::string> get_auth_token(bool from_file = true)
		{
			const auto auth_token = utils::flags::get_flag("auth-token");
			if (auth_token.has_value() && auth_token->size() == sizeof(auth_ticket_custom_t::auth_token))
			{
				clear_command_line();
				return auth_token;
			}

			if (!from_file)
			{
				return {};
			}

			const auto path = get_auth_token_save_path();
			std::string data;
			if (utils::io::read_file(path, &data))
			{
				const auto token = utils::string::trim(data);
				if (token.size() == sizeof(auth_ticket_custom_t::auth_token))
				{
					return {token};
				}
			}

			return {};
		}

		utils::hook::detour get_auth_session_ticket_hook;
		unsigned int get_auth_session_ticket_stub(game::ISteamUser* steam_user, char* data, int max_ticket, unsigned int* ticket_size)
		{
			static const auto auth_token = get_auth_token();
			if (!backend_server::is_using_custom_server() || 
				(!auth_token.has_value() && steam_user->__vftable->BLoggedOn(steam_user)))
			{
				console::info("[auth] using steam ticket\n");
				return get_auth_session_ticket_hook.invoke<unsigned int>(steam_user, data, max_ticket, ticket_size);
			}

			game::steam_id steam_id{};
			steam_user->__vftable->GetSteamID(steam_user, &steam_id);

			if (auth_token.has_value())
			{
				console::info("[auth] using auth token ticket\n");
				const auto ticket = reinterpret_cast<auth_ticket_custom_t*>(data);
				ticket->account_id = steam_id.bits;
				std::memcpy(ticket->auth_token, auth_token->data(), sizeof(auth_ticket_custom_t::auth_token));
				*ticket_size = sizeof(auth_ticket_custom_t);
			}
			else
			{
				console::info("[auth] using fake steam ticket\n");
				std::memset(data, 0, max_ticket);
				std::memcpy(data + 12, &steam_id.bits, sizeof(steam_id.bits));
				*ticket_size = max_ticket;
			}

			first_party_ticket->a3 = 0;
			first_party_ticket->result = 0;
			return 1;
		}

		utils::hook::detour first_party_ticket_create_hook;
		game::fox::gk::FirstPartyTicketImpl* first_party_ticket_create_stub(game::fox::gk::FirstPartyTicketImpl* inst)
		{
			first_party_ticket = inst;
			return first_party_ticket_create_hook.invoke<game::fox::gk::FirstPartyTicketImpl*>(inst);
		}
	}

	class component final : public component_interface
	{
	public:
		void pre_load() override
		{
			first_party_ticket_create_hook.create(0x141D2F2E0_r, first_party_ticket_create_stub);
		}

		void start() override
		{

		}

		void game_initialized() override
		{
			const auto steam = game::get_steam_interfaces();

			get_auth_session_ticket_hook.create(steam->steamUser->__vftable->GetAuthSessionTicket, get_auth_session_ticket_stub);
		}
	};
}

REGISTER_COMPONENT(auth_ticket::component)
