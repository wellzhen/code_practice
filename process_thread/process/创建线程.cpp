#include "stdafx.h"
#include <Windows.h>

DWORD  WINAPI   ThreadProc(LPVOID pParam) 
{
	int i = 0;
	while (1) {
		printf("�������߳�: %d\n", i);
		i++;
		Sleep(30);
	}
	
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD dwThreadId = 0;
	//�����߳�
	HANDLE hThread = CreateThread(NULL, 0, ThreadProc, L"ThreadProc", NULL, &dwThreadId);

	//WaitForSingleObject(hThread, 5000);
	while (true) {
		printf("���߳�\n");
		Sleep(30);
	}
	return 0;
}