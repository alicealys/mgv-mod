#include <std_include.hpp>
#include "game.hpp"

#include <utils/flags.hpp>
#include <utils/nt.hpp>
#include <utils/cryptography.hpp>
#include <utils/io.hpp>
#include <utils/string.hpp>

namespace game
{
	namespace environment
	{
		struct binary_t
		{
			std::string name;
			game_mode mode;
			bool supported;
		};

		binary_t binaries[mode_count] =
		{
			{"mgv.exe (eng, 1.0.21.0)", mode_ssd_eng, true},
		};

		std::unordered_map<std::uint32_t, binary_t> hashes_crc =
		{
			{0xD6E0560D, binaries[mode_ssd_eng]}, // default
			{0x726F5323, binaries[mode_ssd_eng]}, // no aslr exe
		};

		std::unordered_map<std::string, game_mode> gamemodes =
		{
			{"ssdeng", mode_ssd_eng},
		};

		game_mode mode = game_mode::mode_none;

		void set_mode(const game_mode mode_)
		{
			mode = mode_;
		}

		game_mode get_mode()
		{
			return mode;
		}

		bool is_ssd()
		{
			return get_mode() == mode_ssd_eng;
		}

		bool is_dedi()
		{
			return false;
		}

		void manual_version(const std::string& value)
		{
			const auto iter = gamemodes.find(value);
			if (iter == gamemodes.end())
			{
				throw std::runtime_error(utils::string::va("invalid gamemode \"%s\", options: ssdeng", value.data()));
			}

			set_mode(iter->second);
		}

		void detect_version()
		{
			utils::nt::library self;
			const auto path = self.get_path();
			std::string data;

			const auto override_ = utils::flags::get_flag("mode");
			if (override_.has_value())
			{
				manual_version(override_.value());
				return;
			}

#ifdef DEBUG
			const auto start = std::chrono::high_resolution_clock::now();
#endif

			std::ifstream stream;
			stream.open(path, std::ios::binary);
			if (!stream.is_open())
			{
				throw std::runtime_error("Failed to get MGV version");
			}

			std::string buffer;
			buffer.resize(0x10000);

			auto crc_value = crc32(0L, Z_NULL, 0);
			while (stream.is_open() && !stream.eof())
			{
				stream.read(buffer.data(), buffer.size());
				crc_value = crc32(crc_value, reinterpret_cast<std::uint8_t*>(buffer.data()), static_cast<std::uint32_t>(stream.gcount()));
				std::memset(buffer.data(), 0, buffer.size());
			}

#ifdef DEBUG
			const auto end = std::chrono::high_resolution_clock::now();
			const auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
			OutputDebugString(utils::string::va("hash: 0x%X, time: %llimsec", crc_value, time));
#endif

			const auto iter = hashes_crc.find(crc_value);
			if (iter == hashes_crc.end())
			{
				throw std::runtime_error("Unknown MGV version, use -mode <gamemode> to manually specify it (ssdeng)");
			}

			if (!iter->second.supported)
			{
				throw std::runtime_error(utils::string::va("This version of MGV is not supported:\n%s", iter->second.name.data()));
			}

			set_mode(iter->second.mode);
		}
	}

	std::size_t get_base_address()
	{
		static const auto handle = GetModuleHandle(NULL);
		return reinterpret_cast<std::size_t>(handle);
	}

	std::size_t rebase_address(const std::size_t rva)
	{
		static const auto base = game::get_base_address();
		return rva - 0x140000000 + base;
	}
}

std::size_t operator ""_r(const std::size_t rva)
{
	return game::rebase_address(rva);
}
