// 网络编程.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#pragma  comment(lib, "ws2_32.lib")



int _tmain(int argc, _TCHAR* argv[])
{
	printf("server starting...\n");
	// 1. 初始化Winsock库
	WSADATA  wd = {};
	WSAStartup(MAKEWORD(2, 2), &wd);
	// 2. 建立一个接收连接的socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//3. 绑定IP和端口到这个socket -- 注意IP和字节序
	sockaddr_in  si = {};
	si.sin_family = AF_INET;
	si.sin_port = htons(1234);
	si.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	bind(sock, (sockaddr*)&si, sizeof(si));

	//4. 监听 (能够限制同时最大的连接数
	listen(sock, 16);
	
	while (true) {
		//5. 循环接收客户端连接, 得到一个通讯socket
		sockaddr_in ClientSi = {};
		int addrSize = sizeof(sockaddr_in);
		SOCKET ClientSock = accept(sock, (sockaddr*)&ClientSi, &addrSize);
		//6.  接收 发送数据
		char * buf = "连接成功";
		send(ClientSock, buf, strlen(buf), 0);
		//7. 关闭socket
		closesocket(ClientSock);
	}
	

    return 0;
}

