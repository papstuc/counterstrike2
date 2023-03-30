#pragma once

#include <cstdint>
#include <string>

namespace schema_system
{
    typedef struct _schema_offset_t
    {
        std::string class_name;
        std::string property_name;
        std::uint32_t offset;
    } schema_offset_t;

    bool initialize();
    std::uint32_t get_schema(std::string class_name, std::string property_name);
}

#define SCHEMA(class_name, property_name, function, type) \
__forceinline type& function() \
{ \
    std::uint32_t offset = schema_system::get_schema(class_name, property_name);  \
    return *reinterpret_cast<type*>(reinterpret_cast<std::uint64_t>(this) + offset); \
} \
