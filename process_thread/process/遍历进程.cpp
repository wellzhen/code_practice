#include "stdafx.h"
#include <Windows.h>
#include <TlHelp32.h>


int _tmain(int argc, _TCHAR* argv[])
{
	PROCESSENTRY32 pe = {};
	pe.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		printf("无效的句柄值");
		return 0;
	}

	if (!Process32First(hProcessSnap, &pe)) {
		printf("无法获取进程\n");
		CloseHandle(hProcessSnap);
		return 0;
	}
	do {
		printf("父进程: %d, 进程ID : %d,  进程名: %S \n", pe.th32ParentProcessID, pe.th32ProcessID, pe.szExeFile);

	} while (Process32Next(hProcessSnap, &pe));


	return 0;
}