#include <Windows.h>
#include <chrono>
#include <thread>

#include "source2-sdk/interfaces/interfaces.hpp"
#include "utilities/debug/debug.hpp"
#include "hooks/hooks.hpp"

DWORD WINAPI initialize(void* instance)
{
#ifdef _DEBUG
	debug::initialize(L"counterstrike2 debug");
#endif
	hooks::initialize();
	
	while (!GetAsyncKeyState(VK_END))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(250));
	FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);

	return TRUE;
}

DWORD WINAPI release()
{
#ifdef _DEBUG
	debug::release();
#endif 

	return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE instance, DWORD call_reason, void* reserved)
{
	switch (call_reason)
	{
		case DLL_PROCESS_ATTACH:
			if (HANDLE handle = CreateThread(nullptr, 0, initialize, instance, 0, nullptr))
			{
				CloseHandle(handle);
			}
			break;

		case DLL_THREAD_ATTACH:
			break;

		case DLL_THREAD_DETACH:
			break;

		case DLL_PROCESS_DETACH:
			release();
			break;

		default:
			break;
	}

	return TRUE;
}