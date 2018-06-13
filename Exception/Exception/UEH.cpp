//#include "stdafx.h"
//#include <Windows.h>
//
////默认的SEH   
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

// 04_默认的SEH.cpp : 定义控制台应用程序的入口点。
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
	// 设置默认的SEH异常过滤函数
	SetUnhandledExceptionFilter(defaultSehFilter);

	*(int*)0 = 0;

	return 0;
}