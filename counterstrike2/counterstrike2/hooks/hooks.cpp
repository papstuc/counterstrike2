#include "hooks.hpp"

#include "../utilities/minhook/MinHook.h"
#include "../utilities/utilities.hpp"
#include "../utilities/debug_console/debug.hpp"

#include "../source2-sdk/interfaces/interfaces.hpp"
#include "../source2-sdk/sdk.hpp"
#include "../skins/skins.hpp"

static hooks::create_move::function_t create_move_original = nullptr;
static hooks::level_init::function_t level_init_original = nullptr;
static hooks::frame_stage_notify::function_t frame_stage_notify_original = nullptr;

bool hooks::initialize()
{
	void* create_move_target = utilities::get_virtual(interfaces::csgo_input, csgo_input_vtable::CREATEMOVE);
	void* level_init_target = utilities::pattern_scan(L"client.dll", "48 89 5C 24 ? 57 48 83 EC ? 48 8B 0D ? ? ? ? 48 8B DA 45 33 C9");
	void* frame_stage_notify_target = utilities::pattern_scan(L"client.dll", "48 89 5C 24 ? 56 48 83 EC ? 8B 05 ? ? ? ? 8D 5A");

	if (MH_Initialize() != MH_OK)
	{
		debug::log(L"[-] failed to initialize minhook\n");
		return false;
	}

	if (MH_CreateHook(create_move_target, &hooks::create_move::hook, reinterpret_cast<void**>(&create_move_original)) != MH_OK)
	{
		debug::log(L"[-] failed to hook CSGOInput!CreateMove\n");
		return false;
	}

	if (MH_CreateHook(level_init_target, &hooks::level_init::hook, reinterpret_cast<void**>(&level_init_original)) != MH_OK)
	{
		debug::log(L"[-] failed to hook CSGOInput!CreateMove\n");
		return false;
	}

	if (MH_CreateHook(frame_stage_notify_target, &hooks::frame_stage_notify::hook, reinterpret_cast<void**>(&frame_stage_notify_original)) != MH_OK)
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

std::byte* __fastcall hooks::create_move::hook(void* csgoinput, unsigned int a2, unsigned __int8 a3)
{
	return create_move_original(csgoinput, a2, a3);
}

std::int64_t __fastcall hooks::level_init::hook(std::int64_t a1, std::int64_t a2)
{
	interfaces::global_vars = *reinterpret_cast<global_vars_t**>(utilities::resolve_rip(utilities::pattern_scan(L"client.dll", "48 8B 05 ? ? ? ? 4C 8D 0D ? ? ? ? F2 0F 11 74 24 ? 4C 8D 05 ? ? ? ? BA"), 3, 7));
	return level_init_original(a1, a2);
}

std::int64_t __fastcall hooks::frame_stage_notify::hook(std::int64_t a1, std::int32_t a2)
{
	return frame_stage_notify_original(a1, a2);
}
