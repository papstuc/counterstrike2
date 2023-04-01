#pragma once

#include <cstdint>

class cmd_qangle_t
{
public:
    char pad1[0x18];
    float x;
    float y;
    float z;
    char pad2[0x41C];
};

static_assert(sizeof(cmd_qangle_t) == 0x440, "cmd_qangle has wrong size");

class user_cmd_base_t
{
public:
    char pad1[0x40];
    cmd_qangle_t* view_angles;
    char pad2[0x3F8];
};

static_assert(sizeof(user_cmd_base_t) == 0x440, "user_cmd_base_t has wrong size");

class user_cmd_t
{
public:
    char pad1[0x30];
    user_cmd_base_t* base;
    char pad2[0x18];
    std::uint32_t buttons;
    char pad3[0x3EC];
};

static_assert(sizeof(user_cmd_t) == 0x440, "user_cmd_t has wrong size");