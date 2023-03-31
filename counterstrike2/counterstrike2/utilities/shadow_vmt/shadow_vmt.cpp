#include "shadow_vmt.hpp"

#include <Windows.h>

shadow_vmt::shadow_vmt(std::uint8_t* table)
{
	/*this->m_instance = table;
	this->m_original_table = *reinterpret_cast<std::uint8_t**>(this->m_instance);

	MEMORY_BASIC_INFORMATION mbi = { };
	while (VirtualQuery(reinterpret_cast<LPCVOID>(this->m_original_table[this->m_table_size]), &mbi, sizeof(mbi)))
	{
		if ((mbi.State != MEM_COMMIT) || (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) || !(mbi.Protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)))
		{
			break;
		}

		this->m_table_size++;
	}

	this->m_fake_table = static_cast<std::uint8_t*>(VirtualAlloc(nullptr, this->m_table_size * sizeof(void*), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));

	if (this->m_fake_table)
	{
		for (std::size_t i = 0; i < this->m_table_size; i++)
		{
			this->m_fake_table[i] = this->m_original_table[i];
		}
	}

	*reinterpret_cast<std::uint8_t**>(this->m_instance) = this->m_fake_table;*/
}

shadow_vmt::shadow_vmt()
{

}

shadow_vmt::~shadow_vmt()
{
	*reinterpret_cast<std::uint8_t**>(this->m_instance) = this->m_original_table;

	if (this->m_fake_table)
	{
		VirtualFree(this->m_fake_table, 0, MEM_RELEASE);
	}
}

void shadow_vmt::initialize(std::uint8_t* table)
{
	this->m_instance = *reinterpret_cast<std::uint8_t**>(table);
	this->m_original_table = *reinterpret_cast<std::uint8_t**>(this->m_instance);

	MEMORY_BASIC_INFORMATION mbi = { };
	while (VirtualQuery(reinterpret_cast<LPCVOID>(this->m_original_table[this->m_table_size]), &mbi, sizeof(mbi)))
	{
		if ((mbi.State != MEM_COMMIT) || (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) || !(mbi.Protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)))
		{
			break;
		}

		this->m_table_size++;
	}

	this->m_fake_table = static_cast<std::uint8_t*>(VirtualAlloc(nullptr, this->m_table_size * sizeof(void*), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));

	if (this->m_fake_table)
	{
		for (std::size_t i = 0; i < this->m_table_size; i++)
		{
			this->m_fake_table[i] = this->m_original_table[i];
		}
	}

	*reinterpret_cast<std::uint8_t**>(this->m_instance) = this->m_fake_table;
}

void* shadow_vmt::detour(std::size_t index, void* function)
{
	void* original_function = *reinterpret_cast<void**>(this->m_fake_table + index);

	*reinterpret_cast<void**>(this->m_fake_table + index) = function;

	this->m_hooks[index] = original_function;

	return original_function;
}

void shadow_vmt::release()
{
	*reinterpret_cast<std::uint8_t**>(this->m_instance) = this->m_original_table;

	if (this->m_fake_table)
	{
		VirtualFree(this->m_fake_table, 0, MEM_RELEASE);
	}
}
