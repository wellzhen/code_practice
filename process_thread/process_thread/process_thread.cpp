// process_thread.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	STARTUPINFO  si = { 0 }; //新进程窗口的特性
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

