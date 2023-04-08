#include "prediction.hpp"

#include "../source2-sdk/sdk.hpp"

static float old_current_time = 0.f;
static float old_frame_time = 0.f;
static std::int32_t prediction_seed = 0;
static std::uint32_t predicted_flags = 0;

void prediction::start(c_user_cmd* cmd)
{
	if (!sdk::local_player)
	{
		return;
	}

	predicted_flags = sdk::local_player->flags();

	// random_seed

	old_current_time = interfaces::globals->current_time;
	old_frame_time = interfaces::globals->frame_time;

	interfaces::globals->current_time = sdk::local_controller->tick_base() * interfaces::globals->interval_per_tick;
	interfaces::globals->current_time2 = sdk::local_controller->tick_base() * interfaces::globals->interval_per_tick;

	interfaces::globals->frame_time = interfaces::globals->interval_per_tick;
	interfaces::globals->frame_time2 = interfaces::globals->interval_per_tick;

}

void prediction::end()
{
	if (!sdk::local_player)
	{
		return;
	}

	interfaces::globals->current_time = old_current_time;
	interfaces::globals->current_time2 = old_current_time;

	interfaces::globals->frame_time = old_current_time;
	interfaces::globals->frame_time2 = old_current_time;
}

std::uint32_t prediction::get_predicted_flags()
{
	return predicted_flags;
}