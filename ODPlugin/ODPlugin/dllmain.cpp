// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

HMODULE g_hModule;
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		g_hModule = hModule;
	case DLL_THREAD_ATTACH:
		OutputDebugString(L"加载了plugin");
		break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		OutputDebugString(L"卸载了plugin");
		break;
	}
	return TRUE;
}

