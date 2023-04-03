#include "combat.hpp"

#include "../config/config.hpp"
#include "../source2-sdk/sdk.hpp"

#include <cmath>

void combat::run_aimbot(user_cmd_t* cmd)
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

    float target = config::context.aimbot_fov;
    vec3_t best_target = vec3_t();
    vec3_t local_eye_position = sdk::local_player->get_eye_pos();
    vec3_t view_angles(cmd->base->view_angles->x, cmd->base->view_angles->y, cmd->base->view_angles->z);

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

        if (!player || !player->is_alive() || player->game_scene_node()->dormant() || player->has_gun_immunity())
        {
            continue;
        }

        if (player->team() == sdk::local_player->team())
        {
            continue;
        }
    }
}