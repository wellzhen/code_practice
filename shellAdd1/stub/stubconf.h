#pragma once
#include <Windows.h>


typedef struct __StubConf
{
	DWORD dwOEP; //ԭʼ��OEP
	DWORD dwKey; //������Կ
	DWORD dwEncryptRVA; //���ܵĿ�ʼ��ַ
	DWORD dwCnctyptSize; //���ܴ�С
	IMAGE_DATA_DIRECTORY  dataDir[16];
} StubConf;