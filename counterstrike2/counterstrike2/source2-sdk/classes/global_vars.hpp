#pragma once

#include <cstdint>

class global_vars_t
{
public:
    float realtime;
    std::int32_t frame_count;
    char pad1[0x8];
    std::uint32_t max_clients;
    float intervalpertick;
    char pad2[0x12];
    float curtime;
    float curtime2;
    char pad3[0xC];
    std::int32_t tick_count;
    float intervalpertick2;
    void* current_netchan;
    char pad4[0x130];
    char* current_map;
    char* current_mapname;
};

static_assert(sizeof(global_vars_t) == 0x0190, "global_vars_t has wrong size");