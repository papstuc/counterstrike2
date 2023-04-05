#pragma once

#include <cstdint>
#include "../math/vec3_t.hpp"

class c_cmd_qangle
{
public:
    char pad1[0x18];
    vec3_t angles;
};
static_assert(sizeof(c_cmd_qangle) == 0x24, "c_cmd_qangle has wrong size");

class c_user_cmd_base
{
public:
    char pad1[0x40];
    c_cmd_qangle* view;
};
static_assert(sizeof(c_user_cmd_base) == 0x48, "c_user_cmd_base has wrong size");

class c_user_cmd
{
public:
    char pad1[0x30];
    c_user_cmd_base* base;
    char pad2[0x18];
    std::uint32_t buttons;
};

static_assert(sizeof(c_user_cmd) == 0x58, "c_user_cmd has wrong size");