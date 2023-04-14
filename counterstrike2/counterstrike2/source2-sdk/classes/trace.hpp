#pragma once

#include <cstdint>

#include "../math/vec3_t.hpp"
#include "entities.hpp"

class c_ray
{
public:
	vec3_t start;
	vec3_t end;
	vec3_t mins;
	vec3_t maxs;
	std::uint32_t N000002C7;
	std::uint8_t N000002BE;
};
static_assert(sizeof(c_ray) == 0x38);

class c_trace_filter
{
public:
	std::uint64_t trace_mask;
	std::uint64_t null_it1;
	std::uint64_t null_it2;
	std::uint32_t skip_handle1;
	std::uint32_t skip_handle2;
	std::uint32_t skip_handle3;
	std::uint32_t skip_handle4;
	std::uint16_t collission1;
	std::uint16_t collission2;
	std::uint16_t N0000011C;
	std::uint8_t layer;
	std::uint8_t N00000104;
	std::uint8_t null_it3;

	virtual ~c_trace_filter()
	{

	}

	virtual bool function()
	{
		return true;
	}

	c_trace_filter(std::uint64_t trace_mask, player_t* local_player, std::uint8_t layer);
};
static_assert(sizeof(c_trace_filter) == 0x40);

class c_game_trace
{
public:
	void* surface;
	entity_t* entity;
	void* hitbox;
	char pad_0028[148];
	float fraction;
	char pad_0176[9];
};
static_assert(sizeof(c_game_trace) == 0xC0);