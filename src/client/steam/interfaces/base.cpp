#include <std_include.hpp>

#include "base.hpp"

namespace steam
{
	void* nullmeth()
	{
		printf("[steam] an interface called nullmeth %p\n", _ReturnAddress());
		return nullptr;
	}
}
