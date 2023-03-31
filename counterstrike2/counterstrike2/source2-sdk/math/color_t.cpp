#include "color_t.hpp"

color_t::color_t()
{
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->a = 0;
}

color_t::color_t(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha)
{
	this->r = red;
	this->g = green;
	this->b = blue;
	this->a = alpha;
}

color_t::~color_t()
{

}

std::uint32_t color_t::dump()
{
	std::uint32_t out = 0;

	out = static_cast<std::uint32_t>(this->r) << 0;
	out |= static_cast<std::uint32_t>(this->g) << 8;
	out |= static_cast<std::uint32_t>(this->b) << 16;
	out |= static_cast<std::uint32_t>(this->a) << 24;

	return out;
}

color_t color_t::black(std::uint8_t a)
{
	return { 0, 0, 0, a };
}

color_t color_t::white(std::uint8_t a)
{
	return { 255, 255, 255, a };
}

color_t color_t::red(std::uint8_t a)
{
	return { 255, 0, 0, a };
}

color_t color_t::green(std::uint8_t a)
{
	return { 0, 255, 0, a };
}

color_t color_t::blue(std::uint8_t a)
{
	return { 0, 0, 255, a };
}

color_t color_t::yellow(std::uint8_t a)
{
	return { 247, 202, 24, a };
}
