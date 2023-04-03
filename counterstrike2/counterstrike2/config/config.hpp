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

		bool aimbot = false;
		float aimbot_fov = 1.f;
	} config_t;

	typedef struct _file_t
	{
		char name[260];
		config_t config;
	} file_t;

	extern config_t context;
}