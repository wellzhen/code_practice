// MainChatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Chat.h"
#include "MainChatDlg.h"
#include "afxdialogex.h"
#include "ClientSocket.h"


// CMainChatDlg 对话框

IMPLEMENT_DYNAMIC(CMainChatDlg, CDialogEx)

CMainChatDlg::CMainChatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAINCHATDLG, pParent)
	, m_strChatShow(_T(""))
	, m_strChatSend(_T(""))
{

}

CMainChatDlg::CMainChatDlg(CClientSocket* pClient, CWnd* pParent)
	:CDialogEx(IDD_MAINCHATDLG), m_pClient(pClient)
{

}

CMainChatDlg::~CMainChatDlg()
{
}

void CMainChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CHAT_SHOW, m_strChatShow);
	DDX_Text(pDX, IDC_EDIT_CHAT_SEND, m_strChatSend);
	DDX_Control(pDX, IDC_LIST_USER_ONLINE, m_listUserName);
}


BEGIN_MESSAGE_MAP(CMainChatDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEND_WORD, &CMainChatDlg::OnClickedButtonSendWord)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_USER_ONLINE, &CMainChatDlg::OnDblclkListUserOnline)
END_MESSAGE_MAP()


// CMainChatDlg 消息处理程序


BOOL CMainChatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// 设置窗口标题为用户昵称
	//匿名登陆时m_pClient->m_szName 是个随机值, 构造函数内初始化
	//登陆的时候是登陆用户名, 点登陆按钮的时候初始化
	CString strTitle(m_pClient->m_szName);
	SetWindowText(strTitle.GetBuffer());
	//设置窗体可见性
	ModifyStyleEx(0, WS_EX_APPWINDOW);
	//在线用户列表
	m_listUserName.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listUserName.InsertColumn(0, L"在线列表", 0, 100);
	//使用消息选择模型绑定socket和当前对话框
	// 1. define 自定义消息 WM_SOCKET
	// 2. 类向导添加自定义消息,  WM_SOCKET 响应函数 OnMySocket
	// 3. WSAAsyncSelect 绑定socket, 窗口和消息
	WSAAsyncSelect(m_pClient->m_sClient, m_hWnd, WM_MYSOCKET, FD_READ | FD_CLOSE);
	//告诉服务器自己的昵称
	m_pClient->Send(ANONYMOUS, m_pClient->m_szName, strlen(m_pClient->m_szName) + 1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



void CMainChatDlg::OnClickedButtonSendWord()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMainChatDlg::OnDblclkListUserOnline(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
