#pragma once

#include "../../source2-sdk/math/color_t.hpp"
#include "../../source2-sdk/math/math.hpp"

namespace renderer
{
	void rect(float x, float y, float w, float h, color_t color);
	void filled_rect(float x, float y, float w, float h, color_t color);
	void text(float x, float y, color_t color, const char* text);
	void text_centered(float x, float y, float w, float h, color_t color, const char* text);
}