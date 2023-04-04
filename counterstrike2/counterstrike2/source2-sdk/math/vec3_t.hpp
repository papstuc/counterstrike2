#pragma once

class vec3_t
{
public:
	float x;
	float y;
	float z;

	vec3_t();
	vec3_t(float x, float y, float z);
	~vec3_t();

	vec3_t operator+(vec3_t& other);
	vec3_t operator-(vec3_t& other);
	vec3_t& operator+=(vec3_t& other);

	void clamp();
	bool is_zero();
};