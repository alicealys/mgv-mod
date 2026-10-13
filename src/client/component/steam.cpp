#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/game.hpp"
#include "steam/steam.hpp"

#include "steam.hpp"

#include <utils/flags.hpp>

namespace steam
{
	bool is_nosteam()
	{
		static const auto result = utils::flags::has_flag("nosteam");
		return result;
	}

	class component final : public component_interface
	{
	public:
		void pre_load() override
		{
			if (is_nosteam())
			{
				steam::disable_steam();
			}
		}
	};
}

REGISTER_COMPONENT(steam::component)
