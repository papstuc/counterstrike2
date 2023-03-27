#include <Windows.h>
#include <cstdarg>
#include <cstdio>

#include "console.hpp"

void console::console_color_msg(color_t color, const char* message ...)
{
    using function_t = void(__cdecl*)(const color_t&, const char*);
    static function_t p_console_color_msg = reinterpret_cast<decltype(p_console_color_msg)>(GetProcAddress(GetModuleHandle(L"tier0.dll"), "?ConColorMsg@@YAXAEBVColor@@PEBDZZ"));

    if (!p_console_color_msg)
    {
        return;
    }

    char buffer[1024] = { };
    va_list args = nullptr;

    va_start(args, message);
    vsprintf_s(buffer, message, args);
    va_end(args);

    p_console_color_msg(color, buffer);
}