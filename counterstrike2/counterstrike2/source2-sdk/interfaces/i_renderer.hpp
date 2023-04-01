#pragma once

#include <dxgi.h>

#include "../../utilities/imgui/imgui.h"

enum render_vtable
{
    PRESENT = 8,
    RESIZE_BUFFERS = 13
};

class i_renderer
{
public:
    unsigned char pad1[0x178];
    IDXGISwapChain* swap_chain;
};