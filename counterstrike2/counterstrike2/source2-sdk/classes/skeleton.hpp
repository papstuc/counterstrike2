#pragma once

#include <cstdint>
#include "../math/vec3_t.hpp"
#include "../math/vec4_t.hpp"

typedef struct _bone_t
{
    const char* bone_name;
    const char* parent_name;
    char pad1[0x30];
    vec3_t center;
    vec3_t size;
    float radius;
} bone_t;

static_assert(sizeof(bone_t) == 0x60, "global_vars_t has wrong size");

typedef struct _render_mesh_t
{
    char pad1[0xBC];
    bone_t* skeleton;
} render_mesh_t;

static_assert(sizeof(render_mesh_t) == 0xC8, "render_mesh_t has wrong size");

typedef struct _render_meshes_t
{
    render_mesh_t* meshes;
} render_meshes_t;

static_assert(sizeof(render_meshes_t) == 0x8, "render_meshes_t has wrong size");

typedef struct _model_t
{
    char pad1[0x78];
    render_meshes_t* render_mesh;
} model_t;

static_assert(sizeof(model_t) == 0x80, "model_t has wrong size");

class skeleton_instance
{
public:
    model_t* get_model()
    {
        auto ptr = *reinterpret_cast<void**>((uintptr_t)this + 0x200);

        if (!ptr)
            return nullptr;

        return *reinterpret_cast<model_t**>(ptr);
    }
};