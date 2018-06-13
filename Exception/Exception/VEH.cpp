#include "stdafx.h"
#include <Windows.h>

LONG CALLBACK VectoredHandler(
	_In_ PEXCEPTION_POINTERS ExceptionInfo
);

LONG CALLBACK VectoredContinueHandler(
	_In_ PEXCEPTION_POINTERS ExceptionInfo
);
int main()
{
	AddVectoredExceptionHandler(TRUE, VectoredHandler);
	AddVectoredContinueHandler(TRUE, VectoredContinueHandler);
	int *p = nullptr;
	*p = 1;
	printf("main end");

	return 0;
}


LONG CALLBACK VectoredHandler(
	_In_ PEXCEPTION_POINTERS ExceptionInfo
) {
	printf("vector Handler\n");
	return EXCEPTION_CONTINUE_SEARCH;
	//return EXCEPTION_CONTINUE_EXECUTION;
}

LONG CALLBACK VectoredContinueHandler(
	_In_ PEXCEPTION_POINTERS ExceptionInfo
) {
	printf("vch\n");
	return EXCEPTION_CONTINUE_EXECUTION;
}
