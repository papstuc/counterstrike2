#include "renderer.hpp"

#include "../imgui/imgui.h"

void renderer::rect(float x, float y, float w, float h, color_t color)
{
	ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color.dump());
}