#include "vec4_t.hpp"

vec4_t::vec4_t()
{
	this->x = 0.f;
	this->y = 0.f;
}

vec4_t::vec4_t(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

vec4_t::~vec4_t()
{

}