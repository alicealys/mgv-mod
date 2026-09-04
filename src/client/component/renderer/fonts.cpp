#include <std_include.hpp>

#include "loader/component_loader.hpp"

#include "game/game.hpp"

#include "utils.hpp"
#include "fonts.hpp"
#include "draw.hpp"
#include "../scheduler.hpp"
#include "../vars.hpp"

#include <utils/hook.hpp>

namespace renderer
{
	font_data_t font_data{};

	namespace
	{
		void init_memory_manager(game::fox::gr::dg::MemoryManager* manager, const size_t size)
		{
			const auto aligned_size = (size + 15) & 0xFFFFFFFull;
			const auto buffer = game::fox::KernelAllocAligned(aligned_size, 0x10);

			manager->unk1 = reinterpret_cast<game::fox::gr::dg::MemoryManager_unk1*>(buffer);
			manager->size = aligned_size;

			manager->unk1->unk1 = 0;
			manager->unk1->unk2 = manager->unk1;
			manager->unk1->unk3 = aligned_size;
			manager->unk1->unk4 = 129;
		}

		void destroy_memory_manager(game::fox::gr::dg::MemoryManager* manager)
		{
			game::fox::FreeAnnotated(manager->unk1, 0x5000F);
			std::memset(manager, 0, sizeof(game::fox::gr::dg::MemoryManager));
		}

		void initialize_font_texture_render(game::fox::gr::dg::FontTextureRender* render)
		{
			utils::hook::set<size_t>(0x14021065E_r + 2, 0x3DA16AC4E5A3); // force new texture resource
			game::fox::gr::dg::FontTextureRender_::FontTextureRender_(render, 0x800u, 0x400u);
			utils::hook::set<size_t>(0x14021065E_r + 2, 0xB8A0BF169F98);
		}

		void destroy_font_texture_render(game::fox::gr::dg::FontTextureRender* render)
		{
			render->imageGlyphManager->__vftable->__destructor(render->imageGlyphManager, 1);
			render->imageAreaManager->__vftable->__destructor(render->imageAreaManager, 1);

			if (render->unk1)
			{
				game::fox::FreeAnnotated(render->unk1, 0);
			}

			if (render->unk2)
			{
				game::fox::FreeAnnotated(render->unk2, 0);
			}

			std::memset(render, 0, sizeof(game::fox::gr::dg::FontTextureRender));
		}

		int load_font_internal(game::fox::gr::dg::FontData* font, int begin, int max_count,
			float scale, char spacing,
			char x_offset, char y_offset)
		{
			game::fox::gr::dg::FontTextureRender render{};
			initialize_font_texture_render(&render);
			const auto _0 = gsl::finally([&]
			{
				destroy_font_texture_render(&render);
			});

			const auto end = std::min(static_cast<short>(begin + max_count), font->glyphCount);

			auto done_count = 0;
			for (auto i = begin; i < end; i++)
			{
				const auto glyph = &font->glyphs[i];
				const auto glyph_info = &font_data.wide_char_glyphs[glyph->character];

				unsigned char area_1 = glyph->width + 2 * (font->spacing + 4);
				unsigned char area_2 = font->unk1_3 + 2 * (font->spacing + 4);
				const auto area_info = game::fox::gr::dg::ImageAreaManager_::AllocateAreaInfo(
					render.imageAreaManager, area_1, area_2, glyph->character);

				if (area_info == nullptr)
				{
					return done_count;
				}

				const auto texture_glyph_data = game::fox::gr::dg::ImageGlyphManager_::RegisterGlyphData(
					render.imageGlyphManager, font, area_info, glyph->character);

				glyph_info->texture_handle = render.fontTextureHandle;
				game::fox::gr::dg::FontTextureRender_::AddTextureRenderOrder(&render, font, glyph, texture_glyph_data);

				texture_glyph_data->width = static_cast<unsigned char>(static_cast<float>(texture_glyph_data->width) * scale);
				texture_glyph_data->height = static_cast<unsigned char>(static_cast<float>(texture_glyph_data->height) * scale);
				texture_glyph_data->horizontalSpace += spacing;
				texture_glyph_data->horizontalShift += x_offset;
				texture_glyph_data->verticalShift += y_offset;

				const auto half_pixel_width = 0.5f / static_cast<float>(render.pixel_width);
				const auto half_pixel_height = 0.5f / static_cast<float>(render.pixel_height);
				game::fox::gr::dg::FontSystem_::CalculateMetrics(&glyph_info->metrics, texture_glyph_data, 
					half_pixel_width, half_pixel_height, 1.f / 60.f);

				++done_count;
			}
			
			game::fox::gr::dg::FontTextureRender_::UpdateRenderGlyphTexture(&render);
			return done_count;
		}

		void load_font(const char* font_name,
			float scale, char spacing,
			char x_offset, char y_offset)
		{
			game::fox::gr::dg::FontData font{};
			game::fox::gr::dg::MemoryManager memory_manager{};

			font.fontIndex = 0;
			font.memoryManager = &memory_manager;
			init_memory_manager(&memory_manager, 0x27D000);

			const auto _0 = gsl::finally([&]
			{
				destroy_memory_manager(&memory_manager);
			});

			if (!game::fox::gr::dg::FontData_::LoadFontData(&font, font_name, nullptr))
			{
				return;
			}

			auto left_count = static_cast<int>(font.glyphCount);
			auto begin = 0;
			while (left_count > 0)
			{
				const auto max_count = std::min(256, left_count);
				const auto count = load_font_internal(&font, begin, max_count, scale, spacing, x_offset, y_offset);
				left_count -= count;
				begin += count;
			}
		}

