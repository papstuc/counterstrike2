#pragma once

// entities.hpp
#define GET_BONE_POSITION "48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 4D 8B F1"

// hooks.cpp
#define FRAME_STAGE_NOTIFY "48 89 5C 24 ? 56 48 83 EC ? 8B 05 ? ? ? ? 8D 5A"
#define LEVEL_INIT "48 89 5C 24 ? 57 48 83 EC ? 48 8B 0D ? ? ? ? 48 8B DA 45 33 C9"
#define SEND_MOVE "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 8D 55"

// i_entity_list.hpp
#define GET_CONTROLLER_BY_INDEX "81 FA ? ? ? ? 77 3B 8B C2"
#define GET_ENTITY_FROM_HANDLE "83 FA ? 77 ? 8B C2 25 ? ? ? ? 44 8B C0 48 C1 E8 ? 48 8B 4C C1"
#define GET_HANDLE_FROM_ENTITY "48 85 C9 74 ? 48 8B 41 ? 48 85 C0 74 ? 44 8B 40 ? BA ? ? ? ? 8B 48 ? 41 8B C0 83 E1"
#define GET_LOCAL_CONTROLLER "8B 05 ? ? ? ? 89 01 8B 05"
#define GET_LOCAL_PLAYER "48 83 EC ? 83 F9 ? 75 ? 48 8B 0D ? ? ? ? 48 8D 54 24 ? 48 8B 01 FF 90 ? ? ? ? 8B 08 48 63 C1 48 8D 0D ? ? ? ? 48 8B 0C C1"
#define GET_PLAYER_FROM_CONTROLLER "8B 91 D4 05 00 00 83 FA FF 74 3F"

// i_csgo_input.hpp
#define SET_VIEW_ANGLES "F2 41 0F 10 00 48 63 C2 48 69 D0"
#define GET_VIEW_ANGLES "48 63 C2 48 69 D0 ? ? ? ? 48 8D 81"

// i_trace.hpp
#define CLIP_TRACE_TO_PLAYERS "48 8B C4 55 56 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 48 89 58"
#define TRACE_SHAPE "48 89 54 24 ? 48 89 4C 24 ? 55 53 56 57 41 55 41 56 48 8D AC 24"

// interfaces.cpp
#define CLIENT_MODE "48 8B 0D ? ? ? ? 48 85 C9 74 44 F6 42 10 20 74 14 48 8B 01 4C 8D 4F 70"
#define CSGO_INPUT "48 8B 0D ? ? ? ? 48 8B 01 FF 50 ? 8B DF"
#define ENTITY_LIST "48 8B 0D ? ? ? ? 8B D3 E8 ? ? ? ? 48 8B F0"
#define GLOBAL_VARS "48 8B 05 ? ? ? ? 4C 8D 0D ? ? ? ? F2 0F 11 74 24 ? 4C 8D 05 ? ? ? ? BA"
#define RENDERER "66 0F 7F 05 ? ? ? ? 66 0F 7F 0D ? ? ? ? 48 89 35"
#define TRACE_MANAGER "48 8B 05 ? ? ? ? 80 A4 24"

// math.cpp
#define WORLD_TO_SCREEN "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 1D ? ? ? ? 48 8B FA 48 8B F1"