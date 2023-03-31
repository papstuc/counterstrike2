#pragma once

class vec2_t
{
public:
	float x;
	float y;

	vec2_t();
	vec2_t(float x, float y);
	~vec2_t();

	vec2_t operator+(vec2_t& other);
};