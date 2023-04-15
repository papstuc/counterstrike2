#pragma once

#include <cstdint>
#include "../math/vec3_t.hpp"

class c_cmd_qangle
{
public:
    char pad1[0x18];
    vec3_t angles;
};
static_assert(sizeof(c_cmd_qangle) == 0x24);

class c_sub_tick_cmd
{
public:
    char pad1[0x18];
    c_cmd_qangle* view;
};
static_assert(sizeof(c_sub_tick_cmd) == 0x20);

class c_sub_tick_container
{
public:
    std::int32_t tick_count;
    char pad1[0x4];
    std::uint8_t* tick_pointer;

    c_sub_tick_cmd* get_tick(std::int32_t index)
    {
        if (index < this->tick_count)
        {
            c_sub_tick_cmd** tick_list = reinterpret_cast<c_sub_tick_cmd**>(this->tick_pointer + 0x8);
            return tick_list[index];
        }

        return nullptr;
    }
};
static_assert(sizeof(c_sub_tick_container) == 0x10);

class c_user_cmd_base
{
public:
    char pad1[0x40];
    c_cmd_qangle* view;
    char pad2[0x8];
    float forwardmove;
    float sidemove;
};
static_assert(sizeof(c_user_cmd_base) == 0x58);

class c_user_cmd
{
public:
    char pad1[0x20];
    c_sub_tick_container sub_tick_container;
    c_user_cmd_base* base;
    char pad2[0x18];
    std::uint32_t buttons;

    void set_sub_tick_angles(vec3_t& angles)
    {
        c_sub_tick_container container = this->sub_tick_container;
        for (std::int32_t i = 0; i < container.tick_count; i++)
        {
            c_sub_tick_cmd* tick = container.get_tick(i);

            if (tick && tick->view)
            {
                tick->view->angles = angles;
            }
        }
    }
};
static_assert(sizeof(c_user_cmd) == 0x58);