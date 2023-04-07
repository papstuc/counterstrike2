#include "anti_aim.hpp"

#include "../config/config.hpp"
#include "../source2-sdk/sdk.hpp"

#include <ctime>
#include <cmath>

static float random_angle(std::int32_t min, std::int32_t max)
{
    static bool first = true;
    if (first)
    {
        std::srand(static_cast<std::uint32_t>(std::time(nullptr)));
        first = false;
    }
    return static_cast<float>(min + std::rand() % ((max + 1) - min));
}

void anti_aim::run_anti_aim(c_user_cmd* cmd)
{
    if (!config::context.anti_aim)
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

    if (cmd->buttons & buttons_t::in_attack)
    {
        return;
    }

    if (sdk::local_player->move_type() == movetype_t::movetype_ladder || sdk::local_player->move_type() == movetype_t::movetype_noclip)
    {
        return;
    }

    vec3_t engine_angles;
    interfaces::csgo_input->get_view_angles(engine_angles);
    float yaw_base = engine_angles.y;

    vec3_t angles = vec3_t(89.f, yaw_base + 180.f, 0.f);
    //angles.y += random_angle(-20, 20);

    //cmd->set_sub_tick_angles(angles);
    cmd->base->view->angles = angles;
}

bool anti_aim::should_choke()
{
    if (!config::context.fake_lag)
    {
        return false;
    }

    if (!interfaces::engine->is_connected() || !interfaces::engine->is_in_game())
    {
        return false;
    }

    if (!sdk::local_player || !sdk::local_player->is_alive())
    {
        return false;
    }

    return false;
}
