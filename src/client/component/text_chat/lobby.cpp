#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/game.hpp"

#include "lobby.hpp"
#include "ui.hpp"
#include "defs.hpp"
#include "../session.hpp"
#include "../scripting.hpp"
#include "../game_socket.hpp"

#include <utils/io.hpp>
#include <utils/hook.hpp>
#include <utils/string.hpp>

namespace text_chat::lobby
{
	namespace
	{
		constexpr auto chat_message_msg_id = 30;

		std::wstring get_steam_player_name(game::steam_id user)
		{
			const auto name = session::get_player_name(user);
			const auto name_w = utils::string::utf8_to_utf16(name);
			return name_w;
		}

		char get_client_color(int index)
		{
			switch (index % 4)
			{
			case 0:
				return 'a';
			case 1:
				return 'b';
			case 2:
				return 'c';
			case 3:
				return 'd';
			}

			return 'a';
		}

		void process_chat_msg(game::fox::nt::Member* client, const char* buffer, const std::size_t size)
		{
			if (size < 6)
			{
				return;
			}

			game::steam_id user{};
			user.bits = client->sessionUserId->userId;

			const auto msg_id = *reinterpret_cast<const int*>(buffer);
			if (msg_id != chat_message_msg_id)
			{
				return;
			}

			const auto name_w = get_steam_player_name(user);
			const auto text = reinterpret_cast<const wchar_t*>(&buffer[sizeof(chat_message_msg_id)]);
			auto text_len = (size - sizeof(chat_message_msg_id)) / sizeof(wchar_t);

			if (text_len > chat_message_max_len)
			{
				text_len = chat_message_max_len;
			}

			std::wstring formatted_msg;
			formatted_msg.resize(chat_message_buffer_len);

			_snwprintf_s(formatted_msg.data(), formatted_msg.size(), _TRUNCATE,
				L"^%c%s^7: %.*s", get_client_color(client->index), name_w.data(), static_cast<int>(text_len), text);

			text_chat::ui::print(formatted_msg, true);

			const auto message_a = utils::string::utf16_to_ascii(formatted_msg);
			console::info("%s\n", message_a.data());
		}
	}

	void send_chat_message(const std::wstring& text)
	{
		const auto id = chat_message_msg_id;

		std::string buffer;
		buffer.reserve(sizeof(id) + text.size() * sizeof(wchar_t));

		buffer.append(reinterpret_cast<const char*>(&id), sizeof(id));
		buffer.append(reinterpret_cast<const char*>(text.data()), text.size() * sizeof(wchar_t));

		game_socket::send("chat_message", buffer, -1);
	}

	class component final : public component_interface
	{
	public:
		void start() override
		{
			game_socket::on("chat_message", [](game::fox::nt::impl::SessionImpl2* session,
				const game_socket::message_info_t& info, const std::string_view& buffer)
			{
				if (info.game_object_id >= session->allMembers.size)
				{
					return;
				}

				const auto sender = session->allMembers.members[info.game_object_id];
				if (sender == nullptr)
				{
					return;
				}

				process_chat_msg(sender, buffer.data(), buffer.size());
			});

			command::add("say", [](const command::params& params)
			{
				if (params.size() < 2)
				{
					return;
				}

				const auto msg = utils::string::convert(params.join(1));
				send_chat_message(msg);
			});
		}
	};
}

REGISTER_COMPONENT(text_chat::lobby::component)
