#pragma once

#include <cstdint>

namespace config
{
	constexpr std::uint32_t magic = 0xDEADBEEF;

	typedef struct _config_t
	{
		bool player_esp = false;
		bool teammate_esp = false;
		bool draw_box = false;
		bool draw_name = false;
		bool draw_health = false;

		bool legitbot = false;
		bool silent_aim = false;
		float legit_fov = 1.f;
		float smooth = 1.f;
		bool hitboxes[4] = { false, false, false, false };

		bool anti_aim = false;
		bool fake_lag = false;
		std::int32_t tick_choke_amount = 0;

		bool bhop = false;
	} config_t;

	typedef struct _file_t
	{
		char name[260];
		config_t config;
	} file_t;

	extern config_t context;
}