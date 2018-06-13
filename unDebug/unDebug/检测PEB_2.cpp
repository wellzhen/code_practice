#include "stdafx.h"
#include <Windows.h>
#include "UnDocumentApi.h"

bool IsDebug()
{
	//获取TEB
	TEB* pTeb = NtCurrentTeb();
	//获取pEB
	PEB* pPeb = pTeb->ProcessEnvironmentBlock;
	printf("NtGlobalFlag: %X\n", pPeb->NtGlobalFlag);
	//获取是否正在调试字段的值
	//检测PEB的NtGlobalFlag字段, 如被调试, 此字段的值为x70
	return pPeb->NtGlobalFlag == 0x70;
}

int _tmain(int argc, _TCHAR* argv[])
{
	bool bIsDebug = IsDebug();
	if (bIsDebug) {
		printf("正在被调试");

	}
	else {
		printf("没有被调试");
	}
	return 0;

}