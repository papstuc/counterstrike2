#pragma once

#include <cstdint>

typedef struct _matrix4x2_t
{
	union
	{
		struct
		{
			float m11, m12, m13, m14;
			float m21, m22, m23, m24;
		};
		float matrix[4][2];
	};
} matrix4x2_t;

static_assert(sizeof(matrix4x2_t) == 0x20, "matrix4x2_t has wrong size");

class skeleton_t
{
public:
	char pad1[0x1BC];
	std::int32_t bone_count;
	char pad2[0x18];
	std::int32_t mask;
	char pad3[0x4];
	matrix4x2_t* bone_matrix;
};

static_assert(sizeof(skeleton_t) == 0x1E8, "skeleton_t has wrong size");