#include"stdafx.h"
#include <Windows.h>


bool CreateChildProcess(LPWSTR lpPath, BOOL bWait)
{
	STARTUPINFO si = {};
	PROCESS_INFORMATION  pi = {};
	BOOL bRes = CreateProcess(lpPath, NULL, 0, 0, FALSE, 0, 0,NULL, &si, &pi);
	if (!bRes) {
		printf("创建失败\n");
		return false;
	}
	if (bWait) {
		WaitForSingleObject(pi.hProcess, 5000);
	}
	//关闭进程和线程句柄
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	printf("执行完毕\n");
	Sleep(3000);
	return true;
}

int _tmain(int argc, _TCHAR* argv[]) {
	printf("我是主进程\n");
	LPWSTR lpPath = L"C:\\Program Files (x86)\\FastStoneCapturecn\\FSCapture.exe";
	CreateChildProcess(lpPath, true);
}