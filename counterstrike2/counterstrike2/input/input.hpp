#pragma once

#include <cstdint>

namespace input
{
	void handle(std::uint32_t message, std::uint64_t wparam);
	bool key_pressed(std::uint32_t virtual_key);
}