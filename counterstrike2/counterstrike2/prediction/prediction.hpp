#pragma once

#include "../source2-sdk/classes/user_cmd.hpp"

#include <cstdint>

namespace prediction
{
	void start(c_user_cmd* cmd);
	void end();

	std::uint32_t get_predicted_flags();
}