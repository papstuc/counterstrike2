#include "sdk.hpp"

#include "../signatures.hpp"
#include "../utilities/utilities.hpp"

controller_t* sdk::local_controller = nullptr;
player_t* sdk::local_player = nullptr;
std::int32_t sdk::screen_width = 0;
std::int32_t sdk::screen_height = 0;

void sdk::update_local_controller()
{
	if (!interfaces::engine->is_connected() || !interfaces::engine->is_in_game())
	{
		sdk::local_player = nullptr;
		return;
	}

	sdk::local_controller = interfaces::entity_list->get_local_controller();
}

void sdk::update_local_player()
{
	if (!interfaces::engine->is_connected() || !interfaces::engine->is_in_game())
	{
		sdk::local_player = nullptr;
		return;
	}

	sdk::local_player = interfaces::entity_list->get_local_player();
}

void sdk::update_global_vars()
{
	interfaces::globals = *reinterpret_cast<global_vars_t**>(utilities::resolve_rip(utilities::pattern_scan(L"client.dll", GLOBAL_VARS), 3, 7));
}

void sdk::update_screen_size()
{
	interfaces::engine->get_screen_size(sdk::screen_width, sdk::screen_height);
}