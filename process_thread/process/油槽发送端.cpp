#include "stdafx.h"
#include <Windows.h>


int _tmain(int argc, _TCHAR* argv[])
{
	//打开油槽对象
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
		printf("创建文件句柄失败:\n");
		return 0;
	}
	//向油槽写入数据
	DWORD  dwWritten;
	LPSTR lpMessage = "油槽测试消息";
	DWORD dwMsgLen = strlen(lpMessage) + sizeof(CHAR);
	if (!WriteFile(hFile, lpMessage, dwMsgLen, &dwWritten, NULL)) {
		printf("写入失败:\n");
		CloseHandle(hFile);
		return 0;
	}
	//结束
	printf("已发送\n");
	CloseHandle(hFile);
	return 0;
}

//int _tmain(int argc, _TCHAR* argv[])
//{
//	// 1. 打开邮槽对象
//	HANDLE hFile = CreateFile(
//		L"\\\\.\\mailslot\\Sample", // 邮槽名称
//		GENERIC_WRITE,              // 读写属性
//		FILE_SHARE_READ,            // 共享属性
//		NULL,                       // 安全属性
//		OPEN_EXISTING,      // 打开方式
//		FILE_ATTRIBUTE_NORMAL,      // 标志位
//		NULL);                     // 文件模板（默认留空）
//								   // 2. 向mailslot写入
//	DWORD  dwWritten;
//	LPSTR  lpMessage = "邮槽测试消息！";
//	DWORD  dwMegLen = strlen(lpMessage) + sizeof(CHAR);
//	WriteFile(hFile, lpMessage, dwMegLen, &dwWritten, NULL);
//	// 3. 结束
//	printf("已经向邮槽写入信息！\n");
//	CloseHandle(hFile);
//
//	return 0;
//}
