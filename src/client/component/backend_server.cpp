#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/game.hpp"

#include "scheduler.hpp"
#include "console.hpp"
#include "vars.hpp"
#include "backend_server.hpp"

#include <utils/string.hpp>
#include <utils/hook.hpp>
#include <utils/flags.hpp>
#include <utils/io.hpp>
#include <utils/cryptography.hpp>
#include <utils/http.hpp>
#include <utils/compression.hpp>
#include <utils/properties.hpp>

namespace backend_server
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
	};
}

REGISTER_COMPONENT(backend_server::component)
