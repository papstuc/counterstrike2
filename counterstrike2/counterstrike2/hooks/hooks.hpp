#pragma once

#include <cstdint>
#include <utility>
#include <dxgi.h>

namespace hooks
{
	bool initialize();

	namespace createmove
	{
		using function_t = std::byte* (__fastcall*)(void*, unsigned int, unsigned __int8);
		std::byte* __fastcall hook(void* csgoinput, unsigned int a2, unsigned __int8 a3);
	}
}