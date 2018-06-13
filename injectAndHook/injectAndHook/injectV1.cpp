// injectAndHook.cpp : �������̨Ӧ�ó������ڵ㡣


#include "stdafx.h"
#include <Windows.h>
#include <TlHelp32.h>

//����Ȩ��
bool enableDebugPriv();
//����Ŀ��
DWORD FindTarget(LPCTSTR lpszProcess);
//Զ���߳�ע��
void InjectDll(char* szPath, DWORD dwPID);



int _tmain(int argc, _TCHAR* argv[])
{
	DWORD dwPID;
	OutputDebugString(L"begin _tmain");
	//printf("����pid:\n");
	//scanf_s("%d", &dwPID);
	enableDebugPriv();
	dwPID = FindTarget(L"TM.exe");
	//dwPID = FindTarget(L"TM.exe");
	if (dwPID == 0) {
		OutputDebugString(L" can not get pid");
		return 1;
	}

	InjectDll("C:\\Users\\moonq\\Desktop\\dll\\veh.dll", dwPID);

	return 1;
}
void InjectDll(char* szPath, DWORD dwPID)
{
	//��ȡָ�����̵ľ��
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, dwPID);
	if (hProcess == NULL) {
		OutputDebugString(L"fail to OpenProcess\n");
		return ;
	}
	//�ڽ���������һ���ڴ�
	DWORD dwSize = strlen(szPath) + 1;
	LPVOID lpBuffer = VirtualAllocEx(hProcess, NULL, dwSize,
		MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (lpBuffer == NULL) {
		CloseHandle(hProcess);
		OutputDebugString(L"fail to VirtualAllocEX");
		return;
	}
	// 3. ��dll·��д������ڴ�
	SIZE_T dwWrite;
	BOOL bRet = WriteProcessMemory(hProcess, lpBuffer, szPath, dwSize, &dwWrite);
	if (bRet == false) {
		CloseHandle(hProcess);
		VirtualFreeEx(hProcess, lpBuffer, 0, MEM_RELEASE);
		OutputDebugString(L"Fail to VirtualFreeEx\n");
		return;
	}

	//����Զ���߳�
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, lpBuffer, NULL, NULL);
	if (hThread == NULL) {
		CloseHandle(hProcess);
		VirtualFreeEx(hProcess, lpBuffer, 0, MEM_RELEASE);
		OutputDebugString(L"Fail to CreateRemoteThread\n");
		DWORD errNO = GetLastError();

		WCHAR errTip[5];

		wsprintfW(errTip, L"%d", errNO);
		OutputDebugString(errTip);


		

		
		return;
	}
	//�ȴ��߳�, �ͷſռ�
	WaitForSingleObject(hThread, -1);
	CloseHandle(hProcess);
	VirtualFreeEx(hProcess, lpBuffer, 0, MEM_RELEASE);
	OutputDebugString(L"Success to CreateRemoteThread");
	return;

}

// �������̷���Ȩ��
bool enableDebugPriv()
{
	HANDLE  hToken;
	LUID    sedebugnameValue;
	TOKEN_PRIVILEGES tkp;
	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)
		)
	{
		OutputDebugString(L"����Ȩ��ʧ��:OpenProcessToken(GetCurrentProcess() ");
		return false;
	}
	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sedebugnameValue))
	{
		OutputDebugString(L"����Ȩ��ʧ��:LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sedebugnameValue) ");
		CloseHandle(hToken);
		return false;
	}
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL))
	{
		OutputDebugString(L"����Ȩ��ʧ��:AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL ");
		CloseHandle(hToken);
		return false;
	}
	OutputDebugString(L"����Ȩ");
	return true;
}

DWORD FindTarget(LPCTSTR lpszProcess)
{
	DWORD dwRet = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	Process32First(hSnapshot, &pe32);
	do
	{
		if (lstrcmpi(pe32.szExeFile, lpszProcess) == 0)
		{
			dwRet = pe32.th32ProcessID;
			OutputDebugString(L"has found pid");
			break;
		}
	} while (Process32Next(hSnapshot, &pe32));
	CloseHandle(hSnapshot);
	return dwRet;
}