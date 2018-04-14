#include "stdafx.h"
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[])
{
	//init WSA
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0) {
		printf("WASStartup error\n");
		return 0;
	}
	//create socket
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET) {
		printf("invalid socket\n");
		return 0;
	}
	//bind ip and port
	sockaddr_in   sin;
	sin.sin_family = AF_INET; // tpc/ip
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR) {
		printf("bind error\n");
		return 0;
	}
	//begin to listen
	if (listen(slisten, 5) == SOCKET_ERROR) {
		printf("listen  error !\n");
		return 0;
	}
	//loop to receive data
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrLen = sizeof(remoteAddr);
	char revData[255];
	while (true) {
		printf("waiting to connet!\n");
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrLen);
		if (sClient = INVALID_SOCKET) {
			printf("accetp error \n");
			continue;
		}
		//error C4996: 'inet_ntoa': Use inet_ntop() or InetNtop() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings
		//printf("receive a linek： %s\n", inet_ntoa(remoteAddr.sin_addr)); // 这是Linux下专用函数。Windows下用inet_addr		
		printf("receive a link： %s\n", remoteAddr.sin_addr); 
		//receive data
		int ret = recv(sClient, revData, 255, 0);
		if (ret > 0) {
			revData[ret] = 0x00;
			printf(revData);
		}
		//send data
		const char* sendData = "welcome, client\n";
		send(sClient, sendData, strlen(sendData), 0);
		closesocket(sClient);
	}

	closesocket(slisten);
	WSACleanup();
	
	return 0;

}