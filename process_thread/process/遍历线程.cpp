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
		printf("�޷���������\n");
		return 0;
	}
	if (!Thread32First(hThreadSnap, &te32)) {
		printf("�޷���ȡ�����߳�\n");
		CloseHandle(hThreadSnap);
		return 0;
	}

	do {
		printf(" %d �߳�ID: %d;���ڽ���ID: %d;  ���ȼ�: %d\n", nIndex, te32.th32OwnerProcessID, te32.th32ThreadID, te32.tpBasePri);
		nIndex++;
		//�̻߳���
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