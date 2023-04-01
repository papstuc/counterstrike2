#pragma once

#include <cstdint>
#include <array>
#include <vector>

class utl_memory_pool
{
public:
	std::int32_t block_size()
	{
		return this->m_blocks_per_blob;
	}

	std::int32_t count()
	{
		return this->m_block_allocated_size;
	}

	std::int32_t peak_count()
	{
		return this->m_peak_alloc;
	}

private:
	std::int32_t m_block_size = 0;
	std::int32_t m_blocks_per_blob = 0;
	std::int32_t m_grow_mode = 0;
	std::int32_t m_blocks_allocated = 0;
	std::int32_t m_block_allocated_size = 0;
	std::int32_t m_peak_alloc = 0;
};

template<class T, class key_type = std::uint64_t>
class utl_ts_hash
{
public:
	static std::uint64_t invalid_handle()
	{
		return static_cast<std::uint64_t>(0);
	}

	std::int32_t block_size()
	{
		return this->m_entry_memory.block_size();
	}

	std::int32_t count()
	{
		return this->m_entry_memory.count();
	}

	std::vector<T> get_elements()
	{
		std::vector<T> list;

		std::int32_t n_count = this->count();
		std::int32_t n_index = 0;
		hash_unallocated_data_t* unallocated_data = this->m_buckets.m_unallocated_data;
		for (hash_unallocated_data_t* element = unallocated_data; element; element = element->m_next)
		{
			for (std::int32_t i = 0; i < this->block_size() && i != n_count; i++)
			{
				list.emplace_back(element->m_current_block_list.at(i).m_data);
				n_index++;

				if (n_index >= n_count)
				{
					break;
				}
			}
		}
		return list;
	}

public:
	template<typename dataT>
	struct hash_fixed_data_internal_t
	{
		key_type m_ui_key;
		hash_fixed_data_internal_t<dataT>* m_next;
		dataT m_data;
	};

	using hash_fixed_data_t = hash_fixed_data_internal_t< T >;

	template< typename dataT >
	struct hash_fixed_struct_data_internal_t
	{
		dataT m_data;
		key_type m_ui_key;
	};

	using hash_fixed_struct_data = hash_fixed_struct_data_internal_t<T>;

	struct hash_struct_data_t
	{
		char pad_1[0x10];
		std::array<hash_fixed_struct_data, 256> m_list;
	};

	struct hash_allocated_data_t
	{
	public:
		std::array<hash_fixed_data_t, 128> get_list()
		{
			return this->m_list;
		}

	private:
		char pad_1[0x18];
		std::array<hash_fixed_data_t, 128> m_list;
	};

	template<typename dataT>
	struct hash_bucket_data_internal_t
	{
		dataT m_data;
		hash_fixed_data_internal_t<dataT>* m_next;
		key_type m_ui_key;
	};

	using hash_bucket_data_t = hash_bucket_data_internal_t<T>;

	struct hash_unallocated_data_t
	{
		hash_unallocated_data_t* m_next = nullptr;
		key_type m_6114;
		key_type m_ui_key;
		key_type m_i_unk_1;
		std::array<hash_bucket_data_t, 256> m_current_block_list;
	};

	struct hash_bucket_t
	{
		hash_struct_data_t* m_struct_data = nullptr;
		void* m_mutex_list = nullptr;
		hash_allocated_data_t* m_allocated_data = nullptr;
		hash_unallocated_data_t* m_unallocated_data = nullptr;
	};

	utl_memory_pool m_entry_memory;
	hash_bucket_t m_buckets;
	bool m_needs_commit = false;
};

typedef struct _schema_class_info_data_t schema_class_info_data_t;
class schema_system_type_scope;

class schema_enum_binding
{
public:
	virtual const char* get_binding_name() = 0;
	virtual void* as_class_binding() = 0;
	virtual schema_enum_binding* as_enum_binding() = 0;
	virtual const char* get_binary_name() = 0;
	virtual const char* get_project_name() = 0;
public:
	char* m_binding_name;
};

