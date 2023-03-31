#include "hooks.hpp"

#include "../utilities/minhook/MinHook.h"
#include "../utilities/utilities.hpp"
#include "../source2-sdk/sdk.hpp"
#include "../visuals/visuals.hpp"

#include "../utilities/imgui/imgui.h"
#include "../utilities/imgui/imgui_internal.h"
#include "../utilities/imgui/imgui_impl_win32.h"
#include "../utilities/imgui/imgui_impl_dx11.h"

#include <d3d11.h>
#include <cstdint>
#include <dxgi.h>

static hooks::create_move::function_t create_move_original = nullptr;
static hooks::level_init::function_t level_init_original = nullptr;
static hooks::frame_stage_notify::function_t frame_stage_notify_original = nullptr;
static hooks::swap_chain_present::function_t swap_chain_present_original = nullptr;
static hooks::swap_chain_resize_buffers::function_t swap_chain_resize_buffers_original = nullptr;

static ID3D11Device* device = nullptr;
static ID3D11DeviceContext* context = nullptr;
static HWND window = nullptr;
static ID3D11RenderTargetView* render_view = nullptr;

bool hooks::initialize()
{
	void* create_move_target = utilities::get_virtual(interfaces::csgo_input, csgo_input_vtable::CREATEMOVE);
	void* level_init_target = utilities::pattern_scan(L"client.dll", "48 89 5C 24 ? 57 48 83 EC ? 48 8B 0D ? ? ? ? 48 8B DA 45 33 C9");
	void* frame_stage_notify_target = utilities::pattern_scan(L"client.dll", "48 89 5C 24 ? 56 48 83 EC ? 8B 05 ? ? ? ? 8D 5A");
	void* swap_chain_present_target = utilities::get_virtual(interfaces::render->swap_chain, render_vtable::PRESENT);
	void* swap_chain_resize_buffers_target = utilities::get_virtual(interfaces::render->swap_chain, render_vtable::RESIZE_BUFFERS);

	if (MH_Initialize() != MH_OK)
	{
		debug::log(L"[-] failed to initialize minhook\n");
		return false;
	}

	if (MH_CreateHook(create_move_target, &hooks::create_move::hook, reinterpret_cast<void**>(&create_move_original)) != MH_OK)
	{
		debug::log(L"[-] failed to hook create move\n");
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
	MH_Uninitialize();
	MH_DisableHook(MH_ALL_HOOKS);
}

std::byte* __fastcall hooks::create_move::hook(void* csgoinput, unsigned int a2, unsigned __int8 a3)
{
	sdk::local_player = (interfaces::engine->is_connected() && interfaces::engine->is_in_game()) ? static_cast<player_t*>(sdk::get_player_pawn_handle(0)) : nullptr;
	return create_move_original(csgoinput, a2, a3);
}

std::int64_t __fastcall hooks::level_init::hook(std::int64_t a1, std::int64_t a2)
{
	interfaces::globals = *reinterpret_cast<global_vars_t**>(utilities::resolve_rip(utilities::pattern_scan(L"client.dll", "48 8B 05 ? ? ? ? 4C 8D 0D ? ? ? ? F2 0F 11 74 24 ? 4C 8D 05 ? ? ? ? BA"), 3, 7));
	return level_init_original(a1, a2);
}

std::int64_t __fastcall hooks::frame_stage_notify::hook(std::int64_t a1, std::int32_t a2)
{
	return frame_stage_notify_original(a1, a2);
}

HRESULT __fastcall hooks::swap_chain_present::hook(IDXGISwapChain* swap_chain, std::uint32_t sync_interval, std::uint32_t flags)
{
	if (!device)
	{
		ID3D11Texture2D* buffer = nullptr;

		swap_chain->GetBuffer(0, IID_PPV_ARGS(&buffer));

		if (buffer)
		{
			swap_chain->GetDevice(IID_PPV_ARGS(&device));
			device->CreateRenderTargetView(buffer, nullptr, &render_view);
			device->GetImmediateContext(&context);
		}

		DXGI_SWAP_CHAIN_DESC desc;
		swap_chain->GetDesc(&desc);
		window = desc.OutputWindow;

		/*if (window_procedure_original && window)
		{
			SetWindowLongPtrA(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(window_procedure_original));
			window_procedure_original = nullptr;
		}

		if (window)
		{
			window_procedure_original = reinterpret_cast<decltype(window_procedure_original)>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(hooks::window_procedure::hook)));
		}

		menu::initialize(window, device, context);*/

		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX11_Init(device, context);

		std::int32_t height, width;
		interfaces::engine->get_screen_size(width, height);

		sdk::screen_height = height;
		sdk::screen_width = width;
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	visuals::run_player_esp();

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

	return swap_chain_resize_buffers_original(swap_chain, buffer_count, width, height, new_format, swap_chain_flags);
}
