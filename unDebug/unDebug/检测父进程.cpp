#include "stdafx.h"
#include <windows.h>
#include <winternl.h>
#pragma comment(lib, "ntdll.lib");

bool NQIP_CheckParentProcess()
{
	struct PROCESS_BASIC_INFORMATION {
		ULONG ExitStatus;
		PPEB PebBaseAddress;
		ULONG AffinityMask;
		LONG BasePriority;
		ULONG UniqueProcessId;
		ULONG InheritedFromUniqueProcessId; 
	} stcProcInfo;

	NtQueryInformationProcess(
		GetCurrentProcess(),
		ProcessBasicInformation,
		&stcProcInfo,
		sizeof(stcProcInfo),
		NULL
	);
	DWORD ExplorerPID = 0;
	DWORD CurrentPID = stcProcInfo.InheritedFromUniqueProcessId;
	GetWindowThreadProcessId(FindWindow(L"Progman", NULL), &ExplorerPID);

	return ExplorerPID == CurrentPID ? false : true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	bool bIsDebug = NQIP_CheckParentProcess();
	if (bIsDebug) {
		printf("正在被调试\n");

	}
	else {
		printf("没有被调试\n");
	}
	system("pause");
	return 0;
}