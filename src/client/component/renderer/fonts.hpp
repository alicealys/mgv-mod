#pragma once

#include "game/game.hpp"

namespace renderer
{
	struct glyph_info_t
	{
		game::fox::gr::dg::FontTextureMetrics metrics;
		unsigned int texture_handle;
	};

	struct font_data_t
	{
		bool loaded;
		glyph_info_t wide_char_glyphs[0xFFFF]{};
	};

	struct custom_font_metrics_t
	{
		game::fox::gr::dg::StringFontMetricsCache native;
		wchar_t* string;
		int str_len;
	};

	extern font_data_t font_data;

	bool is_char_printable(const char c);
	bool is_char_printable(const wchar_t c);
	bool is_system_font(int font_type);
}
