#include <cmath>
#include <limits>
#include "visuals.hpp"

#include "../utilities/utilities.hpp"
#include "../source2-sdk/sdk.hpp"

typedef struct _box_t
{
    float x, y, w, h;
} box_t;

static bool get_bounding_box(player_t* player, box_t& box)
{
	vec3_t min = player->collision_property()->mins();
	vec3_t max = player->collision_property()->maxs();

    return true;
}

void visuals::run_player_esp()
{
    if (!interfaces::engine->is_connected() || !interfaces::engine->is_in_game())
    {
        return;
    }

    for (std::int32_t i = 1; i <= interfaces::globals->maxclients; i++)
    {
        void* entity = sdk::get_entity_index(i);

        if (!entity)
        {
            continue;
        }

        player_t* player = reinterpret_cast<player_t*>(sdk::get_player_pawn(entity));

        if (!player || !player->is_alive())
        {
            continue;
        }

        box_t box = { };
        if (!get_bounding_box(player, box))
        {
            continue;
        }

        renderer::rect(box.x, box.y, box.w, box.h, color_t::black());
    }
}
