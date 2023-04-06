#pragma once

#include "vec2_t.hpp"
#include "vec3_t.hpp"

#include "../classes/user_cmd.hpp"

namespace math
{
	bool world_to_screen(vec3_t& origin, vec3_t& screen);
	vec3_t calculate_angle(vec3_t& source, vec3_t& destination, vec3_t& view_angles);
	void correct_movement(vec3_t old_angles, c_user_cmd* cmd, float old_forwardmove, float old_sidemove);
}