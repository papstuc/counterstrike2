#pragma once

#include "../classes/trace.hpp"
#include "../../utilities/utilities.hpp"
#include "../math/vec3_t.hpp"
#include "../../signatures.hpp"

class i_trace
{
public:
	bool trace_shape(c_ray* ray, vec3_t& start, vec3_t& end, c_trace_filter* filter, c_game_trace* trace)
	{
		using function_t = bool(__fastcall*)(i_trace*, c_ray*, vec3_t*, vec3_t*, c_trace_filter*, c_game_trace*);
		static function_t fn = reinterpret_cast<function_t>(utilities::pattern_scan(L"client.dll", TRACE_SHAPE));

		return fn(this, ray, &start, &end, filter, trace);
	}
};