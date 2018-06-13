// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
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
	// �ж��Ƿ�wParam��lParam���м�����Ϣ���ǵĻ���ִ�д�ӡ����
	if (code == HC_ACTION) {
		// ��256���������״̬������ָ���Ļ������У�����ɹ������
		BYTE KeyState[256] = { 0 };
		if (GetKeyboardState(KeyState)) {
			// �õ���16�C23λ������������
			LONG  KeyInfo = lParam;
			UINT  keyCode = (KeyInfo >> 16) & 0x00ff;
			WCHAR wKeyCode = 0;
			ToAscii((UINT)wParam, keyCode, KeyState, (LPWORD)&wKeyCode, 0);
			// �����ӡ����
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
		OutputDebugString(L"SetWindowsHookEx ʧ��\n");
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
		OutputDebugString(L"dll ���سɹ�");
		g_hIntance = hModule;
		OnHook();
		break;
		// 	case DLL_THREAD_ATTACH:
		// 	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		//UnHook();
		OutputDebugString(L"dell ��ж����");
		break;
	}
	return TRUE;
}

