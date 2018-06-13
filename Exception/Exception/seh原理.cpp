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
	//��װ�½ڵ�
	_asm {
		lea eax, sehNode;
		mov fs : [0], eax;
	}

	printf("Sethandler: %08X\n", SehHandler);
	*(int*)0 = 0;
	//����
	//ȡ�׵�ַ
	_asm {
		lea eax, fs:[0];
		mov pHead, eax;
	}
	while (pHead->Next != (EXCEPTION_REGISTRATION_RECORD*)-1) {
		printf("SEH�쳣������: %08X\n", pHead->Handler);
		pHead = pHead->Next;

	}

	// ж��
	_asm {
		mov eax, fs:[0];
		mov eax, [eax];
		mov fs : [0], eax;
	}

}
