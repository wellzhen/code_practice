#include "stdafx.h"
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#include "ClientSocket.h"



CClientSocket::CClientSocket()
{
}


CClientSocket::~CClientSocket()
{
}

//初始化客户端套接字, 并尝试连接服务器
bool CClientSocket::ConnectServer(char* szIp, WORD port)
{
	WSADATA wsd;
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {
		return false;
	}
	//检查返回的库版本是否是2.2
	if (LOBYTE(wsd.wVersion) != 2 || HIBYTE(wsd.wHighVersion) != 2) {
		return false;
	}
	//创建监听socket
	m_sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_sClient == INVALID_SOCKET) {
		WSACleanup();
		return false;
	}
	//设置服务器地址
	SOCKADDR_IN servAddr = {};
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons((short)port);
	//连接服务器
	int nRetValue = connect(m_sClient, (sockaddr*)&servAddr, sizeof(SOCKADDR_IN));
	if (nRetValue == SOCKET_ERROR) {
		closesocket(m_sClient);
		m_sClient = NULL;
		WSACleanup();
		return false;
	}
	return true;
}

//负责创建线程用来接收服务器信息
char* CClientSocket::Recv()
{
	CHATSEND ct = {};
	if (SOCKET_ERROR == recv(m_sClient, (char*)&ct, sizeof(CHATSEND), NULL)) {
		printf("recv error !\n");
		return nullptr;
	}
	m_pObjChatRecv = &ct;
	switch (ct.m_type) {
	case ANONYMOUS:
		return RecvForAnonymous();
		break;
	case CHAT:
		return RecvForChat();
		break;
	case ONE2ONE:
		return RecvForOne2One();
		break;
	case REGISTER:
		return RecvForRegister();
		break;
	case LOGIN:
		return RecvForLogin();
		break;
	case ADDFRIEND:
		return RecvForAddFriend();
		break;
	case SEARCHUSER:
		return RecvForSearchUser();
		break;
	case FILETRANS:
		//
		break;
	case MSGRECORD:
		return RecvForGetMsgRecord();
		break;
	case UPDATEUSER:
		return RecvForUpdateUserlist();
		break;
	}
	return nullptr;
}

bool CClientSocket::Send(CHATPURPOSE purpose, char* bufSend, DWORD dwLen) 
{
	switch (purpose) {
	case ANONYMOUS:
		SendForAnonymous(bufSend, dwLen);
		break;
	case CHAT:
		SendForChat(bufSend, dwLen);
		break;
	case ONE2ONE:
		SendForOne2One(bufSend, dwLen);
		break;
	case REGISTER:
		SendForRegister(bufSend, dwLen);
		break;
	case LOGIN:
		SendForLogin(bufSend, dwLen);
		break;
	case ADDFRIEND:
		SendForAddFriend(bufSend, dwLen);
		break;
	case SEARCHUSER:
		SendForSearchUser(bufSend, dwLen);
		break;
	case FILETRANS:
		//
		break;
	case MSGRECORD:
		SendForGetMsgRecord(bufSend, dwLen);
		break;
	default:
		break;
	}
	return true;
}

bool CClientSocket::Close()
{
	WSACleanup();
	closesocket(m_sClient);
	return true;
}

// recv function
char* CClientSocket::RecvForAnonymous()
{
	return NULL;
}
char* CClientSocket::RecvForChat()
{
	return NULL;
}
char* CClientSocket::RecvForUpdateUserlist()
{
	return NULL;
}
char* CClientSocket::RecvForOne2One()
{
	return NULL;
}
char* CClientSocket::RecvForRegister()
{	
	return NULL;
}
char* CClientSocket::RecvForLogin()
{
	return NULL;
}
char* CClientSocket::RecvForAddFriend()
{
	return NULL;
}
char* CClientSocket::RecvForSearchUser()
{
	return NULL;
}
char* CClientSocket::RecvForGetMsgRecord()
{
	return NULL;
}
	
// send Function
void CClientSocket::SendForAnonymous(char* bufSend, DWORD dwLen)
{
	CHATSEND ct = { ANONYMOUS };
	//匿名 长度+ 昵称
	strcpy_s(ct.m_content.chat.buf, bufSend);
	ct.m_content.chat.dwLen = dwLen;
	send(m_sClient, (char*)&ct, sizeof(ct), NULL);
}
void CClientSocket::SendForChat(char* bufSend, DWORD dwLen)
{

}
void CClientSocket::SendForOne2One(char* bufSend, DWORD dwLen)
{

}
void CClientSocket::SendForRegister(char* bufSend, DWORD dwLen)
{

}
void CClientSocket::SendForLogin(char* bufSend, DWORD dwLen)
{

}
void CClientSocket::SendForAddFriend(char* bufSend, DWORD dwLen)
{
}
void CClientSocket::SendForSearchUser(char* bufSend, DWORD dwLen)
{
}
void CClientSocket::SendForGetMsgRecord(char* bufSend, DWORD dwLen)
{
}
