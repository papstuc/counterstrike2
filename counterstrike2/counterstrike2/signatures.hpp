#pragma once

// hooks.cpp
#define LEVEL_INIT "48 89 5C 24 ? 57 48 83 EC ? 48 8B 0D ? ? ? ? 48 8B DA 45 33 C9"
#define FRAME_STAGE_NOTIFY "48 89 5C 24 ? 56 48 83 EC ? 8B 05 ? ? ? ? 8D 5A"

// i_entity_list.hpp
#define GET_CONTROLLER_BY_INDEX "81 FA ? ? ? ? 77 3B 8B C2"
#define GET_PLAYER_FROM_CONTROLLER "4C 8B 05 ?? ?? ?? ?? 4D 85 C0 74 39 8B 89 D4 05"
#define GET_LOCAL_PLAYER "48 83 EC ? 83 F9 ? 75 ? 48 8B 0D ? ? ? ? 48 8D 54 24 ? 48 8B 01 FF 90 ? ? ? ? 8B 08 48 63 C1 48 8D 0D ? ? ? ? 48 8B 0C C1"

// interfaces.cpp
#define GLOBAL_VARS "48 8B 05 ? ? ? ? 4C 8D 0D ? ? ? ? F2 0F 11 74 24 ? 4C 8D 05 ? ? ? ? BA"
#define CSGO_INPUT "48 8B 0D ? ? ? ? 4C 8D 8F ? ? ? ? 33 ED"
#define RENDERER "66 0F 7F 05 ? ? ? ? 66 0F 7F 0D ? ? ? ? 48 89 35"
#define ENTITY_LIST "48 8B 0D ? ? ? ? 8B D3 E8 ? ? ? ? 48 8B F0"
#define CLIENT_MODE "48 8B 0D ? ? ? ? 48 85 C9 74 44 F6 42 10 20 74 14 48 8B 01 4C 8D 4F 70"

// math.cpp
#define WORLD_TO_SCREEN "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 1D ? ? ? ? 48 8B FA"