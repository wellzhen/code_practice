#include "stdafx.h"
#include <Windows.h>


HANDLE hEvent;
int i = 0;

int _tmain(int argc, _TCHAR* argv[])
{
	
	HANDLE hOldEvent;
	hOldEvent = OpenEvent(EVENT_ALL_ACCESS, NULL, L"events"); //����Ҫ���ò���1  !!?
	if (hOldEvent != 0) {
		printf("�����Ѿ�����\n");
		Sleep(3000);
		return 0;
	}
	else {
		hEvent = CreateEvent(NULL, false, true, L"events");
	}
	
	while (true)
	{
		printf("%d ������...", i);
		i++;
		Sleep(10000);
	}
	return 0;
}