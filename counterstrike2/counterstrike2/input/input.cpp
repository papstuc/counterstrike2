#include "input.hpp"

#include <array>
#include <Windows.h>

static std::array<bool, 256> key_states = { };

void input::handle(std::uint32_t message, std::uint64_t wparam)
{
	switch (message)
	{
		case WM_LBUTTONDOWN:
			key_states[VK_LBUTTON] = true;
			break;
		case WM_LBUTTONUP:
			key_states[VK_LBUTTON] = false;
			break;
		case WM_RBUTTONDOWN:
			key_states[VK_RBUTTON] = true;
			break;
		case WM_RBUTTONUP:
			key_states[VK_RBUTTON] = false;
			break;
		case WM_MBUTTONDOWN:
			key_states[VK_MBUTTON] = true;
			break;
		case WM_MBUTTONUP:
			key_states[VK_MBUTTON] = false;
			break;
		case WM_KEYDOWN:
			key_states[wparam] = true;
			break;
		case WM_KEYUP:
			key_states[wparam] = false;
			break;
		case WM_XBUTTONDOWN:
		{
			switch (GET_XBUTTON_WPARAM(wparam))
			{
				case XBUTTON1:
					key_states[VK_XBUTTON1] = true;
					break;
				case XBUTTON2:
					key_states[VK_XBUTTON2] = true;
					break;
				default:
					break;
			}
			break;
		}
		case WM_XBUTTONUP:
		{
			switch (GET_XBUTTON_WPARAM(wparam))
			{
				case XBUTTON1:
					key_states[VK_XBUTTON1] = false;
					break;
				case XBUTTON2:
					key_states[VK_XBUTTON2] = false;
					break;
				default:
					break;
			}

			break;
		}
	}
}

bool input::key_pressed(std::uint32_t virtual_key)
{
	return key_states[virtual_key];
}
