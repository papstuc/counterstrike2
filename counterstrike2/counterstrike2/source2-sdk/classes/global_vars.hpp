#pragma once

#include <cstdint>

class c_global_vars
{
public:
	float real_time;
	std::uint32_t frame_count;
	float frame_time;
	float frame_time2;
	std::uint32_t max_clients;
	float interval_per_tick;
	char pad_0018[20];
	float current_time;
	float current_time2;
	char pad_0034[4];
	std::uint32_t tick_count;
	float interval_per_tick2;
	void* net_channel;
	char pad_0048[312];
	char* current_map;
	char* current_map_name;
};
static_assert(sizeof(c_global_vars) == 0x190);