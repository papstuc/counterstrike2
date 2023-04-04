#pragma once

#include "../../utilities/utilities.hpp"
#include "../classes/trace.hpp"
#include "../math/vec3_t.hpp"

#include "../../signatures.hpp"

class i_trace
{
public:
	void clip_trace_to_players(vec3_t& start, vec3_t& end, trace_filter_t* filter, game_trace_t* trace, float min, float max, float length)
	{
		using function_t = void(__fastcall*)(vec3_t&, vec3_t&, trace_filter_t*, game_trace_t*, float, float, float);
		static function_t fn = reinterpret_cast<function_t>(utilities::pattern_scan(L"client.dll", CLIP_TRACE_TO_PLAYERS));

		fn(start, end, filter, trace, min, max, length);
	}

	void trace_shape(ray_t* ray, vec3_t& start, vec3_t& end, trace_filter_t* filter, game_trace_t* trace)
	{
		using function_t = bool(__fastcall*)(i_trace*, ray_t*, vec3_t&, vec3_t&, trace_filter_t*, game_trace_t*);
		static function_t fn = reinterpret_cast<function_t>(utilities::pattern_scan(L"client.dll", TRACE_SHAPE));

		fn(this, ray, start, end, filter, trace);
	}
};