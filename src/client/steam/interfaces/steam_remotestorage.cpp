#include <std_include.hpp>

#include "base.hpp"

#include "steam_user.hpp"
#include "steam_remotestorage.hpp"

#include "component/filesystem.hpp"
#include "component/console.hpp"

#include <utils/io.hpp>

namespace steam
{
	namespace
	{
		int get_file_size(game::ISteamRemoteStorage*, const char* file)
		{
			const auto path = steam_remotestorage::get_file_path(file);
			return static_cast<int>(utils::io::file_size(path));
		}

		bool file_exists(game::ISteamRemoteStorage*, const char* file)
		{
			const auto path = steam_remotestorage::get_file_path(file);
			return utils::io::file_exists(path);
		}

		int file_read(game::ISteamRemoteStorage*, const char* file, void* buffer, int buffer_size)
		{
			console::info("[SteamStorage] Reading file \"%s\"\n", file);

			std::memset(buffer, 0, buffer_size);
			const auto path = steam_remotestorage::get_file_path(file);

			std::string data;
			if (utils::io::read_file(path, &data) && data.size() <= buffer_size)
			{
				std::memcpy(buffer, data.data(), data.size());
				return 1;
			}

			return 0;
		}

		bool file_write(game::ISteamRemoteStorage*, const char* file, const void* buffer, int size)
		{
			console::info("[SteamStorage] Writing file \"%s\"\n", file);

			const auto path = steam_remotestorage::get_file_path(file);
			const auto data = std::string{
				reinterpret_cast<const char*>(buffer), 
				reinterpret_cast<const char*>(buffer) + size};

			return utils::io::write_file(path, data);
		}
	}

	std::string steam_remotestorage::get_file_path(const char* file)
	{
		const auto steam_id = steam_user::get_steam_id();
		const auto& appdata = filesystem::get_config_path();
		return std::format("{}\\userdata\\{}\\steam_storage\\{}", appdata.generic_string(), steam_id.bits, file);
	}

	game::ISteamRemoteStorage* steam_remotestorage::create()
	{
		static game::ISteamRemoteStorage instance{};
		static game::ISteamRemoteStorage_vtbl vtable{};

		init_vtable(vtable);

		instance.__vftable = &vtable;
		instance.__vftable->GetFileSize = get_file_size;
		instance.__vftable->FileRead = file_read;
		instance.__vftable->FileWrite = file_write;
		instance.__vftable->FileExists = file_exists;

		return &instance;
	}

	game::ISteamRemoteStorage* steam_remotestorage::get_instance()
	{
		static const auto instance = create();
		return instance;
	}
}
