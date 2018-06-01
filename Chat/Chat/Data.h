#pragma once

//协议
#define BUFMSG 2048 //一次性接收的最大字节数
#define SERVERIP  "127.0.0.1"
#define SERVERPORT  1234

//自定义消息
#define WM_MYSOCKET (WM_USER + 100)

//头部: 通讯目的, 包括匿名登陆, 聊天, 1v1, 注册, 登陆, 添加好友, 搜索好友, 文件传输, 查看聊天记录
enum CHATPURPOSE {
	ANONYMOUS = 1,
	CHAT,//群聊
	ONE2ONE,
	REGISTER,
	LOGIN,
	ADDFRIEND,
	SEARCHUSER,
	FILETRANS,
	MSGRECORD,
	UPDATEUSER
};

//聊天内容
//匿名的结构体
typedef struct _CHATANONYMOUS {
	DWORD dwLen; //聊天内容长度
	char buf[1024];
} CHATANONYMOUS; 

//聊天的结构体
typedef struct _CHATCHAT {
	DWORD dwLen;
	char buf[1024];
} CHATCHAT;

//1v1结构体
typedef struct _CHATONE2ONE {
	CHAR szName[50];
	CHAR szContent[1024];
} CHATONE2ONE;

//注册结构体
typedef struct _CHATREGISTER {
	CHAR szName[50];
	CHAR szPwd[50];
} CHATREGISTER;

//登陆结构体, 服务器返回结果放在szName中
typedef struct _CHATLOGIN {
	CHAR szName[50];
	CHAR szPwd[50];
} CHATLOGIN;

//添加好友结构体
typedef struct _CHATADDFRIEND {
	CHAR szName[50];
	CHAR szFrd[50];
} CHATADDFRIEND;

// 搜索结构体
typedef struct _CHATSEARCHUSER {
	CHAR szName[50];
} CHATSEARCHUSER;

//文件传输结构体
typedef struct _CHATFILETRANS {
	CHAR  szName[48];
	DWORD dwLen;
	CHAR szContent[1024];
} CHATFILETRANS;

//查看聊天记录结构体
typedef struct _CHATMSGRECORD {
	CHAR szFrom[50];
	CHAR szTo[50];
	CHAR szConent[1024];
} CHATMSGRECORD;

//更新在线用户列表
typedef struct _CHATUPDATEUSER {
	DWORD bAdd;  // 是加入还是退出
	DWORD dwLen;  //一次只接收一个用户名
	CHAR  buf[50];
} CHATUPDATEUSER;

//发送内容
typedef struct _CHATSEND {
	CHATPURPOSE  m_type;
	union {
		char buf[BUFMSG];
		CHATANONYMOUS any;
		CHATCHAT  chat; //聊天
		CHATONE2ONE  o2o;  //lv1
		CHATREGISTER  reg; // 注册
		CHATLOGIN    login; //登陆
		CHATADDFRIEND  adf; //添加好友
		CHATSEARCHUSER  seu; //搜索好友
		CHATFILETRANS   trs; //文件传输
		CHATMSGRECORD rec; //聊天记录
		CHATUPDATEUSER upd; //更新用户列表
	} m_content;
} CHATSEND;





















