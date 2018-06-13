#include "stdafx.h"
#include <windows.h>
#include <winternl.h>
#pragma comment(lib, "ntdll.lib")

bool NQIP_ProcessDebugObjectHandle()
{
	HANDLE hProcessDebugObjectHandle = 0;
	NtQueryInformationProcess(
		GetCurrentProcess(),
		(PROCESSINFOCLASS)0x1E,
		&hProcessDebugObjectHandle,
		sizeof(hProcessDebugObjectHandle),
		NULL
	);
	return hProcessDebugObjectHandle ? true : false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	bool bDebug = NQIP_ProcessDebugObjectHandle();
	if (bDebug) {
		printf("���ڵ�����\n");
	}
	else {
		printf("û�е���\n");
	}
	return 0;
}