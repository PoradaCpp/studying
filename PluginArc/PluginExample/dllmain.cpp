// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

BOOL APIENTRY DllMain (HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// attach to process
		// return FALSE to fail DLL load
		break;
	case DLL_THREAD_ATTACH:
		// detach from process
		break;
	case DLL_THREAD_DETACH:
		// attach to thread
		break;
	case DLL_PROCESS_DETACH:
		// detach from thread
		break;
	}
	return TRUE;
}

