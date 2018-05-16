#include "stdafx.h"
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#include "ClientSocket.h"



CClientSocket::CClientSocket()
{
	srand((int)time(NULL));
	char name[15];
	name[0] = 'a';
	name[1] = 'n';
	name[2] = 'o';
	name[3] = 'n';
	name[4] = 'y';
	name[5] = '_';
	for (int i = 6; i < 15; i++) {
		name[i] = rand() % 26 + 'a';
	}
	memcpy_s(m_szName, 15, name, 15);
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
	default:
		OutputDebugString(L"无效的信息类型");
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
	sprintf_s(m_bufRecv, BUFMSG, "%s 加入聊天室!\n", m_pObjChatRecv->m_content.any.buf);
	return m_bufRecv;
}

char* CClientSocket::RecvForChat()
{
	strcpy_s(m_bufRecv, m_pObjChatRecv->m_content.chat.buf);
	return m_bufRecv;
}
char* CClientSocket::RecvForUpdateUserlist()
{
	m_pObjUpdate = new CHATUPDATEUSER;
	memcpy_s(m_pObjUpdate, sizeof(CHATUPDATEUSER), &m_pObjChatRecv->m_content.upd, sizeof(CHATUPDATEUSER));
	return nullptr;
}
char* CClientSocket::RecvForOne2One()
{
	//新用户加入, 更新到用户列表窗口
	m_pObjOne2One = new CHATONE2ONE;
	memcpy_s(m_pObjOne2One, sizeof(CHATONE2ONE), &m_pObjChatRecv->m_content.o2o, sizeof(CHATONE2ONE));
	return NULL;
}
char* CClientSocket::RecvForRegister()
{	
	if (!strcmp(m_pObjChatRecv->m_content.login.szName, "注册成功!")) {
		return "注册成功";
	}
	return NULL;
}
char* CClientSocket::RecvForLogin()
{
	if (!strcmp(m_pObjChatRecv->m_content.login.szName, "登陆成功!")) {
		return "登陆成功";
	}
	else {
		return nullptr;
	}
}
char* CClientSocket::RecvForAddFriend()
{
	MessageBoxA(NULL,m_pObjChatRecv->m_content.adf.szName, "添加好友", MB_OK);
	return NULL;
}
char* CClientSocket::RecvForSearchUser()
{
	MessageBoxA(NULL, m_pObjChatRecv->m_content.seu.szName, "搜索用户", MB_OK);
	return nullptr;
}
char* CClientSocket::RecvForGetMsgRecord()
{
	if (!strcmp(m_pObjChatRecv->m_content.rec.szFrom, "---end---")) {
		SetEvent(m_hEvent);
	}
	else {
		m_vecMsgRecord.push_back(m_pObjChatRecv->m_content.rec);
	}
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
	CHATSEND ct = { CHAT };
	//聊天 长度+姓名 : 内容
	strcpy_s(ct.m_content.chat.buf, m_szName);
	strcat_s(ct.m_content.chat.buf, " : ");
	strcat_s(ct.m_content.chat.buf, bufSend);
	ct.m_content.chat.dwLen = strlen(ct.m_content.chat.buf) + 1;
	send(m_sClient, (char*)&ct, sizeof(ct), NULL);
}
void CClientSocket::SendForOne2One(char* bufSend, DWORD dwLen)
{
	CHATSEND ct = { ONE2ONE };
	// 姓名 : 内容
	char* nextToken = nullptr;
	char* szContext = strtok_s(bufSend, " : ", &nextToken);
	memcpy_s(ct.m_content.o2o.szName, nextToken - bufSend, bufSend, nextToken - bufSend);
	memcpy_s(ct.m_content.o2o.szContent, strlen(nextToken), nextToken, strlen(nextToken));
	send(m_sClient, (char*)&ct, sizeof(ct), NULL);

}
void CClientSocket::SendForRegister(char* bufSend, DWORD dwLen)
{
	CHATSEND ct = { REGISTER };
	char* pwd = nullptr;
	strtok_s(bufSend, ":", &pwd);
	memcpy_s(ct.m_content.reg.szName, pwd - bufSend, bufSend, pwd - bufSend);
	memcpy_s(ct.m_content.reg.szPwd, strlen(pwd), pwd, strlen(pwd));
	send(m_sClient, (char*)&ct, sizeof(ct), NULL);
}
void CClientSocket::SendForLogin(char* bufSend, DWORD dwLen)
{
	CHATSEND ct = { LOGIN };
	char* pwd = nullptr;
	strtok_s(bufSend, ":", &pwd);
	memcpy_s(ct.m_content.login.szName, pwd - bufSend, bufSend, pwd - bufSend);
	memcpy_s(ct.m_content.login.szPwd, strlen(pwd),pwd ,strlen(pwd));
	send(m_sClient, (char*)&ct, sizeof(ct), NULL);
}
void CClientSocket::SendForAddFriend(char* bufSend, DWORD dwLen)
{
	CHATSEND ct = { ADDFRIEND };
	char* frd = nullptr;
	//构造内容   当前用户:目标好友
	strtok_s(bufSend, ":", &frd);
	memcpy_s(ct.m_content.adf.szName, frd - bufSend, bufSend, frd - bufSend);
	memcpy_s(ct.m_content.adf.szFrd, strlen(frd), frd, strlen(frd));
	send(m_sClient, (char*)&ct, sizeof(ct), NULL);
}
void CClientSocket::SendForSearchUser(char* bufSend, DWORD dwLen)
{
	CHATSEND ct = { SEARCHUSER };
	memcpy_s(ct.m_content.seu.szName, dwLen, bufSend, dwLen);
	send(m_sClient, (char*)&ct, sizeof(ct), NULL);
}
void CClientSocket::SendForGetMsgRecord(char* bufSend, DWORD dwLen)
{
	CHATSEND ct = { MSGRECORD };
	send(m_sClient, (char*)&ct, sizeof(ct), NULL);
}
