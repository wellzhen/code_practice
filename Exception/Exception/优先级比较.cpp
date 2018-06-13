#include "stdafx.h"
#include <Windows.h>


LONG WINAPI veh(EXCEPTION_POINTERS* p)
{
	printf("veh\n");
	return EXCEPTION_CONTINUE_SEARCH;
}

LONG WINAPI veh2(EXCEPTION_POINTERS* p)
{
	printf("veh2\n");
	return EXCEPTION_CONTINUE_SEARCH;
}
LONG WINAPI  vch(EXCEPTION_POINTERS* p)
{
	printf("vch\n");
	return EXCEPTION_CONTINUE_SEARCH;
}

LONG WINAPI  vch2(EXCEPTION_POINTERS* p)
{
	printf("vch2\n");
	return EXCEPTION_CONTINUE_SEARCH;
}

LONG WINAPI ueh(EXCEPTION_POINTERS* p)
{
	printf("UEH\n");
	//return EXCEPTION_CONTINUE_SEARCH;
	return EXCEPTION_EXECUTE_HANDLER;
}
LONG WINAPI ueh2(EXCEPTION_POINTERS* p)
{
	printf("UEH2\n");
	return EXCEPTION_CONTINUE_SEARCH;
	//return EXCEPTION_EXECUTE_HANDLER;
}
LONG WINAPI seh(EXCEPTION_POINTERS* p)
{
	printf("seh\n");
	//return EXCEPTION_CONTINUE_SEARCH;
	//return EXCEPTION_EXECUTE_HANDLER;
	return EXCEPTION_CONTINUE_EXECUTION;
}
LONG WINAPI seh2(EXCEPTION_POINTERS* p)
{
	printf("seh2\n");
	return EXCEPTION_CONTINUE_SEARCH;
	//return EXCEPTION_EXECUTE_HANDLER;
}

int main()
{
	AddVectoredExceptionHandler(true, veh);
	AddVectoredExceptionHandler(true, veh2);
	AddVectoredContinueHandler(true, vch);
	AddVectoredContinueHandler(true, vch2);
	SetUnhandledExceptionFilter(ueh);
	SetUnhandledExceptionFilter(ueh2);

	__try {
		int *p = nullptr;
		*p = 1;
	}
	__except (seh(GetExceptionInformation())) {

		printf("except\n");
			
	}
	printf("end main\n");

	return 1;
}