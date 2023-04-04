#include "hooks.hpp"

#include "../signatures.hpp"

#include "../utilities/minhook/MinHook.h"
#include "../utilities/utilities.hpp"
#include "../source2-sdk/sdk.hpp"
#include "../visuals/visuals.hpp"
#include "../combat/combat.hpp"
#include "../menu/menu.hpp"

#include "../utilities/imgui/imgui.h"
#include "../utilities/imgui/imgui_internal.h"
#include "../utilities/imgui/imgui_impl_win32.h"
#include "../utilities/imgui/imgui_impl_dx11.h"

#include <d3d11.h>
#include <cstdint>
#include <dxgi.h>

static hooks::level_init::function_t level_init_original = nullptr;
static hooks::frame_stage_notify::function_t frame_stage_notify_original = nullptr;
static hooks::create_move::function_t create_move_original = nullptr;
static hooks::swap_chain_present::function_t swap_chain_present_original = nullptr;
static hooks::swap_chain_resize_buffers::function_t swap_chain_resize_buffers_original = nullptr;
static hooks::mouse_input::function_t mouse_input_original = nullptr;
static hooks::window_procedure::function_t window_procedure_original = nullptr;

static ID3D11Device* device = nullptr;
static ID3D11DeviceContext* context = nullptr;
static HWND window = nullptr;
static ID3D11RenderTargetView* render_view = nullptr;

static void* get_virtual(void* class_pointer, std::uint32_t index)
{
	void** vtable = *static_cast<void***>(class_pointer);
	return vtable[index];
}

bool hooks::initialize()
{
	void* level_init_target = utilities::pattern_scan(L"client.dll", LEVEL_INIT);
	void* frame_stage_notify_target = utilities::pattern_scan(L"client.dll", FRAME_STAGE_NOTIFY);

	void* create_move_target = get_virtual(interfaces::csgo_input, csgo_input_vtable::CREATEMOVE);
	void* swap_chain_present_target = get_virtual(interfaces::renderer->swap_chain, render_vtable::PRESENT);
	void* swap_chain_resize_buffers_target = get_virtual(interfaces::renderer->swap_chain, render_vtable::RESIZE_BUFFERS);
	void* mouse_input_target = utilities::pattern_scan(L"client.dll", "40 53 48 83 EC ? 80 B9 ? ? ? ? ? 48 8B D9 75 ? 48 8B 0D");
	
	if (MH_Initialize() != MH_OK)
	{
		debug::log(L"[-] failed to initialize minhook\n");
		return false;
	}

	if (MH_CreateHook(level_init_target, &hooks::level_init::hook, reinterpret_cast<void**>(&level_init_original)) != MH_OK)
	{
		debug::log(L"[-] failed to hook level init\n");
		return false;
	}

	if (MH_CreateHook(frame_stage_notify_target, &hooks::frame_stage_notify::hook, reinterpret_cast<void**>(&frame_stage_notify_original)) != MH_OK)
	{
		debug::log(L"[-] failed to hook frame stage notify\n");
		return false;
	}

	if (MH_CreateHook(create_move_target, &hooks::create_move::hook, reinterpret_cast<void**>(&create_move_original)) != MH_OK)
	{
		debug::log(L"[-] failed to hook create move\n");
		return false;
	}

	if (MH_CreateHook(swap_chain_present_target, &hooks::swap_chain_present::hook, reinterpret_cast<void**>(&swap_chain_present_original)) != MH_OK)
	{
		debug::log(L"[-] failed to hook present\n");
		return false;
	}

	if (MH_CreateHook(swap_chain_resize_buffers_target, &hooks::swap_chain_resize_buffers::hook, reinterpret_cast<void**>(&swap_chain_resize_buffers_original)) != MH_OK)
	{
		debug::log(L"[-] failed to hook resize buffers\n");
		return false;
	}

	if (MH_CreateHook(mouse_input_target, &hooks::mouse_input::hook, reinterpret_cast<void**>(&mouse_input_original)) != MH_OK)
	{
		debug::log(L"[-] failed to hook resize buffers\n");
		return false;
	}

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
	{
		debug::log(L"[-] failed to enable hooks\n");
		return false;
	}

	debug::log(L"[+] hooks initialized\n");
	return true;
}

void hooks::release()
{
	SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<std::int64_t>(window_procedure_original));

	MH_Uninitialize();
	MH_DisableHook(MH_ALL_HOOKS);
}

