#include "stdafx.h"
#include <Windows.h>
#include <ShlObj.h>

int _tmain(int argc, _TCHAR* argv[])
{
	//��ȡ����������
	HANDLE hToken = NULL;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
		printf("������:%x\n", GetLastError());
		return 0;
	}
	//���ڽ�����������
	TOKEN_ELEVATION_TYPE tokenType = TokenElevationTypeDefault;
	DWORD dwRetSize = 0; // ���ڽ��պ��������Ϣ���ֽ���
	//��ȡ������Ϣ
	GetTokenInformation(hToken, TokenElevationType, &tokenType, sizeof(tokenType), &dwRetSize);
	//�жϵ����Ƿ�ɹ�
	if (ERROR_SUCCESS != GetLastError()) {
		printf("������: %x\n", GetLastError());
		return 0;
	}

	//�������Ƶ������������Ӧ����Ϣ
	switch (tokenType) {
	case TokenElevationTypeDefault:
		printf("Ĭ���û�: TokenElevationTypeDefault\n");
		return  IsUserAnAdmin();
		break;
	case TokenElevationTypeFull:
		printf("����Ա�˻�, ����Ȩ��\n");
		break;
	case TokenElevationTypeLimited:
		//�ж������Ƶ��û��ǹ���Ա
		//����ǹ���Ա, ����������лᱣ���й���Ա��SID

		//1. ��ȡϵͳ�ڼ�����Ա�û���SID
		byte adminSID[SECURITY_MAX_SID_SIZE];
		DWORD dwSize = SECURITY_MAX_SID_SIZE;
		CreateWellKnownSid(WinBuiltinAdministratorsSid,
			NULL,
			adminSID,
			&dwSize
		);
		//��ȡ�����Ƶ���������, �����Ƶ����ƶ�����һ�����ӵ�����,
		//�����Ƶ����ƶ��Ƕ�������������������
		TOKEN_LINKED_TOKEN linkToken;
		GetTokenInformation(hToken,
			TokenLinkedToken,
			&linkToken,
			sizeof(linkToken),
			&dwSize
		);
		//�����ӵ������в����Ƿ���й���Ա��SID
		BOOL  bIsMember = false;
		CheckTokenMembership(hToken, &adminSID, &bIsMember);
		if (bIsMember) {
			printf("Ȩ�ޱ��˸�����޹���Ա�˻�\n");
		}
		break;
	}
	system("pause");
	return 0;
}