#pragma once

#include <cstdint>

namespace utilities
{
	std::uint8_t* pattern_scan(const wchar_t* module_name, const char* signature);
	std::uint8_t* resolve_rip(std::uint8_t* address, std::uint32_t rva_offset, std::uint32_t rip_offset);
	void* get_virtual(void* class_pointer, std::uint32_t index);
}
