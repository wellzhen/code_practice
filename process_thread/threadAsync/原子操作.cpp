// 线程同步.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>

LONG g_num = 0;

DWORD WINAPI ThreadProc1(LPVOID lpThreadParameter)
{
	for (int i = 0; i < 50000000; i++) {
		InterlockedIncrement(&g_num);
	}
	return 0;
}
DWORD WINAPI ThreadProc2(LPVOID lpThreadParamter)
{
	for (int i = 0; i < 50000000; i++) {
		InterlockedIncrement(&g_num);
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	HANDLE hThread1 = CreateThread(NULL, 0, ThreadProc1, NULL, 0, 0);
	HANDLE hThread2 = CreateThread(NULL, 0, ThreadProc2, NULL, 0, 0);

	
	WaitForSingleObject(hThread1, -1);
	WaitForSingleObject(hThread2, -1);

	printf("%d\n", g_num);
    return 0;
}