		void init_fonts()
		{
			load_font("/Assets/ssd/ui/Font/KanjiFont.ffnt", 1.f, 0, 0, 0);
			load_font("/Assets/ssd/ui/Font/font_def_jp.ffnt", 1.f, 0, 0, 0);
			load_font("/Assets/ssd/ui/Font/font_def_hgl.ffnt", 1.f, 0, 0, 0);
			load_font("/Assets/ssd/ui/Font/font_def_chn.ffnt", 1.f, 0, 0, 0);
			load_font("/Assets/ssd/ui/Font/font_def_ltn.ffnt", 1.f, 0, 0, 0);
			font_data.loaded = true;
		}

		void* alloc_font_metrics_stub(int a1, int a2)
		{
			const auto buffer = game::fox::KernelAllocAligned(sizeof(custom_font_metrics_t), 4);
			std::memset(buffer, 0, sizeof(custom_font_metrics_t));
			return buffer;
		}

		void free_font_metrics_stub(custom_font_metrics_t* metrics)
		{
			if (metrics->string != nullptr)
			{
				game::fox::FreeAnnotated(metrics->string, 0x5000F);
				metrics->string = nullptr;
			}
			
			game::fox::FreeAnnotated(metrics, 0x5000F);
		}

		void init_metrics_stub(custom_font_metrics_t* string, const char* text, int a3, int font_type)
		{
			game::fox::gr::InitMetrics(&string->native, text, a3, font_type);

			if (!r_custom_text_rendering->current.enabled() || !is_system_font(font_type))
			{
				return;
			}

			auto count = 0;
			{
				auto c = reinterpret_cast<unsigned char*>(reinterpret_cast<size_t>(text));
				while (*c != 0)
				{
					game::fox::Utf8ToUtf32(&c);
					++count;
				};
			}

			auto buffer = game::fox::KernelAllocAligned(count * 2, 4);
			string->string = reinterpret_cast<wchar_t*>(buffer);

			auto c = reinterpret_cast<unsigned char*>(reinterpret_cast<size_t>(text));
			auto idx = 0;
			do
			{
				string->string[idx++] = static_cast<wchar_t>(game::fox::Utf8ToUtf32(&c));
			} while (*c != 0);

			string->str_len = count;
		}

		utils::hook::detour get_string_width_hook;
		int get_string_width_stub(void* a1, game::fox::gr::dg::FontData* a2, unsigned char* text, float* length, char font_type)
		{
			if (!r_custom_text_rendering->current.enabled() || !is_system_font(a2->fontIndex))
			{
				return get_string_width_hook.invoke<int>(a1, a2, text, length, font_type);
			}

			auto c = text;
			auto idx = 0;
			*length = 0.f;

			auto spacing = 0.f;
			auto scaling = 1.f;
			switch (get_language_code())
			{
			case 'npj':
				spacing = 3.f;
				scaling = 1.f;
				break;
			case 'sur':
				scaling = 1.1f;
				spacing = 0.f;
				break;
			default:
				spacing = 3.f;
				scaling = 1.f;
				break;
			}

			while (*c != 0)
			{
				if (c[0] == '^' && get_color_code(static_cast<char>(c[1]), nullptr))
				{
					c += 2;
					continue;
				}

				const auto char_idx = game::fox::Utf8ToUtf32(&c);
				if (char_idx >= 0xFFFF || !is_char_printable(static_cast<wchar_t>(char_idx)))
				{
					continue;
				}

				*length += font_data.wide_char_glyphs[char_idx].metrics.f9 * scaling + spacing * (1.f / 60.f);
				++idx;
			}

			return idx;
		}

		utils::hook::detour get_utf8_count_hook;
		int get_utf8_count_stub(unsigned char* text)
		{
			if (!r_custom_text_rendering->current.enabled())
			{
				return get_utf8_count_hook.invoke<int>(text);
			}

			auto c = text;
			auto idx = 0;
			while (*c != 0)
			{
				if (c[0] == '^' && get_color_code(static_cast<char>(c[1]), nullptr))
				{
					c += 2;
					continue;
				}

				const auto char_idx = game::fox::Utf8ToUtf32(&c);
				if (char_idx >= 0xFFFF || !is_char_printable(static_cast<wchar_t>(char_idx)))
				{
					continue;
				}

				++idx;
			}

			return idx;
		}
	}

	bool is_char_printable(const char c)
	{
		const auto wch = ascii_to_wchar(c);
		return is_char_printable(wch);
	}

	bool is_char_printable(const wchar_t c)
	{
		return iswprint(c) && font_data.wide_char_glyphs[c].texture_handle != 0;
	}

	bool is_system_font(int font_type)
	{
		return font_type == 1 || font_type == 2;
	}

	namespace fonts
	{
		class component final : public component_interface
		{
		public:
			void pre_load() override
			{
				scheduler::once(init_fonts, scheduler::main);
				//utils::hook::call(0x1402BF6A0_r, alloc_font_metrics_stub);
				//utils::hook::call(0x1402BF558_r, free_font_metrics_stub);
				//utils::hook::call(0x1402BF6B5_r, init_metrics_stub);
				//get_utf8_count_hook.create(0x1409F8EE0_r, get_utf8_count_stub);
				//get_string_width_hook.create(0x140232420_r, get_string_width_stub);
			}
		};
	}
}

REGISTER_COMPONENT(renderer::fonts::component)
