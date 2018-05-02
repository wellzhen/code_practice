// process.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	STARTUPINFO si = {};
	PROCESS_INFORMATION pi = {};
	CreateProcess(
		TEXT("C:\\Program Files (x86)\\FastStoneCapturecn\\FSCapture.exe"),//exe文件路径
		NULL, //命令行参数
		NULL, //进程安全属性
		NULL, //线程的安全属性
		FALSE,//是否要继承父进程的句柄，对于本程序来说，就是是否继承VS2013的句柄
		NULL, //创建方式标志：1可以创建一个上来挂起的进程  2 可以创建一个被调试的进程
		NULL, //环境字符串块
		NULL, //程序运行目录，为NULL的话，就是exe所在的目录
		&si,
		&pi);
    return 0;
}

