//#include "stdafx.h"
//#include <Windows.h>
//
////Ĭ�ϵ�SEH   
////UEH
//
//
//LONG WINAPI UnhandledExceptionFilters(
//	_EXCEPTION_POINTERS *ExceptionInfo
//);
//
//int main()
//{
//	SetUnhandledExceptionFilter(UnhandledExceptionFilters);
//	int* p = nullptr;
//	*p = 0;
//	return 1;
//}
//LONG WINAPI UnhandledExceptionFilters(
//	_EXCEPTION_POINTERS *ExceptionInfo
//) {
//	printf("UEH\n");
//	return EXCEPTION_CONTINUE_SEARCH;
//}

// 04_Ĭ�ϵ�SEH.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>

LONG WINAPI defaultSehFilter(EXCEPTION_POINTERS* pException)
{
	printf("defaultSehFilter()\n");
	return EXCEPTION_CONTINUE_SEARCH;
}

int main()
{
	// ����Ĭ�ϵ�SEH�쳣���˺���
	SetUnhandledExceptionFilter(defaultSehFilter);

	*(int*)0 = 0;

	return 0;
}