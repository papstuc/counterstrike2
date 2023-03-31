#pragma once

#include <cstdint>

class color_t
{
public:
	std::uint8_t r, g, b, a;

	color_t();
	color_t(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255);
	~color_t();

	std::uint32_t dump();

	static color_t black(std::uint8_t a = 255);
	static color_t white(std::uint8_t a = 255);
	static color_t red(std::uint8_t a = 255);
	static color_t green(std::uint8_t a = 255);
	static color_t blue(std::uint8_t a = 255);
	static color_t yellow(std::uint8_t a = 255);
};