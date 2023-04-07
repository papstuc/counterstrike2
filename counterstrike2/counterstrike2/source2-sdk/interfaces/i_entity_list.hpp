#pragma once

#include "../../signatures.hpp"
#include "../../utilities/utilities.hpp"
#include "../classes/entities.hpp"

class i_entity_list
{
public:
	controller_t* get_controller_by_index(std::int32_t index)
	{
		using function_t = controller_t*(__fastcall*)(i_entity_list*, std::int32_t);
		static function_t fn = reinterpret_cast<function_t>(utilities::pattern_scan(L"client.dll", GET_CONTROLLER_BY_INDEX));

		return fn(this, index);
	}

	player_t* get_player_from_controller(controller_t* controller)
	{
		using function_t = player_t*(__fastcall*)(controller_t*);
		static function_t fn = reinterpret_cast<function_t>(utilities::pattern_scan(L"client.dll", GET_PLAYER_FROM_CONTROLLER));

		return fn(controller);
	}

	player_t* get_local_player()
	{
		using function_t = void* (__fastcall*)(std::int32_t);
		static function_t fn = reinterpret_cast<function_t>(utilities::pattern_scan(L"client.dll", GET_LOCAL_PLAYER));

		return static_cast<player_t*>(fn(0));
	}

	controller_t* get_local_controller()
	{
		static controller_t* controller = reinterpret_cast<controller_t*>(utilities::resolve_rip(utilities::pattern_scan(L"client.dll", GET_LOCAL_CONTROLLER), 2, 6));
		return controller;
	}

	entity_t* get_entity_from_handle(std::uint32_t handle)
	{
		using function_t = entity_t*(__fastcall*)(i_entity_list*, std::uint32_t);
		static function_t fn = reinterpret_cast<function_t>(utilities::pattern_scan(L"client.dll", GET_ENTITY_FROM_HANDLE));

		return fn(this, handle);
	}

	std::uint32_t get_handle_from_entity(entity_t* entity)
	{
		using function_t = std::uint32_t(__fastcall*)(entity_t*);
		static function_t fn = reinterpret_cast<function_t>(utilities::pattern_scan(L"client.dll", GET_HANDLE_FROM_ENTITY));

		return fn(entity);
	}
};