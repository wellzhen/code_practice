// ������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#pragma  comment(lib, "ws2_32.lib")



int _tmain(int argc, _TCHAR* argv[])
{
	printf("server starting...\n");
	// 1. ��ʼ��Winsock��
	WSADATA  wd = {};
	WSAStartup(MAKEWORD(2, 2), &wd);
	// 2. ����һ���������ӵ�socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//3. ��IP�Ͷ˿ڵ����socket -- ע��IP���ֽ���
	sockaddr_in  si = {};
	si.sin_family = AF_INET;
	si.sin_port = htons(1234);
	si.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	bind(sock, (sockaddr*)&si, sizeof(si));

	//4. ���� (�ܹ�����ͬʱ����������
	listen(sock, 16);
	
	while (true) {
		//5. ѭ�����տͻ�������, �õ�һ��ͨѶsocket
		sockaddr_in ClientSi = {};
		int addrSize = sizeof(sockaddr_in);
		SOCKET ClientSock = accept(sock, (sockaddr*)&ClientSi, &addrSize);
		//6.  ���� ��������
		char * buf = "���ӳɹ�";
		send(ClientSock, buf, strlen(buf), 0);
		//7. �ر�socket
		closesocket(ClientSock);
	}
	

    return 0;
}

