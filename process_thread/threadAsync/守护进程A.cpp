#include "stdafx.h"
#include <Windows.h>


int _tmain(int argc, _TCHAR* argv[])
{
	STARTUPINFO si = {};
	PROCESS_INFORMATION			pi = {};
	printf("��ǰ����A\n");
	HANDLE  hSemaphoreA = CreateSemaphore(NULL, 1, 1, L"daemonA");
	HANDLE  hSemaphoreB;
	while (true) {
		hSemaphoreB = OpenSemaphore(SEMAPHORE_ALL_ACCESS, NULL, L"daemonB");
		if (!hSemaphoreB) {
			printf("û�м�鵽B����\n");
			if (CreateProcess(L"C:\\Users\\moonq\\Desktop\\B.exe", NULL, NULL, NULL, false, false, NULL, NULL, &si, &pi)) {
				printf("��������B�ɹ�\n");
			}
			else {
				printf("��������Bʧ��\n");
			}
		}
		else {
			printf("B����: ok\n");
			CloseHandle(hSemaphoreB);
		}
		Sleep(3000);
	}
}
