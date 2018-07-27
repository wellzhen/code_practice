#pragma once
#include <Windows.h>


typedef struct __StubConf
{
	DWORD dwOEP; //原始的OEP
	DWORD dwEncryptRVA; //加密的开始地址
	DWORD dwCnctyptSize; //加密大小
	char szKey[16]; //加密密钥
	IMAGE_DATA_DIRECTORY  dataDir[16];
	DWORD dwTlsCallBackValue[16];//保存tls的回调函数表
} StubConf;