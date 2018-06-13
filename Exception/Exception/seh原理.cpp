#include "stdafx.h"
#include <Windows.h>



EXCEPTION_DISPOSITION NTAPI SehHandler(
	_Inout_ struct _EXCEPTION_RECORD * ExceptionRecord,
	_In_  PVOID EstablisherFrame,
	_Inout_ struct _CONTEXT * ContextRecord,
	_In_ PVOID DispatcherContext
)
{
	printf("sehHandler\n");
	return ExceptionContinueSearch;
}


int main()
{
	EXCEPTION_REGISTRATION_RECORD* pHead;
	EXCEPTION_REGISTRATION_RECORD  sehNode;
	sehNode.Handler = SehHandler;
	_asm {
		mov eax, fs:[0];
		mov pHead, eax;
	}
	sehNode.Next = pHead;
	sehNode.Handler = SehHandler;
	//安装新节点
	_asm {
		lea eax, sehNode;
		mov fs : [0], eax;
	}

	printf("Sethandler: %08X\n", SehHandler);
	*(int*)0 = 0;
	//遍历
	//取首地址
	_asm {
		lea eax, fs:[0];
		mov pHead, eax;
	}
	while (pHead->Next != (EXCEPTION_REGISTRATION_RECORD*)-1) {
		printf("SEH异常处理函数: %08X\n", pHead->Handler);
		pHead = pHead->Next;

	}

	// 卸载
	_asm {
		mov eax, fs:[0];
		mov eax, [eax];
		mov fs : [0], eax;
	}

}
