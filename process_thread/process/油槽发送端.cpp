#include "stdafx.h"
#include <Windows.h>


int _tmain(int argc, _TCHAR* argv[])
{
	//���Ͳ۶���
	HANDLE hFile = CreateFile(
		L"\\\\.\\mailslot\\Sample",
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE) {
		printf("�����ļ����ʧ��:\n");
		return 0;
	}
	//���Ͳ�д������
	DWORD  dwWritten;
	LPSTR lpMessage = "�Ͳ۲�����Ϣ";
	DWORD dwMsgLen = strlen(lpMessage) + sizeof(CHAR);
	if (!WriteFile(hFile, lpMessage, dwMsgLen, &dwWritten, NULL)) {
		printf("д��ʧ��:\n");
		CloseHandle(hFile);
		return 0;
	}
	//����
	printf("�ѷ���\n");
	CloseHandle(hFile);
	return 0;
}

//int _tmain(int argc, _TCHAR* argv[])
//{
//	// 1. ���ʲ۶���
//	HANDLE hFile = CreateFile(
//		L"\\\\.\\mailslot\\Sample", // �ʲ�����
//		GENERIC_WRITE,              // ��д����
//		FILE_SHARE_READ,            // ��������
//		NULL,                       // ��ȫ����
//		OPEN_EXISTING,      // �򿪷�ʽ
//		FILE_ATTRIBUTE_NORMAL,      // ��־λ
//		NULL);                     // �ļ�ģ�壨Ĭ�����գ�
//								   // 2. ��mailslotд��
//	DWORD  dwWritten;
//	LPSTR  lpMessage = "�ʲ۲�����Ϣ��";
//	DWORD  dwMegLen = strlen(lpMessage) + sizeof(CHAR);
//	WriteFile(hFile, lpMessage, dwMegLen, &dwWritten, NULL);
//	// 3. ����
//	printf("�Ѿ����ʲ�д����Ϣ��\n");
//	CloseHandle(hFile);
//
//	return 0;
//}
