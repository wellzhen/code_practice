#include "stdafx.h"
#include <Windows.h>


int _tmain(int argc, _TCHAR* argv[])
{
	STARTUPINFO si = {};
	PROCESS_INFORMATION			pi = {};
	printf("当前进程A\n");
	HANDLE  hSemaphoreA = CreateSemaphore(NULL, 1, 1, L"daemonA");
	HANDLE  hSemaphoreB;
	while (true) {
		hSemaphoreB = OpenSemaphore(SEMAPHORE_ALL_ACCESS, NULL, L"daemonB");
		if (!hSemaphoreB) {
			printf("没有检查到B进程\n");
			if (CreateProcess(L"C:\\Users\\moonq\\Desktop\\B.exe", NULL, NULL, NULL, false, false, NULL, NULL, &si, &pi)) {
				printf("启动进程B成功\n");
			}
			else {
				printf("启动进程B失败\n");
			}
		}
		else {
			printf("B进程: ok\n");
			CloseHandle(hSemaphoreB);
		}
		Sleep(3000);
	}
}
