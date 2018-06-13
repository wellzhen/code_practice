// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include<windows.h>
#include <tchar.h>

HINSTANCE g_hIntance = 0;
HHOOK g_Hook = 0;

LRESULT CALLBACK KeyboardProc(
	_In_  int code,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
)
{
	OutputDebugString(L"hello");
	// 判断是否wParam与lParam都有键盘消息，是的话则执行打印操作
	if (code == HC_ACTION) {
		// 将256个虚拟键的状态拷贝到指定的缓冲区中，如果成功则继续
		BYTE KeyState[256] = { 0 };
		if (GetKeyboardState(KeyState)) {
			// 得到第16–23位，键盘虚拟码
			LONG  KeyInfo = lParam;
			UINT  keyCode = (KeyInfo >> 16) & 0x00ff;
			WCHAR wKeyCode = 0;
			ToAscii((UINT)wParam, keyCode, KeyState, (LPWORD)&wKeyCode, 0);
			// 将其打印出来
			WCHAR szInfo[2] = { 0 };
			szInfo[0] = wKeyCode;
			//swprintf_s(szInfo,512, L"Hook%c", (char)wKeyCode);
			OutputDebugString(szInfo);
			return 0;
		}
	}

	// 	if (HC_ACTION == code)
	// 	{
	// 		WCHAR vk[3] = {};
	// 		vk[0] = wParam;
	// 		OutputDebugString(vk);
	// 		//if (lParam & 0x80000000)
	// // 		{
	// // 
	// // 		}
	// 	}
	return CallNextHookEx(g_Hook, code, wParam, lParam);
}
extern "C" __declspec(dllexport)
void OnHook()
{
	OutputDebugString(L"begin to onHook");
	g_Hook = SetWindowsHookExW(WH_KEYBOARD, KeyboardProc, g_hIntance, 0);
	if (g_Hook == NULL)
	{
		OutputDebugString(L"SetWindowsHookEx 失败\n");
		return;
	}
	else {
		OutputDebugString(L"Sucess to OnHook()");
	}
}

void UnHook()
{
	if (g_Hook != NULL)
	{
		UnhookWindowsHookEx(g_Hook);
	}
}
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		OutputDebugString(L"dll 加载成功");
		g_hIntance = hModule;
		OnHook();
		break;
		// 	case DLL_THREAD_ATTACH:
		// 	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		//UnHook();
		OutputDebugString(L"dell 被卸载了");
		break;
	}
	return TRUE;
}

