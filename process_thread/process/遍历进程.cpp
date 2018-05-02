#include "stdafx.h"
#include <Windows.h>
#include <TlHelp32.h>


int _tmain(int argc, _TCHAR* argv[])
{
	PROCESSENTRY32 pe = {};
	pe.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		printf("��Ч�ľ��ֵ");
		return 0;
	}

	if (!Process32First(hProcessSnap, &pe)) {
		printf("�޷���ȡ����\n");
		CloseHandle(hProcessSnap);
		return 0;
	}
	do {
		printf("������: %d, ����ID : %d,  ������: %S \n", pe.th32ParentProcessID, pe.th32ProcessID, pe.szExeFile);

	} while (Process32Next(hProcessSnap, &pe));


	return 0;
}