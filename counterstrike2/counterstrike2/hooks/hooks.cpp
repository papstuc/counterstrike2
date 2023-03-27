#include "hooks.hpp"

#include "../utilities/minhook/MinHook.h"

#include "../utilities/shadow_vmt/shadow_vmt.hpp"
#include "../utilities/utilities.hpp"
#include "../utilities/debug/debug.hpp"

#include "../source2-sdk/interfaces/interfaces.hpp"

static hooks::createmove::function_t createmove_original = nullptr;

static void* get_virtual(void* class_pointer, std::uint32_t index)
{
	void** vtable = *static_cast<void***>(class_pointer);
	return vtable[index];
}

bool hooks::initialize()
{
	void* createmove_target = get_virtual(interfaces::csgo_input, csgo_input_vtable::CREATEMOVE);

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

void hooks::release()
{
	MH_Uninitialize();
	MH_DisableHook(MH_ALL_HOOKS);
}

std::byte* __fastcall hooks::createmove::hook(void* csgoinput, unsigned int a2, unsigned __int8 a3)
{
	debug::log(L"createmove called\n");
	return createmove_original(csgoinput, a2, a3);
}
