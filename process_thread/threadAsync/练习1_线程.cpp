#include "stdafx.h"
#include <Windows.h>


HANDLE hEvent;

int g_num = 0;
DWORD WINAPI ThreadProc1(LPVOID lpParameter)
{
	
	
	for (int i = 0; i < 10;) {
		WaitForSingleObject(hEvent, -1);
		if (g_num % 3 == 0) {
			printf("A");
			g_num++;
			i++;
		}
		SetEvent(hEvent);
	}
	
	return 0;
}

DWORD WINAPI ThreadProc2(LPVOID lpParameter)
{

	for (int i = 0; i < 10;) {
		WaitForSingleObject(hEvent, -1);
		if (g_num % 3 == 1) {
			printf("B");
			g_num++;
			i++;
		}
		SetEvent(hEvent);
	}
	
	return 0;
}

DWORD WINAPI ThreadProc3(LPVOID lpParameter)
{
	for (int i = 0; i < 10;) {
		WaitForSingleObject(hEvent, -1);
		if (g_num % 3 == 2) {
			printf("C");
			g_num++;
			i++;
		}
		SetEvent(hEvent);
	}
	
	return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{
	hEvent = CreateEvent(NULL, false, true, NULL);

	HANDLE  hThread1, hThread2, hThread3;
	hThread1 = CreateThread(NULL, 0, ThreadProc1, NULL, 0, 0);
	hThread2 = CreateThread(NULL, 0, ThreadProc2, NULL, 0, 0);
	hThread3 = CreateThread(NULL, 0, ThreadProc3, NULL, 0, 0);

	WaitForSingleObject(hThread1, -1);
	WaitForSingleObject(hThread2, -1);
	WaitForSingleObject(hThread3, -1);

	return 0;

}