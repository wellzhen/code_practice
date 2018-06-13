#include "stdafx.h"
#include <Windows.h>
#include <winternl.h>

#pragma comment(lib, "ntdll.lib")

bool NQIP_ProcessDebugPort()
{
	HANDLE nDebugPort = 0;
	NtQueryInformationProcess(
		GetCurrentProcess(),
		ProcessDebugPort,
		&nDebugPort,
		sizeof(nDebugPort),
		NULL
	);
	return nDebugPort == INVALID_HANDLE_VALUE ? true : false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	bool bIsDebug = NQIP_ProcessDebugPort();
	if (bIsDebug) {
		printf("���ڱ�����\n");

	}
	else {
		printf("û��û����\n");
	}
	return 0;
}