#include "stdafx.h"
#include <Windows.h>


int _tmain(int argc, _TCHAR* argv[])
{
	STARTUPINFO si = {};
	PROCESS_INFORMATION			pi = {};
	printf("��ǰ����B\n");
	HANDLE  hSemaphoreB = CreateSemaphore(NULL, 1, 1, L"daemonB");
	HANDLE  hSemaphoreA;
	while (true) {
		hSemaphoreA = OpenSemaphore(SEMAPHORE_ALL_ACCESS, NULL, L"daemonA");
		if (!hSemaphoreA) {
			printf("û�м�鵽A����\n");
			if (CreateProcess(L"C:\\Users\\moonq\\Desktop\\A.exe", NULL, NULL, NULL, false, false, NULL, NULL, &si, &pi)) {
				printf("��������A�ɹ�\n");
			}
			else {
				printf("��������Aʧ��\n");
			}
		}
		else {
			printf("A����: ok\n");
			CloseHandle(hSemaphoreA);
		}
		Sleep(3000);
	}
}