class schema_type
{
public:
	bool get_sizes(int* out_size1, uint8_t* unk_probably_not_size)
	{
		return reinterpret_cast<int(__thiscall*)(void*, int*, uint8_t*)>(this->m_vtable[3])(this, out_size1, unk_probably_not_size);
	}
public:
	bool get_size(int* out_size)
	{
		uint8_t smh = 0;
		return get_sizes(out_size, &smh);
	}
public:
	std::uintptr_t* m_vtable;
	const char* m_name;
	schema_system_type_scope* m_type_scope;
	std::uint8_t m_type_category;
	std::uint8_t m_atomic_category;

	schema_type* get_ref_class()
	{
		if (this->m_type_category != 1)
		{
			return nullptr;
		}

		schema_type* ptr = this->m_schema_type;

		while (ptr && ptr->m_type_category == 1)
		{
			ptr = ptr->m_schema_type;
		}

		return ptr;
	}

	typedef struct _array_t
	{
		std::uint32_t array_size;
		std::uint32_t unknown;
		schema_type* element_type_;
	} array_t;

	typedef struct _atomic_t
	{
		std::uint64_t gap[2];
		schema_type* template_typename;
	} atomic_t;

	typedef struct _atomic_tt
	{
		std::uint64_t gap[2];
		schema_type* templates[2];
	} atomic_tt;

	typedef struct _atomic_i
	{
		std::uint64_t gap[2];
		std::uint64_t integer;
	} atomic_i;

	union
	{
		schema_type* m_schema_type;
		schema_class_info_data_t* m_class_info;
		void* m_enum_binding_;
		array_t m_array_;
		atomic_t m_atomic_t_;
		atomic_tt m_atomic_tt_;
		atomic_i m_atomic_i_;
	};
};

typedef struct _schema_class_field_data_t
{
	const char* name;
	schema_type* type;
	short offset;
	unsigned char pad1[0xE];
} schema_class_field_data_t;

typedef struct _schema_class_info_data_t
{
	unsigned char pad1[0x8];
	const char* name;
	char* module;
	std::int32_t size;
	std::int16_t field_size;
	std::int16_t static_size;
	std::int16_t metadata_size;
	std::int16_t i_unk1;
	std::int16_t i_unk2;
	std::int16_t i_unk3;
	schema_class_field_data_t* fields;
} schema_class_info_data_t;

typedef struct _schema_type_t
{
	std::uintptr_t* vtable;
	const char* name;
} schema_type_t;

typedef struct _schema_class_binding_t
{
	_schema_class_binding_t* parent;
	const char* binary_name;
	const char* module_name;
	const char* class_name;
	void* class_info_old_synthesized;
	void* class_info;
	void* this_module_binding_pointer;
	schema_type_t* schema_type;
} schema_class_binding_t;

class schema_system_type_scope
{
public:
	schema_class_info_data_t* find_type_declared_class(const char* name)
	{
		using function_t = schema_class_info_data_t*(__thiscall*)(void*, const char*);
		return (*reinterpret_cast<function_t**>(this))[2](this, name);
	}

	utl_ts_hash<schema_class_binding_t*> get_classes()
	{
		return this->m_classes;
	}

private:
	char pad1[0x8];
	std::array<char, 256> m_name = { };
	unsigned char pad2[0x450];
	utl_ts_hash<schema_class_binding_t*> m_classes;
	char pad3[0x2804];
};

class i_schema_system
{
public:
	schema_system_type_scope* global_type_scope()
	{
		using function_t = schema_system_type_scope*(__thiscall*)(void*);
		return (*reinterpret_cast<function_t**>(this))[11](this);
	}

	schema_system_type_scope* find_type_scope_for_module(const char* module)
	{
		using function_t = schema_system_type_scope*(__thiscall*)(void*, const char*);
		return (*reinterpret_cast<function_t**>(this))[13](this, module);
	}
};