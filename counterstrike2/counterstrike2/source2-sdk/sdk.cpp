#include "sdk.hpp"

#include "../utilities/utilities.hpp"

player_t* sdk::local_player = nullptr;
std::int32_t sdk::screen_width = 0;
std::int32_t sdk::screen_height = 0;

void* sdk::get_entity_index(int index)
{
    using function_t = void* (__fastcall*)(int);
    static function_t get_entity_index = reinterpret_cast<function_t>(utilities::pattern_scan(L"client.dll", "40 53 48 83 EC ? 48 8B 05 ? ? ? ? 48 85 C0 74 ? 85 C9 78 ? 3B 48 ? 7D ? 8D 51 ? 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B D8 48 85 C0 74 ? 48 8B 10 48 8B C8 FF 92 ? ? ? ? 33 C9"));

    return get_entity_index(index);
}

void* sdk::get_player_pawn(void* entity)
{
    using function_t = void* (__fastcall*)(void*);
    static function_t get_player_pawn = reinterpret_cast<function_t>(utilities::pattern_scan(L"client.dll", "4C 8B 05 ? ? ? ? 4D 85 C0 74 ? 8B 89 ? ? ? ? 83 F9 ? 77 ? 8B C1 25 ? ? ? ? 8B D0 48 C1 E8 ? 4D 8B 0C C0 4D 85 C9 74 ? 81 E2 ? ? ? ? 48 6B C2 ? 49 03 C1 74 ? 39 48 ? 75 ? 48 8B 00 C3 33 C0 C3 CC CC CC CC CC CC CC CC 4C 8B CA"));

    return get_player_pawn(entity);
}

void* sdk::get_player_pawn_handle(std::uint16_t handle)
{
    using function_t = void* (__fastcall*)(int);
    static function_t get_player_pawn_handle = reinterpret_cast<function_t>(utilities::pattern_scan(L"client.dll", "48 83 EC ? 83 F9 ? 75 ? 48 8B 0D ? ? ? ? 48 8D 54 24 ? 48 8B 01 FF 90 ? ? ? ? 8B 08 48 63 C1 48 8D 0D ? ? ? ? 48 8B 0C C1"));

    return get_player_pawn_handle(handle);
}