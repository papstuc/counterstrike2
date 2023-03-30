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
};