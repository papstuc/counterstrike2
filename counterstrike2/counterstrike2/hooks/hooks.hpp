#pragma once

#include <cstdint>
#include <utility>
#include <dxgi.h>


namespace hooks
{
	bool initialize();
	void release();

	namespace level_init
	{
		using function_t = std::int64_t(__fastcall*)(std::int64_t, std::int64_t);
		std::int64_t __fastcall hook(std::int64_t a1, std::int64_t a2);
	}

	namespace frame_stage_notify
	{
		using function_t = std::int64_t(__fastcall*)(std::int64_t, std::int32_t);
		std::int64_t __fastcall hook(std::int64_t a1, std::int32_t a2);
	}

	namespace create_move
	{
		using function_t = bool(__fastcall*)(void*, std::uint32_t, std::uint8_t);
		bool __fastcall hook(void* a1, std::uint32_t a2, std::uint8_t a3);
	}

	namespace swap_chain_present
	{
		using function_t = HRESULT(__fastcall*)(IDXGISwapChain*, std::uint32_t, std::uint32_t);
		HRESULT __fastcall hook(IDXGISwapChain* swap_chain, std::uint32_t sync_interval, std::uint32_t flags);
	}

	namespace swap_chain_resize_buffers
	{
		using function_t = HRESULT(__fastcall*)(IDXGISwapChain*, std::uint32_t, std::uint32_t, std::uint32_t, DXGI_FORMAT, std::uint32_t);
		HRESULT __fastcall hook(IDXGISwapChain* swap_chain, std::uint32_t buffer_count, std::uint32_t width, std::uint32_t height, DXGI_FORMAT new_format, std::uint32_t swap_chain_flags);
	}

	namespace mouse_input
	{
		using function_t = bool(__fastcall*)(std::int64_t);
		bool __fastcall hook(std::int64_t a1);
	}

	namespace window_procedure
	{
		using function_t = LRESULT(__stdcall*)(HWND, std::uint32_t, WPARAM, LPARAM);
		LRESULT __stdcall hook(HWND hwnd, std::uint32_t message, WPARAM wparam, LPARAM lparam);
	}
}