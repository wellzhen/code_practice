#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")

//客户端数据包结构体
struct ClientDataPack {
	int errNo;
	int msgType;


	

};
DWORD WINAPI RecvProc(LPVOID pParam)
{
	SOCKET sock = (SOCKET)pParam;
	char buf[1024] = {};
	while (TRUE) {
		ZeroMemory(buf, 1024);
		if (!recv(sock, buf, 1024, 0)) {
			break;
		}
		printf("other>> %s\n", buf);
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA  wd = {};
	//初始化WinSock
	int nInitRes = WSAStartup(MAKEWORD(2, 2), &wd);
	//创建连接socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // 变量名不能是socket
	//连接
	sockaddr_in serverSi = {};
	serverSi.sin_family = AF_INET;
	serverSi.sin_port = htons(1234);
	serverSi.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	connect(sock, (sockaddr*)&serverSi, sizeof(serverSi));
	
	CreateThread(NULL, 0, RecvProc, (LPVOID)sock, 0, 0);
	char buf[1024] = {};
	while (TRUE) {
		//ZeroMemory(buf, 1024);
		printf("you>>  \n");
		scanf_s("%s", buf, 1024);
		send(sock, buf, strlen(buf), 0);
	}


	return 0;
}