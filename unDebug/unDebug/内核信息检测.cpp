// 07 ���ϵͳ�Ƿ��ڵ���ģʽ.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include <winternl.h>
#pragma comment(lib,"ntdll.lib")
bool NQSI_SystemKernelDebuggerInformation() {


	struct _SYSTEM_KERNEL_DEBUGGER_INFORMATION {
		BOOLEAN DebuggerEanbled;
		BOOLEAN DebuggerNotPresent;
	}DebuggerInfo = { 0 };


	NtQuerySystemInformation((SYSTEM_INFORMATION_CLASS)0x23,       // ��ѯ��Ϣ����
		&DebuggerInfo, 			         // �����ѯ��Ϣ
		sizeof(DebuggerInfo), 			         // ��ѯ���ʹ�С
		NULL 					         // ʵ�ʷ��ش�С
	);

	return DebuggerInfo.DebuggerEanbled;
}

int _tmain(int argc, _TCHAR* argv[])
{
	bool bDebug = NQSI_SystemKernelDebuggerInformation();
	if (bDebug)
	{
		MessageBoxA(NULL, "���ڱ�����", "����", 0);
	}
	else
	{
		MessageBoxA(NULL, "���ںܰ�ȫ", "��ϲ", 0);
	}
	return 0;
}

