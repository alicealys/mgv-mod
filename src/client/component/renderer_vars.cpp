#include <std_include.hpp>

#include "loader/component_loader.hpp"

#include "game/game.hpp"

#include "vars.hpp"

#include <utils/hook.hpp>

namespace renderer_vars
{
	namespace
	{
		vars::var_ptr var_r_draw2d;
		vars::var_ptr var_r_fog;

		utils::hook::detour gr_plugin_2d_main_exec_hook;

		bool get_fog_enabled()
		{
			return var_r_fog->current.enabled();
		}

		void volumetric_fog_manager_update_stub(utils::hook::assembler& a)
		{
			const auto fog_disabled = a.new_label();
			const auto fog_enabled = a.new_label();

			a.push(rax);
			a.pushad64();
			a.call_aligned(get_fog_enabled);
			a.mov(qword_ptr(rsp, 0x80), rax);
			a.popad64();
			a.pop(rax);

			a.mov(qword_ptr(rdi, 0x18), rdx);
			a.and_(sil, al);
			a.test(sil, sil);
			a.jnz(fog_enabled);

			a.jmp(0x140763E44_r);

			a.bind(fog_enabled);
			a.jmp(0x140763F1B_r);
		}

		void gr_plugin_2d_main_exec_stub(void* a1, void* a2, void* a3)
		{
			if (!var_r_draw2d->current.enabled())
			{
				return;
			}

			gr_plugin_2d_main_exec_hook.invoke<void>(a1, a2, a3);
		}
	}

	class component final : public component_interface
	{
	public:
		void pre_load() override
		{
			var_r_fog = vars::register_bool("r_fog", true, vars::var_flag_saved, "enable fog");
			var_r_draw2d = vars::register_bool("r_draw2d", true, vars::var_flag_saved, "draw 2d");

			utils::hook::jump(0x140763E37_r, utils::hook::assemble(volumetric_fog_manager_update_stub), true);

			gr_plugin_2d_main_exec_hook.create(0x1401CC270_r, gr_plugin_2d_main_exec_stub);
		}
	};
}

REGISTER_COMPONENT(renderer_vars::component)
