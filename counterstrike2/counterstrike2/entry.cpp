#include <Windows.h>

#include "console.hpp"

DWORD WINAPI initialize(void* instance)
{
#ifdef _DEBUG
	console::initialize(L"counterstrike2 debug");
#endif

	FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);

	return TRUE;
}

DWORD WINAPI release()
{
#ifdef _DEBUG
	console::release();
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