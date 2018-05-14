#include "stdafx.h"
#include <Windows.h>

LONG g_num = 0;
CRITICAL_SECTION cs = {};

DWORD WINAPI ThreadProc1(LPVOID lpThreadParameter)
{
	for (int i = 0; i < 50000000; i++) {
		EnterCriticalSection(&cs);
		InterlockedIncrement(&g_num);
		LeaveCriticalSection(&cs);
	}
	return 0;
}
DWORD WINAPI ThreadProc2(LPVOID lpThreadParamter)
{
	for (int i = 0; i < 10000000; i++) {
		EnterCriticalSection(&cs);
		InterlockedIncrement(&g_num);
		LeaveCriticalSection(&cs);
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{

	InitializeCriticalSection(&cs);

	HANDLE hThread1 = CreateThread(NULL, 0, ThreadProc1, NULL, 0, 0);
	HANDLE hThread2 = CreateThread(NULL, 0, ThreadProc2, NULL, 0, 0);

	int sum = 0;
	for (int i = 0; i < 10000000; i++) {
		sum += i;
	}

	WaitForSingleObject(hThread1, -1);
	WaitForSingleObject(hThread2, -1);

	printf("%d\n", g_num);
	return 0;
}
