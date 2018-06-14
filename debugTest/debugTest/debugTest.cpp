// debugTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>

#define DBGPRINT(error) printf("%s %s %d : %s", __FILE__, __FUNCTION__, __LINE__, error);
#define DBGPRINT_EXIT(error) printf("%s %s %d : %s", __FILE__, __FUNCTION__, __LINE__, error); exit(0);



int main()
{
	//1. 创建调试会话
	char path[MAX_PATH];
	printf("请输入路径>");
	gets_s(path, MAX_PATH);
	STARTUPINFOA si = { sizeof(STARTUPINFOA) };
	PROCESS_INFORMATION pi = { 0 };
	BOOL bRet = CreateProcessA(path, 0, 0, 0, 0, DEBUG_ONLY_THIS_PROCESS, 0, 0, &si, &pi);
	if (bRet == FALSE) {
		DBGPRINT_EXIT("打开进程失败");
	}

	//2. 等待调试事件
	DEBUG_EVENT dbgEvent = { 0 };
	while (true) {
		WaitForDebugEvent(&dbgEvent, -1);
		switch (dbgEvent.dwDebugEventCode) {
		case EXCEPTION_DEBUG_EVENT:
				printf("异常调试事件\n");
				break;
		case CREATE_THREAD_DEBUG_EVENT:
			printf("线程创建事件\n");
			break;
		case CREATE_PROCESS_DEBUG_EVENT:
			printf("进程创建事件\n");
			break;
		case EXIT_THREAD_DEBUG_EVENT:
			printf("退出线程事件\n");
			break;
		case EXIT_PROCESS_DEBUG_EVENT:
			printf("退出进程事件\n");
			break;
		case LOAD_DLL_DEBUG_EVENT:
			printf("映射DLL事件\n");
			break;
		case UNLOAD_DLL_DEBUG_EVENT:
			printf("卸载DLL事件\n");
			break;
		case OUTPUT_DEBUG_STRING_EVENT:
			printf("调试字符串输出事件\n");
			break;
		case RIP_EVENT:
			printf("RIP事件, 内部错误\n");
			break;
		}
		//4. 回复调试子系统
		ContinueDebugEvent(dbgEvent.dwProcessId, dbgEvent.dwThreadId, DBG_CONTINUE);
	}

    return 0;
}

