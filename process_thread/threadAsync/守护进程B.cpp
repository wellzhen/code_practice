#include "stdafx.h"
#include <Windows.h>


int _tmain(int argc, _TCHAR* argv[])
{
	STARTUPINFO si = {};
	PROCESS_INFORMATION			pi = {};
	printf("当前进程B\n");
	HANDLE  hSemaphoreB = CreateSemaphore(NULL, 1, 1, L"daemonB");
	HANDLE  hSemaphoreA;
	while (true) {
		hSemaphoreA = OpenSemaphore(SEMAPHORE_ALL_ACCESS, NULL, L"daemonA");
		if (!hSemaphoreA) {
			printf("没有检查到A进程\n");
			if (CreateProcess(L"C:\\Users\\moonq\\Desktop\\A.exe", NULL, NULL, NULL, false, false, NULL, NULL, &si, &pi)) {
				printf("启动进程A成功\n");
			}
			else {
				printf("启动进程A失败\n");
			}
		}
		else {
			printf("A进程: ok\n");
			CloseHandle(hSemaphoreA);
		}
		Sleep(3000);
	}
}
