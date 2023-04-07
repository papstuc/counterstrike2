#include "menu.hpp"

#include "../source2-sdk/sdk.hpp"
#include "../source2-sdk/interfaces/interfaces.hpp"
#include "../config/config.hpp"

#include "../utilities/imgui/imgui.h"
#include "../utilities/imgui/imgui_internal.h"
#include "../utilities/imgui/imgui_impl_win32.h"
#include "../utilities/imgui/imgui_impl_dx11.h"

extern bool menu::open = true;

void menu::render()
{
	if (!menu::open)
	{
		if (interfaces::input_system->is_relative_mouse_mode())
		{
			sdl::set_relative_mouse_mode(true);
			sdl::set_window_polling_mode(interfaces::input_system->get_sdl_window(), true);
			sdl::set_mouse_warp_position(nullptr, sdk::screen_width / 2, sdk::screen_height / 2);
		}

		return;
	}

	sdl::set_relative_mouse_mode(false);
	sdl::set_window_polling_mode(interfaces::input_system->get_sdl_window(), false);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(800.f, 400.f));

	if (ImGui::Begin("counterstrike2", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
	{
		if (ImGui::BeginTabBar("##features"))
		{
			if (ImGui::BeginTabItem("legit"))
			{
				ImGui::Checkbox("aimbot", &config::context.legitbot);
				ImGui::Checkbox("silent", &config::context.silent_aim);
				ImGui::SliderFloat("fov", &config::context.legit_fov, 1.f, 180.f, "%.2f");
				ImGui::SliderFloat("smooth", &config::context.smooth, 1.f, 30.f, "%.2f");
				ImGui::Checkbox("head", &config::context.hitboxes[0]);
				ImGui::Checkbox("chest", &config::context.hitboxes[1]);
				ImGui::Checkbox("arms", &config::context.hitboxes[2]);
				ImGui::Checkbox("legs", &config::context.hitboxes[3]);
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("anti-aim"))
			{
				ImGui::Checkbox("anti aim", &config::context.anti_aim);
				ImGui::Checkbox("fake lag", &config::context.fake_lag);
				ImGui::SliderInt("choke amount", &config::context.tick_choke_amount, 0, 20, "%d");
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("player esp"))
			{
				ImGui::Checkbox("players", &config::context.player_esp);
				ImGui::Checkbox("teammates", &config::context.teammate_esp);
				ImGui::Checkbox("box", &config::context.draw_box);
				ImGui::Checkbox("name", &config::context.draw_name);
				ImGui::Checkbox("health", &config::context.draw_health);
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("movement"))
			{
				ImGui::Checkbox("bhop", &config::context.bhop);
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
		ImGui::End();
	}

	ImGui::PopStyleVar();
}
