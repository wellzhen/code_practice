// debugTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>

#define DBGPRINT(error) printf("%s %s %d : %s", __FILE__, __FUNCTION__, __LINE__, error);
#define DBGPRINT_EXIT(error) printf("%s %s %d : %s", __FILE__, __FUNCTION__, __LINE__, error); exit(0);



int main()
{
	//1. �������ԻỰ
	char path[MAX_PATH];
	printf("������·��>");
	gets_s(path, MAX_PATH);
	STARTUPINFOA si = { sizeof(STARTUPINFOA) };
	PROCESS_INFORMATION pi = { 0 };
	BOOL bRet = CreateProcessA(path, 0, 0, 0, 0, DEBUG_ONLY_THIS_PROCESS, 0, 0, &si, &pi);
	if (bRet == FALSE) {
		DBGPRINT_EXIT("�򿪽���ʧ��");
	}

	//2. �ȴ������¼�
	DEBUG_EVENT dbgEvent = { 0 };
	while (true) {
		WaitForDebugEvent(&dbgEvent, -1);
		switch (dbgEvent.dwDebugEventCode) {
		case EXCEPTION_DEBUG_EVENT:
				printf("�쳣�����¼�\n");
				break;
		case CREATE_THREAD_DEBUG_EVENT:
			printf("�̴߳����¼�\n");
			break;
		case CREATE_PROCESS_DEBUG_EVENT:
			printf("���̴����¼�\n");
			break;
		case EXIT_THREAD_DEBUG_EVENT:
			printf("�˳��߳��¼�\n");
			break;
		case EXIT_PROCESS_DEBUG_EVENT:
			printf("�˳������¼�\n");
			break;
		case LOAD_DLL_DEBUG_EVENT:
			printf("ӳ��DLL�¼�\n");
			break;
		case UNLOAD_DLL_DEBUG_EVENT:
			printf("ж��DLL�¼�\n");
			break;
		case OUTPUT_DEBUG_STRING_EVENT:
			printf("�����ַ�������¼�\n");
			break;
		case RIP_EVENT:
			printf("RIP�¼�, �ڲ�����\n");
			break;
		}
		//4. �ظ�������ϵͳ
		ContinueDebugEvent(dbgEvent.dwProcessId, dbgEvent.dwThreadId, DBG_CONTINUE);
	}

    return 0;
}

