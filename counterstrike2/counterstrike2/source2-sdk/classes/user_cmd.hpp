#pragma once

#include <cstdint>
#include "../math/vec3_t.hpp"

class cmd_qangle_t
{
public:
    char pad1[0x18];
    vec3_t angles;
};

static_assert(sizeof(cmd_qangle_t) == 0x24, "cmd_qangle_t has wrong size");

class user_cmd_base_t
{
public:
    char pad1[0x40];
    cmd_qangle_t* view;
};

static_assert(sizeof(user_cmd_base_t) == 0x48, "user_cmd_base_t has wrong size");

class user_cmd_t
{
public:
    char pad1[0x30];
    user_cmd_base_t* base;
    char pad2[0x18];
    std::uint32_t buttons;
};

static_assert(sizeof(user_cmd_t) == 0x58, "user_cmd_t has wrong size");