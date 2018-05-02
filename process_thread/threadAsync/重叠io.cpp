#include "stdafx.h"
#include <Windows.h>

HANDLE  hFile;

struct MYOVERLAPPED
{
	OVERLAPPED ol;
	char* buf;
};
//回调函数
VOID WINAPI ReadProc(
	_In_  DWORD dwErrorCode,
	_In_  DWORD dwNumberOfBytesTransfered,
	_Inout_ LPOVERLAPPED lpOverlapped
)
{
	MYOVERLAPPED* pOl = (MYOVERLAPPED*)lpOverlapped;
	for (int i = 0; i < 100; i++) {
			printf("内容是:%d\n", pOl->buf[i*100]);
	}
	
}

//异步调用
int _tmain2(int argc, _TCHAR* argv[])
{
	DWORD dwRealSize = 0;
	hFile = CreateFile(
		L"Y:\\soft\\win10_x64\\Windows.iso",
		FILE_GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);

	char* buff = new char[1024 * 1024 * 1024];
	MYOVERLAPPED* pOl = new MYOVERLAPPED;
	ZeroMemory(pOl, sizeof(MYOVERLAPPED));
	pOl->buf = buff;
	ReadFileEx(hFile, buff, 1024 * 1024 * 1024, (LPOVERLAPPED)pOl, ReadProc);
	SleepEx(1, true);





	//OVERLAPPED ol = {};
	//ol.hEvent = CreateEvent(NULL, false, true, NULL);
	//printf("%d\n", buff[1024 * 1024 * 500]);
	//ReadFile(hFile, buff, 1024 * 1024 * 1024, &dwRealSize, &ol);
	//printf("%d\n", buff[1024 * 1024 * 500]);
	//WaitForSingleObject(ol.hEvent, -1);

	//printf("%d\n", buff[1024 * 1024 * 500]);

	return 0;
}




int _tmain_normal(int argc, _TCHAR* argv[])
{	
	DWORD dwRealSize = 0;
	hFile = CreateFile(
		L"Y:\\soft\\win10_x64\\Windows.iso",
		FILE_GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);

	char* buff = new char[1024 * 1024 * 1024];
	OVERLAPPED ol = {};
	ol.hEvent = CreateEvent(NULL, false, true, NULL);
	printf("%d\n", buff[1024 * 1024 * 500]);
	ReadFile(hFile, buff, 1024 * 1024 * 1024, &dwRealSize, &ol);
	printf("%d\n", buff[1024 * 1024 * 500]);
	WaitForSingleObject(ol.hEvent, -1);

	printf("%d\n", buff[1024 * 1024 * 500]);

	return 0;
}