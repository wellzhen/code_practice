#include "stdafx.h"
#include <Windows.h>

BOOL inject(char* szPath, DWORD pid);
int _tmain(int argc, _TCHAR* argv[])
{

	//获取进程的句柄
	char* szPath = "C:\\Users\\moonq\\Desktop\\msgHookDll.dll";
	DWORD pid = NULL;
	printf("请输入远程进程pid\n");
	scanf_s("%d", &pid);
	
	//注入
	inject(szPath, pid);
	return 1;
}

BOOL inject(char* szPath, DWORD pid)
{
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, pid); // 需求的权限?
	if (hProcess == NULL) {
		OutputDebugString(L"fail to open remote process");
		return false;
	}
	//在进程中开辟空间
	DWORD dwSize = strlen(szPath) + 1;
	LPVOID   lpBaseAddress  = VirtualAllocEx(hProcess, NULL,dwSize , MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (lpBaseAddress == NULL) {
		CloseHandle(hProcess);
		OutputDebugString(L"fail to VirtualAllocEx");
		return false;
	}
	//向进程写入
	BOOL bWriteRes = WriteProcessMemory(hProcess, lpBaseAddress, szPath, dwSize, NULL);
	if (bWriteRes == 0) {
		CloseHandle(hProcess);
		VirtualFreeEx(hProcess, lpBaseAddress, 0, MEM_RELEASE);
		OutputDebugString(L"fail to WriteProcessMemory");
		return false;
	}
	//创建远程线程
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryA, lpBaseAddress, 9, 0);
	if (hThread == NULL) {
		CloseHandle(hProcess);
		VirtualFreeEx(hProcess, lpBaseAddress, 0, MEM_RELEASE);
		OutputDebugString(L"fail to CreateRemoteThread");
		return false;
	}
	WaitForSingleObject(hThread, 0);
	//释放空间
	CloseHandle(hProcess);
	VirtualFreeEx(hProcess, lpBaseAddress, 0, MEM_RELEASE);
	OutputDebugString(L"inject over");
	return true;
}