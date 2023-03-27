#include "interfaces.hpp"

#include "../../utilities/utilities.hpp"

global_vars_t* interfaces::global_vars = nullptr;

bool interfaces::initialize()
{
	interfaces::global_vars = *reinterpret_cast<global_vars_t**>(utilities::resolve_rip(utilities::pattern_scan(L"client.dll", "48 8B 05 ? ? ? ? 4C 8D 0D ? ? ? ? F2 0F 11 74 24 ? 4C 8D 05 ? ? ? ? BA"), 3, 7));

	return true;
}
