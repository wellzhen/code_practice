#pragma once
#include "afxcmn.h"
#include <map>
#include "ClientSocket.h"
using std::map;

// CMainChatDlg 对话框

class CMainChatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainChatDlg)

public:
	CMainChatDlg(CWnd* pParent = NULL);   // 标准构造函数
	CMainChatDlg(CClientSocket* pClient, CWnd* pParent = NULL);
	virtual ~CMainChatDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINCHATDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//登陆聊天还是匿名聊天
	BOOL m_bLogin = FALSE;
	//调用send/recv的类对象, socket对象指针
	CClientSocket * m_pClient;
	
	// 群聊信息显示框
	CString m_strChatShow;
	// 待发送的消息
	CString m_strChatSend;
	// list控件, 在线的用户列表
	CListCtrl m_listUserName;

	//1V1的聊天map 表
	map<CString, CDialogEx*> m_map;

	//鼠标点击在线用户列表时的索引值
	DWORD m_dwNameIndex = 0;
	//聊天记录窗口指针
	//CDlgRecord* m_pDlgRecord = nullptr;



};
