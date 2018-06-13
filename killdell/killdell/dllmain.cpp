// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include<windows.h>

char g_OldBytes[5] = {};
char g_NewBytes[5] = { 0xE9 };
void OnHook();
void UnHook();

HANDLE WINAPI MyOpenProcess(
	_In_ DWORD dwDesiredAccess,
	_In_ BOOL  bInheritHandle,
	_In_ DWORD dwProcessId
) {
	//MessageBoxW(NULL, L"openProcess", L"hook success", MB_OK);
	return NULL;
}
void OnHook()
{
	/*
	//保存原字节
	memcpy(g_OldBytes, MessageBoxW, 5);
	//计算偏移量
	DWORD dwOffset = (DWORD)MyMessageBoxW - (DWORD)MessageBoxW - 5;
	memcpy(g_NewBytes + 1, &dwOffset, 4);

	DWORD dwOldProctect;
	VirtualProtect(MessageBoxW, 5, PAGE_READWRITE, &dwOldProctect);
	//修改为Jmp XXXX
	memcpy(MessageBoxW, g_NewBytes, 5);
	VirtualProtect(MessageBoxW, 5, dwOldProctect, &dwOldProctect);
	*/
	//保存原字节
	memcpy(g_OldBytes, OpenProcess, 5);
	//计算偏移量
	DWORD dwOffset = (DWORD)MyOpenProcess - (DWORD)OpenProcess - 5;
	memcpy(g_NewBytes + 1, &dwOffset, 4);

	DWORD dwOldProctect;
	VirtualProtect(OpenProcess, 5, PAGE_READWRITE, &dwOldProctect);
	//修改为Jmp XXXX
	memcpy(OpenProcess, g_NewBytes, 5);
	VirtualProtect(OpenProcess, 5, dwOldProctect, &dwOldProctect);


}

void UnHook()
{
	/*
	DWORD dwOldProctect;
	VirtualProtect(MessageBoxW, 5, PAGE_READWRITE, &dwOldProctect);
	memcpy(MessageBoxW, g_OldBytes, 5);
	VirtualProtect(MessageBoxW, 5, dwOldProctect, &dwOldProctect);
	*/
	DWORD dwOldProctect;
	VirtualProtect(OpenProcess, 5, PAGE_READWRITE, &dwOldProctect);
	memcpy(OpenProcess, g_OldBytes, 5);
	VirtualProtect(OpenProcess, 5, dwOldProctect, &dwOldProctect);
}



BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		OnHook();
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

