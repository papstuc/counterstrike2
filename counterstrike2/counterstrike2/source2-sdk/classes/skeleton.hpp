#pragma once

#include <cstdint>
#include "../math/vec3_t.hpp"
#include "../math/vec4_t.hpp"

class c_model_state
{
public:
	char pad_0000[128];
	class c_bone* bones;
};

static_assert(sizeof(c_model_state) == 0x88);

class c_skeleton
{
public:
	char pad_0000[352];
	class c_model_state model_state;
};

static_assert(sizeof(c_skeleton) == 0x1E8);

class c_bone
{
public:
	vec3_t location;
	char pad_000C[20];
};

static_assert(sizeof(c_bone) == 0x20);