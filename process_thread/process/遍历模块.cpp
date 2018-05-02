#include "stdafx.h"
#include <Windows.h>
#include <TlHelp32.h>


int _tmain(int argc, _TCHAR* argv[])
{
	MODULEENTRY32 me32 = { sizeof(MODULEENTRY32) };
	//me32.dwSize = sizeof(MODULEENTRY32);

	//HANDLE hModuleSnap = CreateToolhelp32SnapShot(TH32CS_SNAPMODULE32, ) //错误
	//HANDLE  hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32, 8688); //错误: TH32CS_SNAPMODULE32 不是32
	HANDLE  hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 8688);
	if (hModuleSnap == INVALID_HANDLE_VALUE) {
		printf("无法创建快照\n");
		return 0;
	}
	if (!Module32First(hModuleSnap, &me32)){
		printf("无模块\n");
		CloseHandle(hModuleSnap);
		return 0;
	}
	int nIndex = 0;
	do{
		printf("%d  Pid:%d ; Tid:%d ; path: %S, module: %S \n ", nIndex, me32.th32ProcessID, me32.th32ModuleID, me32.szExePath, me32.szModule);
	} while (Module32Next(hModuleSnap, &me32));
	CloseHandle(hModuleSnap);
	return 0;
}