std::int64_t __fastcall hooks::level_init::hook(std::int64_t a1, std::int64_t a2)
{
	sdk::update_global_vars();
	return level_init_original(a1, a2);
}

std::int64_t __fastcall hooks::frame_stage_notify::hook(std::int64_t a1, std::int32_t a2)
{
	return frame_stage_notify_original(a1, a2);
}

bool __fastcall hooks::create_move::hook(void* a1, std::uint32_t a2, std::uint8_t a3)
{
	create_move_original(a1, a2, a3);

	sdk::update_local_controller();
	sdk::update_local_player();

	user_cmd_t* user_cmd = interfaces::csgo_input->get_user_cmd(a1, a2);
	combat::run_aimbot(user_cmd);

	interfaces::client->set_view_angles({ 180, 0, 0 });

	return false;
}

HRESULT __fastcall hooks::swap_chain_present::hook(IDXGISwapChain* swap_chain, std::uint32_t sync_interval, std::uint32_t flags)
{
	if (!device)
	{
		ID3D11Texture2D* buffer = nullptr;
		DXGI_SWAP_CHAIN_DESC desc = { };

		swap_chain->GetBuffer(0, IID_PPV_ARGS(&buffer));

		if (buffer)
		{
			swap_chain->GetDevice(IID_PPV_ARGS(&device));
			device->CreateRenderTargetView(buffer, nullptr, &render_view);
			device->GetImmediateContext(&context);
			DXGI_SWAP_CHAIN_DESC desc;
			swap_chain->GetDesc(&desc);
			window = desc.OutputWindow;
		}

		if (window_procedure_original && window)
		{
			SetWindowLongPtrA(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(window_procedure_original));
			window_procedure_original = nullptr;
		}

		if (window)
		{
			window_procedure_original = reinterpret_cast<decltype(window_procedure_original)>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(hooks::window_procedure::hook)));
		}

		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX11_Init(device, context);

		sdk::update_screen_size();
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	visuals::run_player_esp();
	menu::render();

	ImGui::Render();

	context->OMSetRenderTargets(1, &render_view, nullptr);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return swap_chain_present_original(swap_chain, sync_interval, flags);
}

HRESULT __fastcall hooks::swap_chain_resize_buffers::hook(IDXGISwapChain* swap_chain, std::uint32_t buffer_count, std::uint32_t width, std::uint32_t height, DXGI_FORMAT new_format, std::uint32_t swap_chain_flags)
{
	if (render_view)
	{
		render_view->Release();
		render_view = nullptr;
	}

	if (context)
	{
		context->Release();
		context = nullptr;
	}

	if (device)
	{
		device->Release();
		device = nullptr;
	}

	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext();

	return swap_chain_resize_buffers_original(swap_chain, buffer_count, width, height, new_format, swap_chain_flags);
}

bool __fastcall hooks::mouse_input::hook(std::int64_t a1)
{
	if (menu::open)
	{
		return false;
	}

	return mouse_input_original(a1);
}

LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT __stdcall hooks::window_procedure::hook(HWND hwnd, std::uint32_t message, WPARAM wparam, LPARAM lparam)
{
	if (message == WM_KEYDOWN && LOWORD(wparam) == VK_INSERT)
	{
		menu::open = !menu::open;
	}

	LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	ImGui_ImplWin32_WndProcHandler(hwnd, message, wparam, lparam);
	if (menu::open)
	{
		switch (message)
		{
			case WM_MOUSEMOVE:
			case WM_NCMOUSEMOVE:
			case WM_MOUSELEAVE:
			case WM_NCMOUSELEAVE:
			case WM_LBUTTONDOWN:
			case WM_LBUTTONDBLCLK:
			case WM_RBUTTONDOWN:
			case WM_RBUTTONDBLCLK:
			case WM_MBUTTONDOWN:
			case WM_MBUTTONDBLCLK:
			case WM_XBUTTONDOWN:
			case WM_XBUTTONDBLCLK:
			case WM_LBUTTONUP:
			case WM_RBUTTONUP:
			case WM_MBUTTONUP:
			case WM_XBUTTONUP:
			case WM_MOUSEWHEEL:
			case WM_MOUSEHWHEEL:
			case WM_KEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
			case WM_SETFOCUS:
			case WM_KILLFOCUS:
			case WM_CHAR:
			case WM_DEVICECHANGE:
				return 1;
		}
	}

	return CallWindowProc(window_procedure_original, hwnd, message, wparam, lparam);
}