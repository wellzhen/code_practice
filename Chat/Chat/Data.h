#pragma once

//Э��
#define BUFMSG 2048 //һ���Խ��յ�����ֽ���

//ͷ��: ͨѶĿ��, ����������½, ����, 1v1, ע��, ��½, ���Ӻ���, ��������, �ļ�����, �鿴�����¼
enum CHATPURPOSE {
	ANONYMOUS = 1,
	CHAT,
	ONE2ONE,
	REGISTER,
	LOGIN,
	ADDFRIEND,
	SEARCHUSER,
	FILETRANS,
	MSGRECORD,
	UPDATEUSER
};

//��������
//�����Ľṹ��
typedef struct _CHATANONYMOUS {
	DWORD dwLen; //�������ݳ���
	char buf[1024];
} CHATANONYMOUS; 

//����Ľṹ��
typedef struct _CHATCHAT {
	DWORD dwLen;
	char buf[1024];
} CHATCHAT;

//1v1�ṹ��
typedef struct _CHATONE2ONE {
	CHAR szName[50];
	CHAR szContent[1024];
} CHATONE2ONE;

//ע��ṹ��
typedef struct _CHATREGISTER {
	CHAR szName[50];
	CHAR szPwd[50];
} CHATREGISTER;

//��½�ṹ��, ���������ؽ������szName��
typedef struct _CHATLOGIN {
	CHAR szName[50];
	CHAR szPwd[50];
} CHATLOGIN;

//���Ӻ��ѽṹ��
typedef struct _CHATADDFRIEND {
	CHAR szName[50];
	CHAR szFrd[50];
} CHATADDFRIEND;

// �����ṹ��
typedef struct _CHATSEARCHUSER {
	CHAR szName[50];
} CHATSEARCHUSER;

//�ļ�����ṹ��
typedef struct _CHATFILETRANS {

} CHATFILETRANS;

//�鿴�����¼�ṹ��
typedef struct _CHATMSGRECORD {
	CHAR szFrom[50];
	CHAR szTo[50];
	CHAR szConent[1024];
} CHATMSGRECORD;

//���������û��б�
typedef struct _CHATUPDATEUSER {
	DWORD bAdd;  // �Ǽ��뻹���˳�
	DWORD dwLen;  //һ��ֻ����һ���û���
	CHAR  buf[50];
} CHATUPDATEUSER;

//��������
typedef struct _CHATSEND {
	CHATPURPOSE  m_type;
	union {
		char buf[BUFMSG];
		CHATANONYMOUS any;
		CHATCHAT  chat; //����
		CHATONE2ONE  o2o;  //lv1
		CHATREGISTER  reg; // ע��
		CHATLOGIN    login; //��½
		CHATADDFRIEND  adf; //���Ӻ���
		CHATSEARCHUSER  seu; //��������
		CHATFILETRANS   trs; //�ļ�����
		CHATMSGRECORD rec; //�����¼
		CHATUPDATEUSER upd; //�����û��б�
	} m_content;
} CHATSEND;



















