#include "anti_aim.hpp"

#include "../config/config.hpp"
#include "../source2-sdk/sdk.hpp"

#include <ctime>

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

    vec3_t angles = vec3_t(89.f, 180.f + 180.f, 0.f);
    angles.y = random_angle(-35, 35);

    cmd->set_sub_tick_angles(angles);
    cmd->base->view->angles = angles;
}