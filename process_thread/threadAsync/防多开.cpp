#include "stdafx.h"
#include <Windows.h>


HANDLE hEvent;
int i = 0;

int _tmain(int argc, _TCHAR* argv[])
{
	
	HANDLE hOldEvent;
	hOldEvent = OpenEvent(EVENT_ALL_ACCESS, NULL, L"events"); //必须要设置参数1  !!?
	if (hOldEvent != 0) {
		printf("进程已经存在\n");
		Sleep(3000);
		return 0;
	}
	else {
		hEvent = CreateEvent(NULL, false, true, L"events");
	}
	
	while (true)
	{
		printf("%d 运行中...", i);
		i++;
		Sleep(10000);
	}
	return 0;
}