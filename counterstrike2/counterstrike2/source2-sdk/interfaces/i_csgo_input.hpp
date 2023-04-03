#pragma once

#include "../../signatures.hpp"

#include "../math/vec3_t.hpp"
#include "../classes/user_cmd.hpp"
#include "../../utilities/utilities.hpp"

enum csgo_input_vtable
{
	CREATEMOVE = 5,
	MOUSE_INPUT = 10
};

class i_csgo_input
{
public:
    user_cmd_t* get_user_cmd(void* a1, std::uint32_t a2)
    {
        // 48 63 DA 4C 8B E1 4C 69 EB
        std::int64_t v5 = 0x460 * a2;
        std::int64_t v6 = *reinterpret_cast<std::int64_t*>(reinterpret_cast<std::uintptr_t>(a1) + v5 + 0x41E0);
        std::int64_t v7 = 0x70 * (0x9A * a2 + v6 % 0x96) + reinterpret_cast<std::uintptr_t>(a1);
        std::uint64_t split_screen = v7 + 0x10;

        return reinterpret_cast<user_cmd_t*>(split_screen);
    }

    void set_view_angles(vec3_t& angles)
    {
        using function_t = std::int64_t(__fastcall*)(i_csgo_input*, std::int32_t, vec3_t&);
        static function_t fn = reinterpret_cast<function_t>(utilities::pattern_scan(L"client.dll", SET_VIEW_ANGLES));

        fn(this, 0, angles);
    }
};