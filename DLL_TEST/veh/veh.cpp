// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include<windows.h>



LONG WINAPI VehHandler(EXCEPTION_POINTERS* pException)
{

	MessageBox(NULL, L"::VeHandler\n", NULL, NULL);
	//return EXCEPTION_CONTINUE_EXECUTION;//����ִ��:�ص��쳣������λ�ü���ִ��
	return EXCEPTION_CONTINUE_SEARCH;//����������һ���쳣������
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

