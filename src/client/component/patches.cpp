#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/game.hpp"

#include "vars.hpp"
#include "scheduler.hpp"

#include <utils/hook.hpp>
#include <utils/flags.hpp>
#include <utils/string.hpp>

namespace patches
{
	namespace
	{

	}

	class component final : public component_interface
	{
	public:
		void pre_load() override
		{

		}

		void start() override
		{

		}

		void game_initialized()
		{

		}
	};
}

REGISTER_COMPONENT(patches::component)
