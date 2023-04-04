#pragma once

#include <cstdint>
#include "entities.hpp"
#include "../math/vec3_t.hpp"

typedef struct _ray_t
{
	vec3_t start;
	vec3_t end;
	vec3_t mins;
	vec3_t maxs;
} ray_t;

static_assert(sizeof(ray_t) == 0x30, "ray_t has wrong size");

typedef struct _trace_hitbox_data_t
{
	char pad1[0x58];
	std::uint32_t hitgroup;
	char pad2[0x4];
	std::uint32_t hitbox_id;
} trace_hitbox_data_t;

static_assert(sizeof(trace_hitbox_data_t) == 0x64, "trace_hitbox_data_t has wrong size");

typedef struct _trace_filter_t
{
	std::uint64_t mask;
	std::uint64_t unknown1[2];
	std::uint32_t skip_handles[4];
	std::uint16_t collisions[2];
	std::uint16_t unknown2;
	std::uint8_t layer;
	std::uint8_t unknown3;
	std::uint8_t unknown4;
} trace_filter_t;

static_assert(sizeof(trace_filter_t) == 0x38, "trace_filter_t has wrong size");

typedef struct _game_trace_t
{
	void* surface;
	player_t* player;
	trace_hitbox_data_t* hitbox_data;
	char pad1[0x10];
	std::uint32_t contents;
	char pad2[0x58];
	vec3_t endpos;
	char pad3[0x1C];
	float fraction;
} game_trace_t;

static_assert(sizeof(game_trace_t) == 0xB0, "game_trace_t has wrong size");