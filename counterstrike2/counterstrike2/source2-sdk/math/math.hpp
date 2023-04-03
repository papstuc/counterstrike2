#pragma once

#include "vec2_t.hpp"
#include "vec3_t.hpp"

namespace math
{
	bool world_to_screen(vec3_t& origin, vec3_t& screen);
	vec3_t calculate_angle(vec3_t& source, vec3_t& destination, vec3_t& view_angles);
}