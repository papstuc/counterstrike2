#pragma once

#include "../classes/global_vars.hpp"
#include "i_csgo_input.hpp"
#include "i_engine_client.hpp"
#include "i_schema_system.hpp"

namespace interfaces
{
	extern global_vars_t* global_vars;
	extern i_csgo_input* csgo_input;
	extern i_engine_client* engine;
	extern i_schema_system* schema_system;

	bool initialize();
}