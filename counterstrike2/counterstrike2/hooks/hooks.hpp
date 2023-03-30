#pragma once

#include <cstdint>
#include <utility>
#include <dxgi.h>

namespace hooks
{
	bool initialize();
	void release();

	namespace create_move
	{
		using function_t = std::byte* (__fastcall*)(void*, unsigned int, unsigned __int8);
		std::byte* __fastcall hook(void* csgoinput, unsigned int a2, unsigned __int8 a3);
	}

	namespace level_init
	{
		using function_t = std::int64_t(__fastcall*)(std::int64_t, std::int64_t);
		std::int64_t __fastcall hook(std::int64_t a1, std::int64_t a2);
	}

	namespace frame_stage_notify
	{
		using function_t = std::int64_t(__fastcall*)(std::int64_t, std::int32_t);
		std::int64_t __fastcall hook(std::int64_t a1, std::int32_t a2);
	}
}