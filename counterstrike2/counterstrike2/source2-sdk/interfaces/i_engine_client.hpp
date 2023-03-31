#pragma once

class i_engine_client
{
public:
	bool is_in_game()
	{
		using function_t = bool(__thiscall*)(i_engine_client*);
		return (*reinterpret_cast<function_t**>(this))[30](this);
	}

	bool is_connected()
	{
		using function_t = bool(__thiscall*)(i_engine_client*);
		return (*reinterpret_cast<function_t**>(this))[31](this);
	}

	void get_screen_size(std::int32_t& width, std::int32_t& height)
	{
		using function_t = void(__thiscall*)(i_engine_client*, int&, int&);
		return (*reinterpret_cast<function_t**>(this))[48](this, width, height);
	}

	const char* get_level_name()
	{
		using function_t = const char*(__thiscall*)(i_engine_client*);
		return (*reinterpret_cast<function_t**>(this))[51](this);
	}

	const char* get_level_name_short()
	{
		using function_t = const char* (__thiscall*)(i_engine_client*);
		return (*reinterpret_cast<function_t**>(this))[52](this);
	}
};