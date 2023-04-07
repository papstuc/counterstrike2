#include "vec3_t.hpp"

#include <cmath>
#include <algorithm>

vec3_t::vec3_t()
{
	this->x = 0.f;
	this->y = 0.f;
	this->z = 0.f;
}

vec3_t::vec3_t(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

vec3_t::~vec3_t()
{

}

vec3_t vec3_t::operator+(vec3_t& other)
{
	return vec3_t(this->x + other.x, this->y + other.y, this->z + other.z);
}

vec3_t vec3_t::operator-(vec3_t& other)
{
	return vec3_t(this->x - other.x, this->y - other.y, this->z - other.z);
}

vec3_t& vec3_t::operator+=(vec3_t& other)
{
	this->x += other.x; this->y += other.y; this->z += other.z;
	return *this;
}

vec3_t vec3_t::operator*(vec3_t& other)
{
	return vec3_t(this->x * other.x, this->y * other.y, this->z * other.z);
}

vec3_t vec3_t::operator*(float factor)
{
	return vec3_t(this->x * factor, this->y * factor, this->z * factor);
}

vec3_t vec3_t::operator/(float factor)
{
	return vec3_t(this->x / factor, this->y / factor, this->z / factor);
}

vec3_t vec3_t::operator/(vec3_t& other)
{
	return vec3_t(this->x / other.x, this->y / other.y, this->z / other.z);
}

vec3_t& vec3_t::operator/=(float factor)
{
	this->x /= factor;
	this->y /= factor;
	this->z /= factor;
	return *this;
}

void vec3_t::clamp()
{
	this->x = std::clamp(this->x, -89.0f, 89.0f);
	this->y = std::clamp(std::remainder(this->y, 360.0f), -180.0f, 180.0f);
	this->z = std::clamp(this->z, -50.0f, 50.0f);
}

void vec3_t::normalize()
{
	this->x = std::isfinite(this->x) ? std::remainderf(this->x, 360.0f) : 0.0f;
	this->y = std::isfinite(this->y) ? std::remainderf(this->y, 360.0f) : 0.0f;
	this->z = 0.0f;
}

bool vec3_t::is_zero()
{
	if (this->x == 0 && this->y == 0 && this->z == 0)
	{
		return true;
	}

	return false;
}

float vec3_t::length()
{
	return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}