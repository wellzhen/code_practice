#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <Windows.h>


#pragma comment(lib, "ws2_32.lib")



int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA  wd = {};
	char buf[100] = {};
	//��ʼ��WinSock
	int nInitRes = WSAStartup(MAKEWORD(2, 2), &wd);
	//��������socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // ������������socket
	//����
	sockaddr_in si = {};
	si.sin_family = AF_INET;
	si.sin_port = htons(1234);
	si.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	connect(sock, (sockaddr*)&si, sizeof(si));
	recv(sock, buf, 100, 0);
	printf("%s\n", buf);
	system("pause");
	return 0;
}