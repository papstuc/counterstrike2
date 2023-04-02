#include "combat.hpp"

#include "../config/config.hpp"
#include "../source2-sdk/sdk.hpp"

void run_aimbot(user_cmd_t* cmd)
{
	if (!config::context.aimbot)
	{
		return;
	}

    if (!interfaces::engine->is_connected() || !interfaces::engine->is_in_game())
    {
        return;
    }

    if (!sdk::local_player || !sdk::local_player->is_alive())
    {
        return;
    }

    for (std::uint32_t i = 0; i < interfaces::globals->max_clients; i++)
    {
        controller_t* controller = interfaces::entity_list->get_controller_by_index(i);

        if (!controller)
        {
            continue;
        }

        player_t* player = interfaces::entity_list->get_player_from_controller(controller);

        if (!player)
        {
            continue;
        }

        if (!player || !player->is_alive() || player->game_scene_node()->dormant())
        {
            continue;
        }

        if (player->team() == sdk::local_player->team())
        {
            continue;
        }
    }
}