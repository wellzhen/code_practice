// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
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
		OutputDebugString(L"������plugin");
		break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		OutputDebugString(L"ж����plugin");
		break;
	}
	return TRUE;
}

