#include "combat.hpp"

#include "../config/config.hpp"
#include "../source2-sdk/sdk.hpp"

#include <cmath>
#include <vector>

static std::vector<std::uint32_t> bones;

static bool can_see_player_position(player_t* player, vec3_t& position)
{
    c_trace_filter filter(0x1C300B, sdk::local_player, 3);
    c_ray ray = { };
    c_game_trace trace = { };

    vec3_t eye_position = sdk::local_player->get_eye_position();
    interfaces::trace->trace_shape(&ray, eye_position, position, &filter, &trace);

    return trace.entity == player || trace.fraction > 0.97f;
}

void combat::run_legitbot(c_user_cmd* cmd)
{
	if (!config::context.legitbot)
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

    if (sdk::local_player->move_type() == movetype_t::movetype_ladder || sdk::local_player->move_type() == movetype_t::movetype_noclip)
    {
        return;
    }

    float target_fov = config::context.legit_fov;
    vec3_t best_target = vec3_t();
    vec3_t local_eye_position = sdk::local_player->get_eye_position();
    vec3_t cmd_angles = cmd->base->view->angles;

    if (config::context.hitboxes[0])
    {
        bones.emplace_back(5); // neck
        bones.emplace_back(6); // head
    }

    if (config::context.hitboxes[1])
    {
        bones.emplace_back(0); // pelvis
        bones.emplace_back(1); // spine_0
        bones.emplace_back(2); // spine_1
        bones.emplace_back(3); // spine_2
        bones.emplace_back(4); // spine_3
    }

    if (config::context.hitboxes[2])
    {
        bones.emplace_back(10); // arm_upper_l
        bones.emplace_back(11); // arm_lower_l
        bones.emplace_back(15); // arm_upper_r
        bones.emplace_back(16); // arm_lower_r
    }

    if (config::context.hitboxes[3])
    {
        bones.emplace_back(23); // leg_upper_l
        bones.emplace_back(24); // leg_lower_l
        bones.emplace_back(26); // leg_upper_r
        bones.emplace_back(27); // leg_lower_r
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

        if (!player || !player->is_alive() || player->game_scene_node()->dormant() || player->has_gun_immunity())
        {
            continue;
        }

        if (player->team() == sdk::local_player->team())
        {
            continue;

        }
        vec3_t bone_position = { };
        vec3_t bone_rotation = { };

        for (std::uint32_t bone_id : bones)
        {
            player->get_bone_position(bone_id, bone_position, bone_rotation);

            if (!can_see_player_position(player, bone_position))
            {
                continue;
            }

            vec3_t angle = math::calculate_angle(local_eye_position, bone_position, cmd_angles);
            angle.clamp();

            float fov = std::hypotf(angle.x, angle.y);
            if (fov < target_fov)
            {
                best_target = bone_position;
                target_fov = fov;
            }
        }
    }

    bones.clear();

    if (best_target.is_zero())
    {
        return;
    }

    vec3_t angle = math::calculate_angle(local_eye_position, best_target, cmd_angles);
    angle.clamp();

    angle /= config::context.smooth;

    cmd_angles += angle;
    cmd->set_sub_tick_angles(cmd_angles);

    if (!config::context.silent_aim)
    {
        cmd->base->view->angles = cmd_angles;
        interfaces::csgo_input->set_view_angles(cmd->base->view->angles);
    }
}