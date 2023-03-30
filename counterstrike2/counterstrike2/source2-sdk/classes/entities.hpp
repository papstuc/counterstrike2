#pragma once

#include <cstdint>

#include "../schema_system/schema_system.hpp"
#include "../math/vec3_t.hpp"

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
};

class collision_property_t
{
public:
    SCHEMA("CCollisionProperty", "m_vecMins", mins, vec3_t);
    SCHEMA("CCollisionProperty", "m_vecMaxs", maxs, vec3_t);
};

class entity_t
{
public:
    SCHEMA("C_BaseEntity", "m_pGameSceneNode", game_scene_node, game_scene_node_t*);
    SCHEMA("C_BaseEntity", "m_pCollision", collision_property, collision_property_t*);

    SCHEMA("C_BaseEntity", "m_hOwnerEntity", owner_handle, unsigned long);
    SCHEMA("C_BaseEntity", "m_flSimulationTime", simulation_time, float);

    SCHEMA("C_BaseEntity", "m_lifeState", life_state, std::int32_t);
};

class weapon_services_t
{
public:
    std::uint32_t* get_weapons()
    {
        return reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint64_t>(this) + schema_system::get_schema("CPlayer_WeaponServices", "m_hMyWeapons"));
    }
};

class econ_entity_t
{
public:
    SCHEMA("C_EconEntity", "m_OriginalOwnerXuidLow", original_owner_xuid_low, std::int32_t);
    SCHEMA("C_EconEntity", "m_OriginalOwnerXuidHigh", original_owner_xuid_high, std::int32_t);
    SCHEMA("C_EconEntity", "m_nFallbackStatTrak", fallback_stattrak, std::int32_t);
    SCHEMA("C_EconEntity", "m_nFallbackPaintKit", fallback_paint_kit, std::int32_t);
    SCHEMA("C_EconEntity", "m_nFallbackSeed", fallback_seed, std::int32_t);
    //SCHEMA("DT_BaseAttributableItem", "m_iEntityQuality", entity_quality, std::int32_t);
    SCHEMA("C_EconEntity", "m_flFallbackWear", fallback_wear, float);
    //SCHEMA("DT_BaseCombatWeapon", "m_hWeaponWorldModel", world_model_handle, unsigned long);
    //SCHEMA("DT_BaseAttributableItem", "m_iItemDefinitionIndex", item_definition_index, short);
    //SCHEMA("DT_BaseAttributableItem", "m_iItemIDHigh", item_id_high, std::int32_t);
    SCHEMA("C_EconItemView", "m_iItemIDHigh", item_id_high, std::int32_t);
};

class weapon_base_t : public econ_entity_t
{
    // [C_WeaponCSBase] -> m_nViewModelIndex
};

class player_t : public entity_t
{
public:
    SCHEMA("C_BasePlayerPawn", "m_pWeaponServices", weapon_services, weapon_services_t*);

    SCHEMA("CCSPlayer_ItemServices", "m_bHasDefuser", has_defuser, bool);
    SCHEMA("C_CSPlayerPawnBase", "m_bGunGameImmunity", has_gun_immunity, bool);

    bool is_alive()
    {
        return this->life_state() == 0;
    }
};
