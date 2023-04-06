#pragma once

#include <cstdint>

#include "../../utilities/utilities.hpp"
#include "../../signatures.hpp"
#include "../schema_system/schema_system.hpp"
#include "../math/vec3_t.hpp"
#include "skeleton.hpp"

enum buttons_t : std::uint32_t
{
    in_attack = 1,
    in_jump = 2,
    in_duck = 4,
    in_forward = 8,
    in_attack2 = 2048
};

enum movetype_t : std::uint32_t
{
    movetype_none = 0,
    movetype_isometric,
    movetype_walk,
    movetype_step,
    movetype_fly,
    movetype_flygravity,
    movetype_vphysics,
    movetype_push,
    movetype_noclip,
    movetype_ladder,
    movetype_observer,
    movetype_custom,
    movetype_last = movetype_custom,
    movetype_max_bits = 4
};

enum flags_t : std::uint32_t
{
    fl_onground = (1 << 0),
    fl_ducking = (1 << 1),
    fl_waterjump = (1 << 2),
    fl_ontrain = (1 << 3),
    fl_inrain = (1 << 4),
    fl_frozen = (1 << 5),
    fl_atcontrols = (1 << 6),
    fl_client = (1 << 7),
    fl_fakeclient = (1 << 8),
    fl_inwater = (1 << 9),
    fl_fly = (1 << 10),
    fl_swim = (1 << 11),
    fl_conveyor = (1 << 12),
    fl_npc = (1 << 13),
    fl_godmode = (1 << 14),
    fl_notarget = (1 << 15),
    fl_aimtarget = (1 << 16),
    fl_partialground = (1 << 17),
    fl_staticprop = (1 << 18),
    fl_graphed = (1 << 19),
    fl_grenade = (1 << 20),
    fl_stepmovement = (1 << 21),
    fl_donttouch = (1 << 22),
    fl_basevelocity = (1 << 23),
    fl_worldbrush = (1 << 24),
    fl_object = (1 << 25),
    fl_killme = (1 << 26),
    fl_onfire = (1 << 27),
    fl_dissolving = (1 << 28),
    fl_transragdoll = (1 << 29),
    fl_unblockable_by_player = (1 << 30)
};

enum frame_stage_t : std::int32_t
{
    FRAME_UNDEFINED = -1,
    FRAME_START,
    FRAME_NET_UPDATE_START,
    FRAME_NET_UPDATE_POSTDATAUPDATE_START,
    FRAME_NET_UPDATE_POSTDATAUPDATE_END,
    FRAME_NET_UPDATE_END,
    FRAME_RENDER_START,
    FRAME_RENDER_END
};

class game_scene_node_t
{
public:
    SCHEMA("CGameSceneNode", "m_vecAbsOrigin", abs_origin, vec3_t);
    SCHEMA("CGameSceneNode", "m_vecOrigin", vec_origin, vec3_t);
    SCHEMA("CGameSceneNode", "m_bDormant", dormant, bool);
};

class CGameSceneNode
{
public:
    class CSkeletonInstance* GetSkeletonInstance()
    {
        using function = class CSkeletonInstance* (*)();

        return (*reinterpret_cast<function**>(this))[8]();
    }
};

class Quaternion
{
public:
    float x, y, z, w;
    float operator[](int i) const { if (i == 1) return x; if (i == 2) return y; if (y == 3) return z; return w; };
    float& operator[](int i) { if (i == 1) return x; if (i == 2) return y; if (y == 3) return z; return w; };
};


struct CBoneData
{
    vec3_t Location;
    float Scale;
    Quaternion Rotation;
};

class CModelState /* "client" */
{
public:
    unsigned char pad_0[0x80]; // 0x0 - 0xA0
    CBoneData* m_boneArray;
    unsigned char pad_88[0x18];
    void* m_hModel; // 0xA0 - 0xA8
    const char* m_ModelName; // 0xA8 - 0xB0
    unsigned char pad_B0[0x38]; // 0xB0 - 0xE8
    bool m_bClientClothCreationSuppressed; // 0xE8 - 0xE9
    unsigned char pad_E9[0x97]; // 0xE9 - 0x180
    uint64_t m_MeshGroupMask; // 0x180 - 0x188
    unsigned char pad_188[0x9A]; // 0x188 - 0x222
    int8_t m_nIdealMotionType; // 0x222 - 0x223
    int8_t m_nForceLOD; // 0x223 - 0x224
    int8_t m_nClothUpdateFlags; // 0x224 - 0x225
    unsigned char pad_225[0xB]; // 0x225 - 0x230
}; // size - 0x230

