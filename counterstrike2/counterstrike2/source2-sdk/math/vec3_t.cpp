#include "vec3_t.hpp"

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