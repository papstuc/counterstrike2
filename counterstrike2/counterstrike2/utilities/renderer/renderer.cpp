#include "renderer.hpp"

#include "../imgui/imgui.h"

void renderer::rect(float x, float y, float w, float h, color_t color)
{
	ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color.dump());
}

void renderer::filled_rect(float x, float y, float w, float h, color_t color)
{
	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color.dump());
}

void renderer::text(float x, float y, color_t color, const char* text, bool centered)
{
	ImVec2 text_size = ImGui::CalcTextSize(text);
	ImVec2 text_position = { centered ? (x - (text_size.x)) : x, y - text_size.y};

	ImGui::GetBackgroundDrawList()->AddText(ImVec2(text_position.x + 1.f, text_position.y + 1.f), color_t::black().dump(), text);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(text_position.x, text_position.y), color.dump(), text);
}
