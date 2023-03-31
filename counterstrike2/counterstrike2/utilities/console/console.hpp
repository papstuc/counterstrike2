#pragma once

#include "../../source2-sdk/math/color_t.hpp"

namespace console
{
    void console_color_msg(color_t color, const char* message...);
}