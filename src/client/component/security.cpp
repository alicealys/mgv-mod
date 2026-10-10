#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "game/game.hpp"

#include "console.hpp"

#include <utils/hook.hpp>
#include <utils/string.hpp>

namespace security
{
	namespace
	{
		unsigned __int64 nio_buffer_read_stub(game::fox::nio::Buffer* buffer, unsigned char* dest, unsigned int size)
		{
			const auto result = game::fox::nio::Buffer_::IoBinary(buffer, dest, size);
			if (*dest != 0 && *dest != 3)
			{
				*dest = 0;
			}
			return result;
		}
	}

	class component final : public component_interface
	{
	public:
		void pre_load() override
		{
			utils::hook::far_call(0x14032FA97_r, nio_buffer_read_stub);  // unchecked session user id type
		}
	};
}

REGISTER_COMPONENT(security::component)
