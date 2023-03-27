#pragma once

#include <cstdint>
#include <utility>
#include <map>

class shadow_vmt
{
private:
	std::uint8_t* m_instance = nullptr;

	std::uint8_t* m_original_table = nullptr;
	std::size_t m_table_size = 0;

	std::uint8_t* m_fake_table = nullptr;

	std::map<std::size_t, void*> m_hooks = { };

public:
	shadow_vmt(std::uint8_t* table);
	shadow_vmt();
	~shadow_vmt();

	void initialize(std::uint8_t* table);
	void* detour(std::size_t index, void* function);
	void release();
};