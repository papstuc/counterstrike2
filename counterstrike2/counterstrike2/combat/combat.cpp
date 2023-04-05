#include "combat.hpp"

#include "../config/config.hpp"
#include "../source2-sdk/sdk.hpp"

#include <cmath>

void combat::run_aimbot(c_user_cmd* cmd)
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

    float target_fov = config::context.aimbot_fov;
    vec3_t best_target = vec3_t();
    vec3_t local_eye_position = sdk::local_player->get_eye_position();

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

        vec3_t bone_position = player->get_eye_position();

        vec3_t angle = math::calculate_angle(local_eye_position, bone_position, cmd->base->view->angles);
        angle.clamp();

        float fov = std::hypotf(angle.x, angle.y);
        if (fov < target_fov)
        {
            best_target = bone_position;
            target_fov = fov;
        }
    }

    if (best_target.is_zero())
    {
        return;
    }

    vec3_t angle = math::calculate_angle(local_eye_position, best_target, cmd->base->view->angles);
    angle.clamp();

    cmd->base->view->angles += angle;
    interfaces::csgo_input->set_view_angles(cmd->base->view->angles);
}