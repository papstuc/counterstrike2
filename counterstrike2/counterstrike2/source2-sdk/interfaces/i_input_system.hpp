#pragma once

#include <cstdint>

class i_input_system
{
public:
	void* get_sdl_window()
	{
		return *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(this) + 0x2670);
	}

	bool is_relative_mouse_mode()
	{
		return *reinterpret_cast<bool*>(reinterpret_cast<std::uint8_t*>(this) + 0x4F);
	}
};