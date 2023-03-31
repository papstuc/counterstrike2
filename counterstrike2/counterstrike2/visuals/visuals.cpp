#include <array>
#include "visuals.hpp"

#include "../utilities/utilities.hpp"
#include "../source2-sdk/sdk.hpp"

typedef struct _box_t
{
    float x, y, w, h;
} box_t;

static bool get_bounding_box(player_t* player, box_t& box)
{
    vec3_t origin = player->game_scene_node()->abs_origin();

    vec3_t flb, brt, blb, frt, frb, brb, blt, flt;
    float left, top, right, bottom;

    vec3_t min = player->collision_property()->mins() + origin;
    vec3_t max = player->collision_property()->maxs() + origin;

    std::array<vec3_t, 8> points = {
        vec3_t(min.x, min.y, min.z),
        vec3_t(min.x, min.y, max.z),
        vec3_t(min.x, max.y, min.z),
        vec3_t(min.x, max.y, max.z),
        vec3_t(max.x, min.y, min.z),
        vec3_t(max.x, min.y, max.z),
        vec3_t(max.x, max.y, min.z),
        vec3_t(max.x, max.y, max.z) };

    if (!math::world_to_screen(points[3], flb)
        || !math::world_to_screen(points[5], brt)
        || !math::world_to_screen(points[0], blb)
        || !math::world_to_screen(points[4], frt)
        || !math::world_to_screen(points[2], frb)
        || !math::world_to_screen(points[1], brb)
        || !math::world_to_screen(points[6], blt)
        || !math::world_to_screen(points[7], flt))
    {
        return false;
    }

    std::array<vec3_t, 8> arr = { flb, brt, blb, frt, frb, brb, blt, flt };

    left = flb.x;
    top = flb.y;
    right = flb.x;
    bottom = flb.y;

    for (std::int32_t i = 1; i < 8; i++)
    {
        if (left > arr[i].x)
        {
            left = arr[i].x;
        }

        if (bottom < arr[i].y)
        {
            bottom = arr[i].y;
        }

        if (right < arr[i].x)
        {
            right = arr[i].x;
        }

        if (top > arr[i].y)
        {
            top = arr[i].y;
        }
    }

    box.x = left;
    box.y = top;
    box.w = right - left;
    box.h = bottom - top;


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

        renderer::rect(box.x, box.y, box.w, box.h, color_t::red());
    }
}
