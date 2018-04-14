#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

int main()
{

	for (int i = 0; i < 1024; i++) {
		Sleep(100);
		int *p = (int*)malloc(1 * 1024 * 1024);
		printf("%d  %pM\n", i * 1, p);
	}
		
	return 0;

}