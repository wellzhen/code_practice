#include "stdafx.h"
#include <Windows.h>

BOOL inject(char* szPath, DWORD pid);
int _tmain(int argc, _TCHAR* argv[])
{

	//��ȡ���̵ľ��
	char* szPath = "C:\\Users\\moonq\\Desktop\\msgHookDll.dll";
	DWORD pid = NULL;
	printf("������Զ�̽���pid\n");
	scanf_s("%d", &pid);
	
	//ע��
	inject(szPath, pid);
	return 1;
}

BOOL inject(char* szPath, DWORD pid)
{
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, pid); // �����Ȩ��?
	if (hProcess == NULL) {
		OutputDebugString(L"fail to open remote process");
		return false;
	}
	//�ڽ����п��ٿռ�
	DWORD dwSize = strlen(szPath) + 1;
	LPVOID   lpBaseAddress  = VirtualAllocEx(hProcess, NULL,dwSize , MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (lpBaseAddress == NULL) {
		CloseHandle(hProcess);
		OutputDebugString(L"fail to VirtualAllocEx");
		return false;
	}
	//�����д��
	BOOL bWriteRes = WriteProcessMemory(hProcess, lpBaseAddress, szPath, dwSize, NULL);
	if (bWriteRes == 0) {
		CloseHandle(hProcess);
		VirtualFreeEx(hProcess, lpBaseAddress, 0, MEM_RELEASE);
		OutputDebugString(L"fail to WriteProcessMemory");
		return false;
	}
	//����Զ���߳�
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryA, lpBaseAddress, 9, 0);
	if (hThread == NULL) {
		CloseHandle(hProcess);
		VirtualFreeEx(hProcess, lpBaseAddress, 0, MEM_RELEASE);
		OutputDebugString(L"fail to CreateRemoteThread");
		return false;
	}
	WaitForSingleObject(hThread, 0);
	//�ͷſռ�
	CloseHandle(hProcess);
	VirtualFreeEx(hProcess, lpBaseAddress, 0, MEM_RELEASE);
	OutputDebugString(L"inject over");
	return true;
}