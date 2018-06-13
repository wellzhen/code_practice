// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "DLL_TEST.h"
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		AlertBox();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		AlertBoxEnd();
		break;
	}
	return TRUE;
}

