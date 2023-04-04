#include "combat.hpp"

#include "../config/config.hpp"
#include "../source2-sdk/sdk.hpp"

#include <cmath>

static bool can_see_player_position(player_t* local_player, std::uint32_t local_player_handle, player_t* player, std::uint32_t player_handle, vec3_t& position)
{
    trace_filter_t filter = { };
    filter.unknown1[0] = 0;
    filter.unknown1[1] = 0;
    filter.unknown2 = 7;
    filter.layer = 4;
    filter.unknown3 = 0x49;
    //filter.unknown3 |= 2;

    filter.unknown4 = 0;

    filter.skip_handles[0] = local_player_handle;
    filter.skip_handles[1] = 0;
    filter.skip_handles[2] = local_player->owner_handle();
    filter.skip_handles[3] = 0;

    filter.collisions[0] = local_player->collision_property()->get_collision_mask();
    filter.collisions[1] = 0;

    filter.mask = 0x1C1003;

    ray_t ray = { };
    game_trace_t trace = { };

    vec3_t eye_position = local_player->get_eye_position();
    interfaces::trace->trace_shape(&ray, eye_position, position, &filter, &trace);

    if (trace.fraction == 1.f)
    {
        return false;
    }

    return true;
}

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

        vec3_t bone_position = player->get_bone_position(8);

        /*if (!can_see_player_position(sdk::local_player, pawn_handle, player, handle, bone_position))
        {
            continue;
        }*/

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