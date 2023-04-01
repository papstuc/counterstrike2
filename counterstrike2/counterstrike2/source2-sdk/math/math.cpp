#include "math.hpp"

#include "../../signatures.hpp"
#include "../../utilities/utilities.hpp"
#include "../../source2-sdk/sdk.hpp"

bool math::world_to_screen(vec3_t& origin, vec3_t& screen)
{
	using function_t = bool(__fastcall*)(vec3_t&, vec3_t&);
	static function_t function = reinterpret_cast<function_t>(utilities::pattern_scan(L"client.dll", WORLD_TO_SCREEN));

    bool status = !function(origin, screen);

    screen.x = static_cast<float>((screen.x + 1.0) * 0.5) * sdk::screen_width;
    screen.y = sdk::screen_height - (static_cast<float>((screen.y + 1.0) * 0.5) * sdk::screen_height);

    return status;
}