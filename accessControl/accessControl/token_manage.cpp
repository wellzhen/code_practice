#include "stdafx.h"
#include <Windows.h>
#include <ShlObj.h>

BOOL AddPrivilege(HANDLE hProcess, const TCHAR* pszPrivilegeName);

BOOL IsAdmin(HANDLE hProcess);

void RunAsAdmin(const TCHAR* pszExeFile);

int _tmain(int argc, _TCHAR* argv[])
{

	return 0;
}

BOOL AddPrivilege(HANDLE hProcess, const TCHAR* pszPrivilegeName)
{
	LUID privilegeLuid;
	if (!LookupPrivilegeValue(NULL, pszPrivilegeName, &privilegeLuid)) {
		return false;
	}
	//获取本进程令牌
	HANDLE hToken = NULL;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		printf("错误码: %x\n", GetLastError());
		return 0;
	}
	//2
	TOKEN_PRIVILEGES tokenPrivileges;
	tokenPrivileges.PrivilegeCount = 1;
	tokenPrivileges.Privileges[0].Luid = privilegeLuid;
	tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	return AdjustTokenPrivileges(hToken, false, &tokenPrivileges, sizeof(tokenPrivileges), NULL, NULL);


	return true;
}
