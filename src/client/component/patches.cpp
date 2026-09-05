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
		vars::var_ptr var_com_unlock_fps;
		vars::var_ptr var_com_worker_count;
		vars::var_ptr var_com_max_fps;
		vars::var_ptr var_sensitivity;

		void set_timer_resolution()
		{
			ULONG data{};
			const utils::nt::library ntdll("ntdll.dll");
			ntdll.invoke_pascal<void>("NtSetTimerResolution", 5000, TRUE, &data);
		}

		unsigned int get_processor_count_stub()
		{
			return var_com_worker_count->current.get_int();
		}

		utils::hook::detour leave_frame_hook;

		void leave_frame_stub(void* a1)
		{
			leave_frame_hook.invoke<void>(a1);

			const auto max_fps = var_com_max_fps->current.get_int();
			if (max_fps == 0)
			{
				return;
			}

			constexpr auto nano_secs = std::chrono::duration_cast<std::chrono::nanoseconds>(1s);
			const auto target_frame_time = nano_secs / max_fps;

			while ((std::chrono::steady_clock::now() - scheduler::main_frame_begin) < target_frame_time)
			{
				std::this_thread::sleep_for(1ms);
			}
		}

		void unlock_fps()
		{
			utils::hook::jump(0x14008CA2A_r, 0x14008CBF8_r); // nowait frame mode
			utils::hook::nop(0x1400339AC_r, 5); // job executor thread sleep
			utils::hook::far_jump(game::get_base_address(), 0x140035000_r, get_processor_count_stub);
			leave_frame_hook.create(0x14008B6D0_r, leave_frame_stub);
		}

		void patch_sensitivity()
		{
			constexpr const auto base_value = 0.016683333f;
			auto value_ptr = utils::hook::far_inject<float>(game::get_base_address(), 0x1416950E1_r + 4);
			*value_ptr = base_value;

			var_sensitivity->set_callback = [value_ptr]()
			{
				*value_ptr = base_value * var_sensitivity->current.get_float();
			};

			var_sensitivity->set_callback->operator()();
		}
	}

	class component final : public component_interface
	{
	public:
		void pre_load() override
		{
			var_com_unlock_fps = vars::register_bool("com_unlock_fps", true, 
				vars::var_flag_saved | vars::var_flag_latched, "unlock fps");

			var_com_max_fps = vars::register_int("com_max_fps", 200, 0, 1000,
				vars::var_flag_saved, "max fps (only works when com_unlock_fps is enabled)");

			var_com_worker_count = vars::register_int("com_worker_count", 4, 2, std::thread::hardware_concurrency(),
				vars::var_flag_saved | vars::var_flag_latched, "maxiumum number of job executor worker threads");

			var_sensitivity = vars::register_float("sensitivity", 1.f, 0.f, 10.f,
				vars::var_flag_saved, "mouse sensitivity scale");
		}

		void start() override
		{
			set_timer_resolution();

			if (var_com_unlock_fps->current.enabled())
			{
				unlock_fps();
			}

			// disable _purecall error
			utils::hook::set<std::uint8_t>(0x14192416E_r, 0xC3);

			patch_sensitivity();
		}

		void game_initialized()
		{

		}
	};
}

REGISTER_COMPONENT(patches::component)
