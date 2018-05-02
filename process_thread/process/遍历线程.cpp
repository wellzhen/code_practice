#include "stdafx.h"
#include <Windows.h>
#include <TlHelp32.h>


int _tmain(int argc, _TCHAR* argv[])
{
	INT nIndex = 0;
	THREADENTRY32  te32 = {};
	te32.dwSize = sizeof(THREADENTRY32);
	HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnap == INVALID_HANDLE_VALUE) {
		printf("无法创建快照\n");
		return 0;
	}
	if (!Thread32First(hThreadSnap, &te32)) {
		printf("无法获取快照线程\n");
		CloseHandle(hThreadSnap);
		return 0;
	}

	do {
		printf(" %d 线程ID: %d;所在进程ID: %d;  优先级: %d\n", nIndex, te32.th32OwnerProcessID, te32.th32ThreadID, te32.tpBasePri);
		nIndex++;
		//线程环境
		if (te32.th32OwnerProcessID == 8688) {
			HANDLE hThreadSearch = OpenThread(THREAD_ALL_ACCESS, false, te32.th32ThreadID);
			SuspendThread(hThreadSearch);
			CONTEXT stcCXT = { CONTEXT_FULL };
			GetThreadContext(hThreadSearch, &stcCXT);
			int a = 1;
		}
	} while (Thread32Next(hThreadSnap, &te32));
	
	return 0;
}