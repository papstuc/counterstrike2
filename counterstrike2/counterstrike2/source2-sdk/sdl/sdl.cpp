#include "sdl.hpp"

#include <Windows.h>

void sdl::set_relative_mouse_mode(bool mode)
{
	using function_t = std::int32_t(__stdcall*)(bool);
	static function_t fn = reinterpret_cast<function_t>(GetProcAddress(GetModuleHandle(L"SDL2.dll"), "SDL_SetRelativeMouseMode"));

	fn(mode);
}

void sdl::set_window_polling_mode(void* window, bool mode)
{
	using function_t = void(__stdcall*)(void*, bool);
	static function_t fn = reinterpret_cast<function_t>(GetProcAddress(GetModuleHandle(L"SDL2.dll"), "SDL_SetWindowGrab"));

	fn(window, mode);
}

void sdl::set_mouse_warp_position(void* window, std::int32_t x, std::int32_t y)
{
	using function_t = void(__stdcall*)(void*, std::int32_t, std::int32_t);
	static function_t fn = reinterpret_cast<function_t>(GetProcAddress(GetModuleHandle(L"SDL2.dll"), "SDL_WarpMouseInWindow"));

	fn(window, x, y);
}
