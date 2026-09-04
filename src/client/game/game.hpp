#pragma once

#include "structs.hpp"

#define SELECT_VALUE(...) game::select(__VA_ARGS__)
#define SELECT_VALUE_NOLANG(tpp, mgo) (game::environment::is_tpp() ? (tpp) : (mgo))
#define SELECT_VALUE_LANG(eng, jpn) (game::environment::is_eng() ? (eng) : (jpn))

namespace game
{
	namespace environment
	{
		enum game_mode
		{
			mode_none = -1,
			mode_ssd_eng = 0,
			mode_count = 1,
		};

		game_mode get_mode();

		void set_mode(game_mode mode);

		bool is_ssd();

		void detect_version();
	}

	template <typename ...Args, size_t N = sizeof...(Args)>
	auto select(Args... values)
	{
		using T = std::common_type_t<Args...>;
		const std::array<T, environment::mode_count> v = {values...};
		const auto mode = environment::get_mode();
		assert(mode >= 0);
		return v[mode];
	}

	template <typename T>
	class symbol
	{
	public:
		symbol(const size_t ssd_eng)
		{
			this->addresses_[environment::mode_ssd_eng] = ssd_eng;
		}

		T* get() const
		{
			return reinterpret_cast<T*>(this->addresses_[environment::get_mode()]);
		}

		operator T* () const
		{
			return this->get();
		}

		T* operator->() const
		{
			return this->get();
		}

	private:
		std::array<size_t, environment::mode_count> addresses_{};

	};
}

#include "symbols.hpp"
