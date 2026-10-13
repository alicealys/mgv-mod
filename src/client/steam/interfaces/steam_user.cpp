#include <std_include.hpp>

#include "base.hpp"

#include "steam_user.hpp"

#include "component/filesystem.hpp"

namespace steam
{
	namespace
	{
		game::steam_id* get_steam_id_stub(game::ISteamUser*, game::steam_id* out)
		{
			out->bits = steam_user::get_steam_id().bits;
			return out;
		}

		bool get_user_data_folder(game::ISteamUser*, char* buffer, int size)
		{
			const auto& path = filesystem::get_config_path();
			const auto folder = (path / "userdata").generic_string();
			sprintf_s(buffer, size, "%s", folder.data());
			return true;
		}

		bool b_logged_on(game::ISteamUser*)
		{
			return true;
		}

		game::HAuthTicket get_auth_session_ticket(game::ISteamUser* this_, void* data, int max_ticket, unsigned int* ticket_size)
		{
			game::steam_id steam_id{};
			this_->__vftable->GetSteamID(this_, &steam_id);

			std::memset(reinterpret_cast<char*>(data), 0, max_ticket);
			std::memcpy(reinterpret_cast<char*>(data) + 12, &steam_id.bits, sizeof(steam_id.bits));
			*ticket_size = max_ticket;
			return 1;
		}

		game::EVoiceResult decompress_voice(game::ISteamUser*, const void* compressed, unsigned int compressed_size, 
			void* dest, unsigned int dest_size, unsigned int* bytes_written, unsigned int sample_rate)
		{
			std::memset(dest, 0, dest_size);
			bytes_written = 0;
			return game::EVoiceResult(3);
		}

		game::EVoiceResult get_available_voice(game::ISteamUser*, unsigned int* compressed, unsigned int* uncompressed, unsigned int sample_rate)
		{
			return game::EVoiceResult(3);
		}

		void start_voice_recording(game::ISteamUser*)
		{

		}

		void stop_voice_recording(game::ISteamUser*)
		{

		}
	}

	game::steam_id steam_user::get_steam_id()
	{
		game::steam_id out{};
		out.bits = 76561197960265742;
		return out;
	}

	game::ISteamUser* steam_user::create()
	{
		static game::ISteamUser instance{};
		static game::ISteamUser_vtbl vtable{};

		init_vtable(vtable);

		instance.__vftable = &vtable;
		instance.__vftable->GetSteamID = get_steam_id_stub;
		instance.__vftable->GetUserDataFolder = get_user_data_folder;
		instance.__vftable->BLoggedOn = b_logged_on;
		instance.__vftable->GetAuthSessionTicket = get_auth_session_ticket;
		instance.__vftable->DecompressVoice = decompress_voice;
		instance.__vftable->GetAvailableVoice = get_available_voice;
		instance.__vftable->StartVoiceRecording = start_voice_recording;
		instance.__vftable->StopVoiceRecording = stop_voice_recording;

		return &instance;
	}

	game::ISteamUser* steam_user::get_instance()
	{
		static const auto instance = create();
		return instance;
	}
}
