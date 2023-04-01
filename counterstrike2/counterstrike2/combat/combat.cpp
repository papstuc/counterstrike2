#include "combat.hpp"

#include "../config/config.hpp"
#include "../source2-sdk/interfaces/interfaces.hpp"

void run_aimbot(user_cmd_t* cmd)
{
	if (!config::context.aimbot)
	{
		return;
	}
}