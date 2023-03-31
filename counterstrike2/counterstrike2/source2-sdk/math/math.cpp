#include "math.hpp"

#include "../../utilities/utilities.hpp"
#include "../../source2-sdk/sdk.hpp"

bool math::world_to_screen(vec3_t& origin, vec3_t& screen)
{
	using function_t = bool(__fastcall*)(vec3_t&, vec3_t&);
	static function_t function = reinterpret_cast<function_t>(utilities::pattern_scan(L"client.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 1D ? ? ? ? 48 8B FA"));

	return function(origin, screen);
}