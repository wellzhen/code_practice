#include"stdafx.h"
#include <Windows.h>


bool CreateChildProcess(LPWSTR lpPath, BOOL bWait)
{
	STARTUPINFO si = {};
	PROCESS_INFORMATION  pi = {};
	BOOL bRes = CreateProcess(lpPath, NULL, 0, 0, FALSE, 0, 0,NULL, &si, &pi);
	if (!bRes) {
		printf("����ʧ��\n");
		return false;
	}
	if (bWait) {
		WaitForSingleObject(pi.hProcess, 5000);
	}
	//�رս��̺��߳̾��
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	printf("ִ�����\n");
	Sleep(3000);
	return true;
}

int _tmain(int argc, _TCHAR* argv[]) {
	printf("����������\n");
	LPWSTR lpPath = L"C:\\Program Files (x86)\\FastStoneCapturecn\\FSCapture.exe";
	CreateChildProcess(lpPath, true);
}