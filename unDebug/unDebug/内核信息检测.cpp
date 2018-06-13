// 07 检测系统是否处于调试模式.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <winternl.h>
#pragma comment(lib,"ntdll.lib")
bool NQSI_SystemKernelDebuggerInformation() {


	struct _SYSTEM_KERNEL_DEBUGGER_INFORMATION {
		BOOLEAN DebuggerEanbled;
		BOOLEAN DebuggerNotPresent;
	}DebuggerInfo = { 0 };


	NtQuerySystemInformation((SYSTEM_INFORMATION_CLASS)0x23,       // 查询信息类型
		&DebuggerInfo, 			         // 输出查询信息
		sizeof(DebuggerInfo), 			         // 查询类型大小
		NULL 					         // 实际返回大小
	);

	return DebuggerInfo.DebuggerEanbled;
}

int _tmain(int argc, _TCHAR* argv[])
{
	bool bDebug = NQSI_SystemKernelDebuggerInformation();
	if (bDebug)
	{
		MessageBoxA(NULL, "正在被调试", "警告", 0);
	}
	else
	{
		MessageBoxA(NULL, "现在很安全", "恭喜", 0);
	}
	return 0;
}

