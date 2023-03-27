#include "hooks.hpp"

#include "../utilities/minhook/MinHook.h"

#include "../utilities/shadow_vmt/shadow_vmt.hpp"
#include "../utilities/utilities.hpp"
#include "../utilities/debug/debug.hpp"

#include "../source2-sdk/interfaces/interfaces.hpp"

static hooks::createmove::function_t createmove_original = nullptr;

template <typename T = void*>
inline T get_virtual(std::uint32_t uIndex, void* class_pointer)
{
	void** vtable = *static_cast<void***>(class_pointer);
	return reinterpret_cast<T>(vtable[uIndex]);
}

bool hooks::initialize()
{
	//std::uint8_t* createmove_target = utilities::pattern_scan(L"client.dll", "48 8B C4 48 89 58 ? 48 89 48 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8");

	std::uint8_t* createmove_target = get_virtual<std::uint8_t*>(5, interfaces::csgo_input);

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
