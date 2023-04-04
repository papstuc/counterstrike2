#pragma once

#include <cstdint>

#include "classes/entities.hpp"
#include "classes/global_vars.hpp"

#include "interfaces/interfaces.hpp"

#include "math/math.hpp"
#include "math/color_t.hpp"
#include "math/vec2_t.hpp"
#include "math/vec3_t.hpp"

#include "schema_system/schema_system.hpp"

#include "sdl/sdl.hpp"

namespace sdk
{
	extern controller_t* local_controller;
	extern player_t* local_player;
	extern std::int32_t screen_width;
	extern std::int32_t screen_height;

	void update_local_controller();
	void update_local_player();
	void update_global_vars();
	void update_screen_size();
}