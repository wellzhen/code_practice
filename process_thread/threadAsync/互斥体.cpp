#include "stdafx.h"
#include <Windows.h>

LONG g_num = 0;
HANDLE hMutex = NULL;

DWORD WINAPI ThreadProc1(LPVOID lpThreadParameter)
{
	for (int i = 0; i < 50000000; i++) {
		WaitForSingleObject(hMutex, -1);
		g_num++;
		if (g_num % 10000 == 0) {
			printf("%d\n", g_num);
		}
		ReleaseMutex(hMutex);
	}
	return 0;
}
DWORD WINAPI ThreadProc2(LPVOID lpThreadParamter)
{
	for (int i = 0; i < 50000000; i++) {
		WaitForSingleObject(hMutex, -1);
		g_num++;
		if (g_num % 10000 == 0) {
			printf("%d\n", g_num);
		}
		ReleaseMutex(hMutex);
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	hMutex = CreateMutex(NULL, NULL, NULL);

	HANDLE hThread1 = CreateThread(NULL, 0, ThreadProc1, NULL, 0, 0);
	HANDLE hThread2 = CreateThread(NULL, 0, ThreadProc2, NULL, 0, 0);


	WaitForSingleObject(hThread1, -1);
	WaitForSingleObject(hThread2, -1);

	printf("%d\n", g_num);
	return 0;
}
