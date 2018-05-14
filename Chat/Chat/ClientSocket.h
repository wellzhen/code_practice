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
	//��ʼ���ͻ����׽���, ���������ӷ�����
	bool ConnectServer(char* szIp, WORD port);
	//���𴴽��߳��������շ�������Ϣ
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
	//���������¼
	HANDLE m_hEvent = 0;
	vector<CHATMSGRECORD> m_vecMsgRecord;
	//�ͻ����׽���
	SOCKET m_sClient = NULL;
	//���û�������˳������ҵ�ʱ���õ�
	CHATUPDATEUSER* m_pObjUpdate = nullptr;
	// 1v1����
	CHATONE2ONE* m_pObjOne2One = nullptr;
	//��ǰ�ͻ��˵��û���
	char m_szName[BUFNAME] = {};
	//����Ϣ��ʱ����
	CHATSEND* m_pObjChatRecv;

private:

	char m_bufRecv[BUFMSG] = {};


};

