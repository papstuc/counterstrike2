#include "math.hpp"

#include "../../signatures.hpp"
#include "../../utilities/utilities.hpp"
#include "../../source2-sdk/sdk.hpp"

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

#define deg_to_rad(x)  ((float)(x) * (float)(M_PI / 180.f))
#define rad_to_deg(x)  ((float)(x) * (float)(180.f / M_PI))

bool math::world_to_screen(vec3_t& origin, vec3_t& screen)
{
	using function_t = bool(__fastcall*)(vec3_t&, vec3_t&);
	static function_t function = reinterpret_cast<function_t>(utilities::pattern_scan(L"client.dll", WORLD_TO_SCREEN));

    bool status = !function(origin, screen);

    screen.x = static_cast<float>((screen.x + 1.0) * 0.5) * sdk::screen_width;
    screen.y = sdk::screen_height - (static_cast<float>((screen.y + 1.0) * 0.5) * sdk::screen_height);

    return status;
}

vec3_t math::calculate_angle(vec3_t& source, vec3_t& destination, vec3_t& view_angles)
{
	vec3_t delta = source - destination;
	vec3_t angles;

	angles.x = rad_to_deg(std::atanf(delta.z / std::hypotf(delta.x, delta.y))) - view_angles.x;
	angles.y = rad_to_deg(std::atanf(delta.y / delta.x)) - view_angles.y;
	angles.z = 0.0f;

	if (delta.x >= 0.0)
	{
		angles.y += 180.0f;
	}

	return angles;
}

void math::correct_movement(vec3_t old_angles, c_user_cmd* cmd, float old_forwardmove, float old_sidemove)
{
	float delta_view;
	float f1 = 0.f;
	float f2 = 0.f;

	if (old_angles.y < 0.f)
	{
		f1 = 360.0f + old_angles.y;
	}
	else
	{
		f1 = old_angles.y;
	}

	if (cmd->base->view->angles.y < 0.0f)
	{
		f2 = 360.0f + cmd->base->view->angles.y;
	}
	else
	{
		f2 = cmd->base->view->angles.y;
	}

	if (f2 < f1)
	{
		delta_view = abs(f2 - f1);
	}
	else
	{
		delta_view = 360.0f - abs(f1 - f2);
	}

	delta_view = 360.0f - delta_view;

	cmd->base->forwardmove = std::cos(deg_to_rad(delta_view)) * old_forwardmove + std::cos(deg_to_rad(delta_view + 90.f)) * old_sidemove;
	cmd->base->sidemove = std::sin(deg_to_rad(delta_view)) * old_forwardmove + std::sin(deg_to_rad(delta_view + 90.f)) * old_sidemove;
}
