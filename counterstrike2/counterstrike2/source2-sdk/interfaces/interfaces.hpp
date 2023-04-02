#pragma once

#include "i_client.hpp"
#include "i_csgo_input.hpp"
#include "i_engine_client.hpp"
#include "i_entity_list.hpp"
#include "i_input_system.hpp"
#include "i_renderer.hpp"
#include "i_schema_system.hpp"
#include "i_trace.hpp"
#include "../classes/global_vars.hpp"

namespace interfaces
{
	extern i_client* client;
	extern i_csgo_input* csgo_input;
	extern i_engine_client* engine;
	extern i_entity_list* entity_list;
	extern i_input_system* input_system;
	extern i_renderer* renderer;
	extern i_schema_system* schema_system;
	extern i_trace* trace;
	extern global_vars_t* globals;

	bool initialize();
}