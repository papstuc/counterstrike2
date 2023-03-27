#include "hooks.hpp"

#include "../utilities/minhook/MinHook.h"

#include "../utilities/shadow_vmt/shadow_vmt.hpp"
#include "../utilities/utilities.hpp"
#include "../utilities/debug/debug.hpp"

static hooks::createmove::function_t createmove_original = nullptr;

bool hooks::initialize()
{
	std::uint8_t* createmove_target = utilities::pattern_scan(L"client.dll", "48 8B C4 48 89 58 ? 48 89 48 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8");

	if (MH_Initialize() != MH_OK)
	{
		debug::log(L"[-] failed to initialize minhook\n");
		return false;
	}

	if (MH_CreateHook(createmove_target, &hooks::createmove::hook, reinterpret_cast<void**>(&createmove_original)) != MH_OK)
	{
		debug::log(L"[-] failed to hook CSGOInput!CreateMove\n");
		return false;
	}

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
	{
		debug::log(L"[-] failed to enable hooks\n");
		return false;
	}

	debug::log(L"[+] hooks initialized\n");

	return true;
}

std::byte* __fastcall hooks::createmove::hook(void* csgoinput, unsigned int a2, unsigned __int8 a3)
{
	debug::log(L"createmove called\n");
	return createmove_original(csgoinput, a2, a3);
}
