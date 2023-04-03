#pragma once

class vec4_t
{
public:
	float x;
	float y;
	float z;
	float w;

	vec4_t();
	vec4_t(float x, float y, float z, float w);
	~vec4_t();
};