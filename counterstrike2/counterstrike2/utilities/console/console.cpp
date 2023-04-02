#include "console.hpp"

#include <Windows.h>
#include <cstdarg>
#include <cstdio>

void console::console_color_msg(color_t color, const char* message ...)
{
    using function_t = void(__cdecl*)(color_t&, const char*);
    static function_t fn = reinterpret_cast<function_t>(GetProcAddress(GetModuleHandle(L"tier0.dll"), "?ConColorMsg@@YAXAEBVColor@@PEBDZZ"));

    char buffer[1024] = { };
    va_list args = nullptr;

    va_start(args, message);
    vsprintf_s(buffer, message, args);
    va_end(args);

    fn(color, buffer);
}