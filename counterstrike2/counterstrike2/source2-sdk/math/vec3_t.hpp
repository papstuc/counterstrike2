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
	vec3_t operator*(vec3_t& other);
	vec3_t operator*(float factor);
	vec3_t operator/(float factor);
	vec3_t operator/(vec3_t& other);
	vec3_t& operator/=(float factor);



	void clamp();
	void normalize();
	bool is_zero();
	float length();
};