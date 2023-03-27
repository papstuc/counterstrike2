#pragma once

#include "i_global_vars.hpp"
#include "i_csgo_input.hpp"

namespace interfaces
{
	extern i_global_vars_t* global_vars;
	extern i_csgo_input* csgo_input;

	bool initialize();
}