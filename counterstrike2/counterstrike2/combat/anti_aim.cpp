#include "anti_aim.hpp"

#include "../config/config.hpp"
#include "../source2-sdk/sdk.hpp"

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
}