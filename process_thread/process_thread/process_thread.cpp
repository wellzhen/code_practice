// process_thread.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	STARTUPINFO  si = { 0 }; //�½��̴��ڵ�����
	PROCESS_INFORMATION pi = { 0 }; 
	BOOL bRes = CreateProcess(
		TEXT("C:\\Program Files(x86)\\Tencent\QQ\Bin\\QQScLauncher.exe"),
		NULL,
		0,
		0,
		FALSE,
		0,
		0,
		0,
		&si,
		&pi
	);


    return 0;
}

