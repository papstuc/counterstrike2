#include "interfaces.hpp"
#include "../../utilities/utilities.hpp"
#include "../../utilities/debug_console/debug.hpp"

#include <Windows.h>

global_vars_t* interfaces::globals = nullptr;
i_csgo_input* interfaces::csgo_input = nullptr;
i_render* interfaces::render = nullptr;
i_engine_client* interfaces::engine = nullptr;
i_schema_system* interfaces::schema_system = nullptr;
i_entity_list* interfaces::entity_list = nullptr;

template<typename T>
static T* get_interface(const wchar_t* module_name, const char* interface_name)
{
	if (!module_name || !interface_name)
	{
		return nullptr;
	}

	HMODULE module = GetModuleHandle(module_name);

	if (!module)
	{
		return nullptr;
	}

	std::uint8_t* create_interface = reinterpret_cast<std::uint8_t*>(GetProcAddress(module, "CreateInterface"));

	if (!create_interface)
	{
		return nullptr;
	}

	using interface_callback_fn = void*(__cdecl*)();

	typedef struct _interface_reg_t
	{
		interface_callback_fn callback;
		const char* name;
		_interface_reg_t* flink;
	} interface_reg_t;

	interface_reg_t* interface_list = *reinterpret_cast<interface_reg_t**>(utilities::resolve_rip(create_interface, 3, 7));

	if (!interface_list)
	{
		return nullptr;
	}

	for (interface_reg_t* it = interface_list; it; it = it->flink)
	{
		if (!strcmp(it->name, interface_name))
		{
			return reinterpret_cast<T*>(it->callback());
		}
	}

	return nullptr;
}

bool interfaces::initialize()
{
	interfaces::globals = *reinterpret_cast<global_vars_t**>(utilities::resolve_rip(utilities::pattern_scan(L"client.dll", "48 8B 05 ? ? ? ? 4C 8D 0D ? ? ? ? F2 0F 11 74 24 ? 4C 8D 05 ? ? ? ? BA"), 3, 7));
	interfaces::csgo_input = *reinterpret_cast<i_csgo_input**>(utilities::resolve_rip(utilities::pattern_scan(L"client.dll", "48 8B 0D ? ? ? ? 4C 8D 8F ? ? ? ? 33 ED"), 3, 7));
	interfaces::render = **reinterpret_cast<i_render***>(utilities::resolve_rip(utilities::pattern_scan(L"rendersystemdx11.dll", "66 0F 7F 05 ? ? ? ? 66 0F 7F 0D ? ? ? ? 48 89 35"), 4, 8));
	interfaces::engine = get_interface<i_engine_client>(L"engine2.dll", "Source2EngineToClient001");
	interfaces::schema_system = get_interface<i_schema_system>(L"schemasystem.dll", "SchemaSystem_001");
	interfaces::entity_list = *reinterpret_cast<i_entity_list**>(utilities::resolve_rip(utilities::pattern_scan(L"client.dll", "48 8B 0D ? ? ? ? 8B D3 E8 ? ? ? ? 48 8B F0"), 3, 7));

	debug::log("[+] interfaces initialized\n");
	return true;
}