#pragma once
#include <Windows.h>


typedef struct __StubConf
{
	DWORD dwOEP; //ԭʼ��OEP
	DWORD dwEncryptRVA; //���ܵĿ�ʼ��ַ
	DWORD dwCnctyptSize; //���ܴ�С
	char szKey[16]; //������Կ
	IMAGE_DATA_DIRECTORY  dataDir[16];
} StubConf;