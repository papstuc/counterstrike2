#include "schema_system.hpp"
#include "../interfaces/interfaces.hpp"

#include <unordered_map>

static std::unordered_map<std::string, std::unordered_map<std::string, schema_system::schema_offset_t>> schema_data;

bool schema_system::initialize()
{
	std::vector<std::string> modules = { "client.dll", "engine2.dll", "schemasystem.dll" };

	for (std::string& module : modules)
	{
		schema_system_type_scope* schema_class = interfaces::schema_system->find_type_scope_for_module(module.c_str());

		if (!schema_class)
		{
			continue;
		}

		utl_ts_hash<schema_class_binding_t*> schema_classes = schema_class->get_classes();

		for (schema_class_binding_t* binding : schema_classes.get_elements())
		{
			schema_class_info_data_t* client_class_info = schema_class->find_type_declared_class(binding->binary_name);

			if (!client_class_info)
			{
				continue;
			}

			for (std::int16_t j = 0; j < client_class_info->field_size; j++)
			{
				schema_class_field_data_t* field = &client_class_info->fields[j];

				if (!binding->binary_name || !field || !field->name)
				{
					continue;
				}

				schema_data[binding->binary_name][field->name].class_name = binding->binary_name;
				schema_data[binding->binary_name][field->name].property_name = field->name;
				schema_data[binding->binary_name][field->name].offset = field->offset;
			}
		}
	}

	if (schema_data.size() == 0)
	{
		debug::log(L"[-] failed to initialize schema system\n");
		return false;
	}

	debug::log("[+] schema system initialized\n");
	return true;
}

std::uint32_t schema_system::get_schema(std::string class_name, std::string property_name)
{
	return schema_data[class_name][property_name].offset;
}

