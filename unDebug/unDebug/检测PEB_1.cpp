#include "stdafx.h"
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	//API�ڲ�ʵ���Ǽ��beingDebugged�ֶ�
	bool bIsDebug = IsDebuggerPresent();
	if (bIsDebug) {
		printf("���ڱ�����\n");
		return 1;
	}
	else {
		printf("û�б�����\n");
		return  2;
	}

	

	return 1;
}