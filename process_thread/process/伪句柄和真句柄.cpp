#include "stdafx.h"
#include <Windows.h>
#include <TlHelp32.h>

DWORD WINAPI ChildThread(PVOID pParam)
{
	HANDLE hThreadParent = (HANDLE)pParam;
	FILETIME stcCreationTime, stcExitTime;
	FILETIME stcKernelTime, stcUserTime;
	GetThreadTimes(hThreadParent, &stcCreationTime, &stcExitTime, &stcKernelTime, &stcUserTime);
	FILETIME LocalTime = {};
	SYSTEMTIME stcSysTime = {};
	FileTimeToLocalFileTime(&stcCreationTime, &LocalTime);
	FileTimeToSystemTime(&LocalTime, &stcSysTime);

	return 0;
}
int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hThreadParent = GetCurrentThread();
	FILETIME stcCreateTime = {}, stcExitTime = {};
	FILETIME stcKernelTime = {}, stcUserTime = {};
	SYSTEMTIME stcSysTime = {};
	//��ȡ�̵߳Ĵ���ʱ��
	GetThreadTimes(hThreadParent, &stcCreateTime, &stcExitTime, &stcKernelTime, &stcUserTime);
	FILETIME LocalTime = {};
	FileTimeToLocalFileTime(&stcCreateTime, &LocalTime);
	FileTimeToSystemTime(&LocalTime, &stcSysTime);
	//��α�����������
	DuplicateHandle(GetCurrentProcess(), GetCurrentThread, GetCurrentProcess(), &hThreadParent, 0, false, DUPLICATE_SAME_ACCESS);

	HANDLE hThread = CreateThread(NULL, 0,ChildThread , hThreadParent ,0, NULL);

	WaitForSingleObject(hThread, -1);
	CloseHandle(hThreadParent);

}