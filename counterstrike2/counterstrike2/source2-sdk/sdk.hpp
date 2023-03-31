#pragma once

#include <cstdint>

#include "classes/entities.hpp"
#include "classes/global_vars.hpp"

#include "interfaces/interfaces.hpp"

#include "math/math.hpp"
#include "math/color_t.hpp"
#include "math/vec2_t.hpp"
#include "math/vec3_t.hpp"
#include "math/point_t.hpp"

#include "schema_system/schema_system.hpp"

namespace sdk
{
	extern player_t* local_player;
	extern std::int32_t screen_width;
	extern std::int32_t screen_height;

	void* get_entity_index(int index);
	void* get_player_pawn(void* entity);
	void* get_player_pawn_handle(std::uint16_t handle);
}