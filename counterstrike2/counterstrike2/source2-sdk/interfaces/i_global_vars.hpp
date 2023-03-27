#pragma once

#include <cstdint>

class i_global_vars_t
{
public:
    float realtime;
    std::int32_t framecount;
    unsigned char pad1[0x8];
    std::int32_t maxclients;
    float intervalpertick;
    unsigned char pad2[0x12];
    float curtime;
    float curtime2;
    unsigned char pad3[0xC];
    std::int32_t m_tickcount;
    float intervalpertick2;
    void* current_netchan;
    unsigned char pad4[0x130];
    char* current_map;
    char* current_mapname;
};

static_assert(sizeof(i_global_vars_t) == 0x0190, "global_vars_t has wrong size");