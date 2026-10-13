#pragma once

#include "game/game.hpp"

namespace steam
{
	void* nullmeth();

	template <typename T>
	void init_vtable(T& vtable)
	{
		const auto func_count = sizeof(T) / sizeof(void*);
		for (auto i = 0ull; i < func_count; i++)
		{
			reinterpret_cast<void**>(&vtable)[i] = nullmeth;
		}
	}
}
