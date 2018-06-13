#include "stdafx.h"
#include <Windows.h>
#include "UnDocumentApi.h"

bool IsDebug()
{
	//��ȡTEB
	TEB* pTeb = NtCurrentTeb();
	//��ȡpEB
	PEB* pPeb = pTeb->ProcessEnvironmentBlock;
	printf("NtGlobalFlag: %X\n", pPeb->NtGlobalFlag);
	//��ȡ�Ƿ����ڵ����ֶε�ֵ
	//���PEB��NtGlobalFlag�ֶ�, �类����, ���ֶε�ֵΪx70
	return pPeb->NtGlobalFlag == 0x70;
}

int _tmain(int argc, _TCHAR* argv[])
{
	bool bIsDebug = IsDebug();
	if (bIsDebug) {
		printf("���ڱ�����");

	}
	else {
		printf("û�б�����");
	}
	return 0;

}