#include "interfaces.hpp"
#include "../../utilities/utilities.hpp"

#include <Windows.h>

i_global_vars_t* interfaces::global_vars = nullptr;
i_csgo_input* interfaces::csgo_input = nullptr;

template<typename T>
static T* get_interface(const wchar_t* module_name, const char* interface_name)
{
	using function_t = void*(__fastcall*)(const char*, DWORD*);
	static function_t p_create_interface = reinterpret_cast<decltype(p_create_interface)>(GetProcAddress(GetModuleHandle(module_name), "CreateInterface"));

	return reinterpret_cast<T*>(p_create_interface(interface_name, nullptr));
}

bool interfaces::initialize()
{
	interfaces::global_vars = *reinterpret_cast<i_global_vars_t**>(utilities::resolve_rip(utilities::pattern_scan(L"client.dll", "48 8B 05 ? ? ? ? 4C 8D 0D ? ? ? ? F2 0F 11 74 24 ? 4C 8D 05 ? ? ? ? BA"), 3, 7));
	interfaces::csgo_input = get_interface<i_csgo_input>(L"client.dll", "InputService_001");

	return true;
}
