#include "stdafx.h"
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	//API内部实际是监测beingDebugged字段
	bool bIsDebug = IsDebuggerPresent();
	if (bIsDebug) {
		printf("正在被调试\n");
		return 1;
	}
	else {
		printf("没有被调试\n");
		return  2;
	}

	

	return 1;
}