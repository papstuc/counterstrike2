#pragma once

#include "../classes/global_vars.hpp"
#include "i_csgo_input.hpp"
#include "i_engine_client.hpp"
#include "i_schema_system.hpp"
#include "i_render.hpp"
#include "i_entity_list.hpp"

namespace interfaces
{
	extern global_vars_t* globals;
	extern i_csgo_input* csgo_input;
	extern i_render* render;
	extern i_engine_client* engine;
	extern i_schema_system* schema_system;
	extern i_entity_list* entity_list;

	bool initialize();
}