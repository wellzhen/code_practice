#include "stdafx.h"
#include <Windows.h>

int SetHandler(EXCEPTION_POINTERS* pException);

char * g_char = nullptr;
int  main()
{
	__try {
		printf("try block\n");
		*g_char = 'a';
	}
	__except(SetHandler(GetExceptionInformation())) {
		printf("except block\n");
	}

	printf("main end");
	return 0;
}
int SetHandler(EXCEPTION_POINTERS* pException)
{
	DWORD code = pException->ExceptionRecord->ExceptionCode;
	PVOID addr = pException->ExceptionRecord->ExceptionAddress;
	printf("异常代码: %08X, 异常地址: %08X\n", code, addr);
	//寄存器信息
	printf("EAX: %08X, ECS: %08X\n", pException->ContextRecord->Eax, pException->ContextRecord->Ecx);

	if (code == EXCEPTION_ACCESS_VIOLATION) {
		g_char = new char;
		pException->ContextRecord->Eax = (DWORD)g_char;
		return EXCEPTION_CONTINUE_EXECUTION;
	}

	return EXCEPTION_EXECUTE_HANDLER;
}