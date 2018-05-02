#include "stdafx.h"
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	//�����Ͳ۶���
	HANDLE hMailslot = CreateMailslot(
		L"\\\\.\\mailslot\\Sample", //�Ͳ���
		0,							//��������Ϣ��С
		MAILSLOT_WAIT_FOREVER,		//�޳�ʱ
		NULL						//��ȫ����
	);
	if (hMailslot == INVALID_HANDLE_VALUE) {
		printf("�����Ͳ۾��ʧ��\n");
		return 0;
	}
	//ѭ����ȡ��Ϣ
	int nLoopTimes = 0;
	while(true) {
		//��ȡ�Ͳ���Ϣ����
		DWORD dwMsgCount = 0, dwMsgSize = 0;
		GetMailslotInfo(
			hMailslot,
			(LPDWORD)NULL,
			&dwMsgSize,
			&dwMsgCount,
			(LPDWORD)NULL
		);
		if (dwMsgSize == MAILSLOT_NO_MESSAGE) {
			printf("%d û����Ϣ\n", nLoopTimes);
			nLoopTimes++;
			Sleep(5000);
			continue;
		}
		else {
			printf("%d �յ�����Ϣ\n", nLoopTimes);
		}
		//ѭ����ȡȫ������Ϣ
		while (dwMsgCount) {
			PBYTE lpBuffer = new BYTE[dwMsgSize + 0x10];
			//��ȡ�Ͳ��е���Ϣ
			DWORD dwRet;
			ZeroMemory(lpBuffer, dwMsgSize);
			if (!ReadFile(hMailslot, lpBuffer, dwMsgSize, &dwRet, NULL)) {
				printf("ReadFile����ʧ��, ������: %d\n", GetLastError());
				delete[] lpBuffer;
				return 0;
			}
			//��ʾ��Ϣ
			printf("�Ͳ۵�����: %s\n", lpBuffer);
			//����ʣ�����Ϣ��
			GetMailslotInfo(hMailslot, (LPDWORD)NULL, &dwMsgSize, &dwMsgCount, nullptr);
			delete[]  lpBuffer;
		}
	}

	return 0;
}

int _tmains(int argc, _TCHAR* argv[])
{
	// 1. �����ʲ۶���
	HANDLE hSlot = CreateMailslot(
		L"\\\\.\\mailslot\\Sample",    // �ʲ���
		0,                             // ��������Ϣ��С 
		MAILSLOT_WAIT_FOREVER,         // �޳�ʱ 
		NULL);  // ��ȫ����
				// 2. ѭ����ȡ�ʲ���Ϣ
	while (true) {
		// 2.1 ��ȡ�ʲ���Ϣ����
		DWORD dwMsgCount = 0, dwMsgSize = 0;
		GetMailslotInfo(     /* ��ȡ�ʲ���Ϣ */
			hSlot,           // �ʲ۾�� 
			(LPDWORD)NULL,   // �������Ϣ����
			&dwMsgSize,      // ��һ����Ϣ�Ĵ�С
			&dwMsgCount,     // ��Ϣ������
			(LPDWORD)NULL);// ��ʱ��
		if (dwMsgSize == MAILSLOT_NO_MESSAGE) {
			Sleep(2000);
			continue;
		}
		// 2.2 ѭ����ȡȫ����Ϣ���п��ܲ�ֻһ����
		while (dwMsgCount)
		{
			PBYTE lpBuffer;
			lpBuffer = new BYTE[dwMsgSize + 0x10];
			// ��ȡ�ʲ��е���Ϣ
			DWORD dwRet;
			ZeroMemory(lpBuffer, dwMsgSize);
			if (!ReadFile(hSlot, lpBuffer, dwMsgSize, &dwRet, NULL))
			{
				printf("ReadFile����ִ��ʧ�ܣ������룺%d.\n", GetLastError());
				delete[] lpBuffer;
				return 0;
			}
			// ��ʾ��Ϣ
			printf("�ʲ۵�����: %s\n", lpBuffer);
			// ����ʣ�����Ϣ��
			GetMailslotInfo(hSlot, (LPDWORD)NULL, &dwMsgSize, &dwMsgCount, nullptr);
			delete[] lpBuffer;
		}
	}

	return 0;
}