class CSkeletonInstance /* "client" */ : public CGameSceneNode /* "client" */
{
public:
    unsigned char pad_150[0x10]; // 0x150 - 0x160
    CModelState m_modelState; // 0x160 - 0x390
    bool m_bIsAnimationEnabled; // 0x390 - 0x391
    bool m_bUseParentRenderBounds; // 0x391 - 0x392
    bool m_bDisableSolidCollisionsForHierarchy; // 0x392 - 0x393
    unsigned char m_bDirtyMotionType : 1; // 0x393 - 0x394
    unsigned char m_bIsGeneratingLatchedParentSpaceState : 1; // 0x393 - 0x394
    char pad1[0x4];
    uint8_t m_nHitboxSet; // 0x398 - 0x399
    unsigned char pad_399[0x57]; // 0x399 - 0x3F0
}; // size - 0x3F0

class collision_property_t
{
public:
    SCHEMA("CCollisionProperty", "m_vecMins", mins, vec3_t);
    SCHEMA("CCollisionProperty", "m_vecMaxs", maxs, vec3_t);
    SCHEMA("CCollisionProperty", "m_usSolidFlags", solid_flags, std::uint16_t);

    std::uint16_t get_collision_mask()
    {
        return *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uintptr_t>(this) + 0x38);
    }
};

class econ_item_view_t
{
public:
    SCHEMA("CEconItemView", "m_iItemIDHigh", item_id_high, std::int32_t);
};

class attribute_container_t
{
public:
    SCHEMA("CAttributeContainer", "m_Item", item, econ_item_view_t*);
};

class econ_entity_t
{
public:
    SCHEMA("CEconEntity", "m_flFallbackWear", fallback_wear, float);
    SCHEMA("CEconEntity", "m_nFallbackSeed", attribute_manager, attribute_container_t*);
    SCHEMA("CEconEntity", "m_nFallbackSeed", fallback_seed, std::int32_t);
    SCHEMA("CEconEntity", "m_nFallbackPaintKit", fallback_paintkit, std::int32_t);
};

class weapon_services_t
{
public:
    SCHEMA("CPlayer_WeaponServices", "m_hMyWeapons", weapons, econ_entity_t*);
};

class entity_t
{
public:
    SCHEMA("C_BaseEntity", "m_pGameSceneNode", game_scene_node, game_scene_node_t*);
    SCHEMA("C_BaseEntity", "m_pCollision", collision_property, collision_property_t*);
    SCHEMA("C_BaseEntity", "m_hOwnerEntity", owner_handle, std::uint32_t);
    SCHEMA("C_BaseEntity", "m_flSimulationTime", simulation_time, float);
};

class player_t : public entity_t
{
public:
    SCHEMA("C_BasePlayerPawn", "m_pWeaponServices", weapon_services, weapon_services_t*);
    SCHEMA("CCSPlayer_ItemServices", "m_bHasDefuser", has_defuser, bool);
    SCHEMA("C_CSPlayerPawnBase", "m_bGunGameImmunity", has_gun_immunity, bool);
    SCHEMA("C_BaseEntity", "m_iHealth", health, std::int32_t);
    SCHEMA("C_BaseEntity", "m_iTeamNum", team, std::uint8_t);
    SCHEMA("C_BaseModelEntity", "m_vecViewOffset", view_offset, vec3_t);
    SCHEMA("C_BasePlayerPawn", "m_hController", controller_handle, std::uint32_t);

    vec3_t get_eye_position()
    {
        vec3_t position;
        using function_t = void*(__fastcall*)(player_t*, vec3_t&);

        (*reinterpret_cast<function_t**>(this))[154](this, position);

        return position;
    }

    c_skeleton* get_skeleton()
    {
        return *reinterpret_cast<c_skeleton**>((std::uintptr_t)this + 0x300);
    }

    void get_bone_position(std::uint32_t bone_index, vec3_t& position, vec3_t& rotation)
    {
        using function_t = std::int64_t(__fastcall*)(player_t*, std::uint32_t, vec3_t*, vec3_t*);
        static function_t fn = reinterpret_cast<function_t>(utilities::pattern_scan(L"client.dll", GET_BONE_POSITION));

        fn(this, bone_index, &position, &rotation);
    }

    bool is_alive()
    {
        return this->health() > 0;
    }
};

class controller_t
{
public:
    SCHEMA("CBasePlayerController", "m_steamID", steam_id, std::uint64_t);
    SCHEMA("CBasePlayerController", "m_hPawn", pawn_handle, std::uint32_t);
    SCHEMA("CBasePlayerController", "m_bIsLocalPlayerController", is_local_player_controller, bool);
    SCHEMA("CCSPlayerController", "m_sSanitizedPlayerName", name, const char*);
};
