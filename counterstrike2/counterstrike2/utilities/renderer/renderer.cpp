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

void renderer::text(float x, float y, color_t color, const char* text)
{
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(x + 1.f, y + 1.f), color_t::black().dump(), text);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y), color.dump(), text);
}

void renderer::text_centered(float x, float y, float w, float h, color_t color, const char* text)
{
	ImVec2 text_size = ImGui::CalcTextSize(text);
	ImVec2 text_position = { (x + (x + w) - text_size.x) / 2.f, y - text_size.y - 4.f };

	ImGui::GetBackgroundDrawList()->AddText(ImVec2(text_position.x + 1.f, text_position.y + 1.f), color_t::black().dump(), text);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(text_position.x, text_position.y), color.dump(), text);
}

void renderer::line(float x, float y, float x1, float y1, color_t color)
{
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x1, y1), color.dump());
}