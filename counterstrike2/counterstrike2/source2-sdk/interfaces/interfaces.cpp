#include <Windows.h>

#include "interfaces.hpp"
#include "../../utilities/utilities.hpp"
#include "../../utilities/debug/debug.hpp"

i_global_vars_t* interfaces::global_vars = nullptr;
i_csgo_input* interfaces::csgo_input = nullptr;

bool interfaces::initialize()
{
	interfaces::global_vars = *reinterpret_cast<i_global_vars_t**>(utilities::resolve_rip(utilities::pattern_scan(L"client.dll", "48 8B 05 ? ? ? ? 4C 8D 0D ? ? ? ? F2 0F 11 74 24 ? 4C 8D 05 ? ? ? ? BA"), 3, 7));
	interfaces::csgo_input = *reinterpret_cast<i_csgo_input**>(utilities::resolve_rip(utilities::pattern_scan(L"client.dll", "48 8B 0D ? ? ? ? 4C 8D 8F ? ? ? ? 33 ED"), 3, 7));

	debug::log("[+] interfaces initialized\n");
	return true;
}
