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
		vars::var_ptr var_sensitivity_patch;

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

		void player_mouse_event_update_stub(__int64 a1)
		{
			const auto time_system = game::fox::GetTimeSystem();
			const auto frame_time_scale = static_cast<float>(time_system.frameTime) * 100.f;

			const auto v_x = *reinterpret_cast<LONG*>(a1 + 40);
			const auto v_y = *reinterpret_cast<LONG*>(a1 + 44);

			InterlockedExchangeAdd(reinterpret_cast<LONG*>(a1 + 40), -v_x);
			InterlockedExchangeAdd(reinterpret_cast<LONG*>(a1 + 44), -v_y);

			*reinterpret_cast<void**>(a1 + 48) = *reinterpret_cast<void**>(a1 + 32);

			if (var_sensitivity_patch->current.enabled())
			{
				*reinterpret_cast<float*>(a1 + 56) = static_cast<float>(v_x) * 0.001f * frame_time_scale;
				*reinterpret_cast<float*>(a1 + 60) = static_cast<float>(v_y) * 0.001f * frame_time_scale;
			}
			else
			{
				*reinterpret_cast<float*>(a1 + 56) = static_cast<float>(v_x) * 0.001f;
				*reinterpret_cast<float*>(a1 + 60) = static_cast<float>(v_y) * 0.001f;
			}
		}


		void unlock_fps()
		{
			utils::hook::jump(0x14008CA2A_r, 0x14008CBF8_r); // nowait frame mode
			utils::hook::nop(0x1400339AC_r, 5); // job executor thread sleep
			utils::hook::far_jump(0x140035000_r, get_processor_count_stub);
			leave_frame_hook.create(0x14008B6D0_r, leave_frame_stub);
			utils::hook::far_jump(0x140A9B900_r, player_mouse_event_update_stub);
		}

		void patch_sensitivity()
		{
			constexpr const auto base_value = 0.016683333f;
			auto value_ptr = utils::hook::far_inject<float>(0x1416950E1_r + 4);
			*value_ptr = base_value;

			var_sensitivity->set_callback = [value_ptr]()
			{
				*value_ptr = base_value * var_sensitivity->current.get_float();
			};

			var_sensitivity->set_callback->operator()();
		}

		void set_appid()
		{
			constexpr const auto app_id = 543900;
			SetEnvironmentVariableA("SteamAppId", utils::string::va("%lu", app_id));
			SetEnvironmentVariableA("SteamGameId", utils::string::va("%llu", app_id & 0xFFFFFF));
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

			var_sensitivity_patch = vars::register_bool("sensitivity_fps_patch", false,
				vars::var_flag_saved, "enable sensitivity scaling patch");
		}

		void start() override
		{
			set_appid();
			set_timer_resolution();

			if (var_com_unlock_fps->current.enabled())
			{
				unlock_fps();
			}

			// disable _purecall error
			utils::hook::set<std::uint8_t>(0x14192416E_r, 0xC3);

			patch_sensitivity();

			// remove anti debugging
			utils::hook::jump(0x1435FB310_r, 0x14192449C_r);
		}

		void game_initialized()
		{

		}
	};
}

REGISTER_COMPONENT(patches::component)
