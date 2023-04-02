#include "interfaces.hpp"

#include "../../signatures.hpp"
#include "../../utilities/utilities.hpp"
#include "../../utilities/debug_console/debug.hpp"

#include <Windows.h>

i_client* interfaces::client = nullptr;
i_csgo_input* interfaces::csgo_input = nullptr;
i_engine_client* interfaces::engine = nullptr;
i_entity_list* interfaces::entity_list = nullptr;
i_input_system* interfaces::input_system = nullptr;
i_renderer* interfaces::renderer = nullptr;
i_schema_system* interfaces::schema_system = nullptr;
i_trace* interfaces::trace = nullptr;
global_vars_t* interfaces::globals = nullptr;

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
	interfaces::client = get_interface<i_client>(L"client.dll", "Source2Client002");
	interfaces::csgo_input = *reinterpret_cast<i_csgo_input**>(utilities::resolve_rip(utilities::pattern_scan(L"client.dll", CSGO_INPUT), 3, 7));
	interfaces::engine = get_interface<i_engine_client>(L"engine2.dll", "Source2EngineToClient001");
	interfaces::entity_list = *reinterpret_cast<i_entity_list**>(utilities::resolve_rip(utilities::pattern_scan(L"client.dll", ENTITY_LIST), 3, 7));
	interfaces::input_system = get_interface<i_input_system>(L"inputsystem.dll", "InputSystemVersion001");
	interfaces::renderer = **reinterpret_cast<i_renderer***>(utilities::resolve_rip(utilities::pattern_scan(L"rendersystemdx11.dll", RENDERER), 4, 8));
	interfaces::schema_system = get_interface<i_schema_system>(L"schemasystem.dll", "SchemaSystem_001");
	interfaces::trace = *reinterpret_cast<i_trace**>(utilities::resolve_rip(utilities::pattern_scan(L"client.dll", TRACE_MANAGER), 3, 7));
	interfaces::globals = *reinterpret_cast<global_vars_t**>(utilities::resolve_rip(utilities::pattern_scan(L"client.dll", GLOBAL_VARS), 3, 7));

	if (!interfaces::csgo_input || !interfaces::engine || !interfaces::entity_list || !interfaces::input_system || !interfaces::renderer || !interfaces::schema_system || !interfaces::trace || !interfaces::globals)
	{
		debug::log("[-] failed to initialize interfaces\n");
		return false;
	}

	debug::log("[+] interfaces initialized\n");
	return true;
}