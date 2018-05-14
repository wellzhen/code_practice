// netWork.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include  <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#define RECIVE 1
#define SEND 2
#define ACCEPT 3

typedef struct _MYOVERLAPPED {
	OVERLAPPED  ol;
	int nReason;
	WSABUF* wsaBuf;
} MYOVERLAPPED, *PMYOVERLAPPED;

void ThreadProc(LPVOID pParam) {
	HANDLE hComPort = (HANDLE)pParam;
	DWORD dwSize = 0;
	SOCKET Socket = NULL;
	PMYOVERLAPPED pOverlapped = NULL;
	while (TRUE) {
		//ѭ����������
		GetQueuedCompletionStatus(
			hComPort,
			&dwSize,
			(ULONG*)&Socket,
			(LPOVERLAPPED*)&pOverlapped,
			-1
		);
		switch (pOverlapped->nReason) {
		case RECIVE:
			printf(pOverlapped->wsaBuf->buf);
			break;
		case SEND:
			printf("send...");
			break;
		default:
			break;
		}
	}
}
int _tmain(int argc, _TCHAR argv[])
{
	// init socket lib
	WSADATA wd = {};
	WSAStartup(MAKEWORD(2, 3), &wd);
	//������ɶ˿�
	HANDLE hComPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	//���������߳�
	// ��ȡ��Ҫ��cpu����
	SYSTEM_INFO sysInfo = {};
	GetSystemInfo(&sysInfo);

	for (DWORD i = 0; i < sysInfo.dwNumberOfProcessors * 2; i++) {
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, (LPVOID)hComPort, 0, NULL);
	}
	//��������socket 
	SOCKET sSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);

	//��socket
	SOCKADDR_IN si = {};
	si.sin_family = AF_INET;
	si.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	si.sin_port = htons(1234);

	bind(sSocket, (SOCKADDR*)&si, sizeof(si));

	listen(sSocket, 8);

	//ѭ�����տͻ��˵�����
	while (TRUE) {
		SOCKADDR_IN clientSi = {};
		int addrSize = sizeof(SOCKADDR_IN);
		SOCKET cSocket = accept(sSocket, (SOCKADDR*)&clientSi, &addrSize);
		if (cSocket != SOCKET_ERROR) {
			//��cSocket�󶨵�comPort��
			CreateIoCompletionPort((HANDLE)cSocket, hComPort, 0, 0);
			//����������ݵ�����
			PMYOVERLAPPED pMyOverlapped = new MYOVERLAPPED;
			ZeroMemory(pMyOverlapped, sizeof(MYOVERLAPPED));
			WSABUF* wsaBuf = new WSABUF;
			DWORD dwRealCount = 0;
			DWORD dwlpFlags = 0;
			wsaBuf->buf = new char[2000];
			wsaBuf->len = 2000;
			pMyOverlapped->wsaBuf = wsaBuf;
			pMyOverlapped->nReason = RECIVE;
			//��ʼ����
			WSARecv(
				cSocket,
				wsaBuf,
				1, 
				&dwRealCount,
				&dwlpFlags,
				(LPWSAOVERLAPPED)pMyOverlapped,
				NULL
			);
		}
		
	}





    return 0;
}

