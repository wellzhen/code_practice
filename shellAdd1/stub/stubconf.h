#pragma once
#include <Windows.h>


typedef struct __StubConf
{
	DWORD dwOEP; //原始的OEP
	DWORD dwKey; //加密密钥
	DWORD dwEncryptRVA; //加密的开始地址
	DWORD dwCnctyptSize; //加密大小
	IMAGE_DATA_DIRECTORY  dataDir[16];
} StubConf;