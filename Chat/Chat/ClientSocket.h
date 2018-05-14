#pragma once
#include "Data.h"
#include <vector>
using std::vector;
#define BUFNAME 50

class CClientSocket
{
public:
	CClientSocket();
	~CClientSocket();
	//初始化客户端套接字, 并尝试连接服务器
	bool ConnectServer(char* szIp, WORD port);
	//负责创建线程用来接收服务器信息
	char* Recv();
	bool Send(CHATPURPOSE purpose, char* bufSend, DWORD dwLen);
	bool Close();

private:
	// recv function
	char* RecvForAnonymous();
	char* RecvForChat();
	char* RecvForUpdateUserlist();
	char* RecvForOne2One();
	char* RecvForRegister();
	char* RecvForLogin();
	char* RecvForAddFriend();
	char* RecvForSearchUser();
	char* RecvForGetMsgRecord();
	
	// send Function
	void SendForAnonymous(char* bufSend, DWORD dwLen);
	void SendForChat(char* bufSend, DWORD dwLen);
	void SendForOne2One(char* bufSend, DWORD dwLen);
	void SendForRegister(char* bufSend, DWORD dwLen);
	void SendForLogin(char* bufSend, DWORD dwLen);
	void SendForAddFriend(char* bufSend, DWORD dwLen);
	void SendForSearchUser(char* bufSend, DWORD dwLen);
	void SendForGetMsgRecord(char* bufSend, DWORD dwLen);

public:
	//保存聊天记录
	HANDLE m_hEvent = 0;
	vector<CHATMSGRECORD> m_vecMsgRecord;
	//客户端套接字
	SOCKET m_sClient = NULL;
	//新用户加入或退出聊天室的时候用到
	CHATUPDATEUSER* m_pObjUpdate = nullptr;
	// 1v1聊天
	CHATONE2ONE* m_pObjOne2One = nullptr;
	//当前客户端的用户名
	char m_szName[BUFNAME] = {};
	//收信息的时候用
	CHATSEND* m_pObjChatRecv;

private:

	char m_bufRecv[BUFMSG] = {};


};

