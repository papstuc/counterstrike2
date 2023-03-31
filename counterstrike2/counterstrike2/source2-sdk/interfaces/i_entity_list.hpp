#pragma once

#include "../../utilities/utilities.hpp"
#include "../classes/entities.hpp"

class i_entity_list
{
public:
	controller_t* get_controller_by_index(std::int32_t index)
	{
		using function_t = controller_t*(__fastcall*)(i_entity_list*, std::int32_t);
		static function_t fn = reinterpret_cast<function_t>(utilities::pattern_scan(L"client.dll", "81 FA ? ? ? ? 77 3B 8B C2"));

		return fn(this, index);
	}

	player_t* get_player_from_controller(controller_t* controller)
	{
		using function_t = player_t*(__fastcall*)(controller_t*);
		static function_t fn = reinterpret_cast<function_t>(utilities::pattern_scan(L"client.dll", "4C 8B 05 ?? ?? ?? ?? 4D 85 C0 74 39 8B 89 D4 05"));

		return fn(controller);
	}
};