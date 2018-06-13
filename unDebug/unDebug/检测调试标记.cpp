#include "stdafx.h"
#include <windows.h>
#include <winternl.h>
#pragma comment(lib, "ntdll.lib")

bool NQIP_ProcessDebugFlag()
{
	HANDLE hProcessDebugFlag= 0;
	NtQueryInformationProcess(
		GetCurrentProcess(),
		(PROCESSINFOCLASS)0x1F,
		&hProcessDebugFlag,
		sizeof(hProcessDebugFlag),
		NULL
	);
	return hProcessDebugFlag? false: true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	bool bDebug = NQIP_ProcessDebugFlag();
	if (bDebug) {
		printf("正在调试中\n");
	}
	else {
		printf("没有调试\n");
	}
	return 0;
}