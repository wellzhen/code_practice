// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include<windows.h>



LONG WINAPI VehHandler(EXCEPTION_POINTERS* pException)
{

	MessageBox(NULL, L"::VeHandler\n", NULL, NULL);
	//return EXCEPTION_CONTINUE_EXECUTION;//继续执行:回到异常触发的位置继续执行
	return EXCEPTION_CONTINUE_SEARCH;//继续搜索下一个异常处理函数
}




BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		AddVectoredExceptionHandler(true, VehHandler);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

