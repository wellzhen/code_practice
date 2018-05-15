// MainChatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Chat.h"
#include "MainChatDlg.h"
#include "afxdialogex.h"
#include "ClientSocket.h"
#include "WhisperDlg.h"


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
	ON_MESSAGE(WM_MYSOCKET, &CMainChatDlg::OnMysocket)
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
	UpdateData(TRUE);
	if (m_strChatSend.IsEmpty()) {
		//发送框的内容为空
		return;
	}
	CStringA str = CW2A(m_strChatSend.GetBuffer(), CP_THREAD_ACP);
	m_pClient->Send(CHAT, str.GetBuffer(), str.GetLength() + 1);
	//显示在自己的对话框上
	m_strChatShow += "你说 : ";
	m_strChatShow += m_strChatSend;
	m_strChatShow += "\r\n";
	//发送消息置空
	m_strChatSend.Empty();
	UpdateData(FALSE);

}


void CMainChatDlg::OnDblclkListUserOnline(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	if (pNMItemActivate->iSubItem == -1) {
		return;
	}
	//新建1v1聊天对话框
	CWhisperDlg * pDlg = new CWhisperDlg;
	pDlg->Create(IDD_WHISPER_DIALOG, this);
	//设置窗口标题为要聊天的目标用户名
	CString title = m_listUserName.GetItemText(pNMItemActivate->iSubItem, 0);
	pDlg->SetWindowTextW(title.GetBuffer());
	//把该私聊窗口添加到自己的私聊Map表中
	m_map[title] = pDlg;
	pDlg->ShowWindow(SW_SHOW);

}


afx_msg LRESULT CMainChatDlg::OnMysocket(WPARAM wParam, LPARAM lParam)
{
	//wparam是socket
	//lparam   低word: 事件   高word: 错误码
	SOCKET s = wParam;
	WORD wEvent = WSAGETSELECTEVENT(lParam);
	WORD wErrorCode = WSAGETSELECTERROR(lParam);
	//先判断是否有网络错误事件发生, 有则跳过
	if (wErrorCode) {
		exit(0);
		MessageBox(L"网络错误");
		CDialogEx::OnClose();
	}
	switch(wEvent) {
	case FD_READ:
	{
		char* szRecv = m_pClient->Recv();
		if (szRecv == nullptr) {
			if (m_pClient->m_pObjUpdate) {
				//更新用户列表, 判断用户是加入还是退出, RecvForUpdateUserlist函数返回处理
				InsertOrDeleteUser(*m_pClient->m_pObjUpdate);
				delete  m_pClient->m_pObjUpdate;
				m_pClient->m_pObjUpdate = nullptr;
			}
			else if (m_pClient->m_pObjOne2One) {
				// 1V1聊天用到, RecvForOne2One函数返回处理
				ChatForOne2One(*m_pClient->m_pObjOne2One);
				delete m_pClient->m_pObjOne2One;
				m_pClient->m_pObjOne2One = nullptr;
			}
			return 0;
		}
		UpdateData(TRUE);
		m_strChatShow += szRecv;
		m_strChatShow += "\r\n";
		UpdateData(FALSE);
	}
	default:
		break;
	}
	return 0;
}



void CMainChatDlg::InsertOrDeleteUser(CHATUPDATEUSER &objUpdate)
{
		
	char * name = objUpdate.buf;
	CString nameInfo = CA2W(name);
	if (objUpdate.bAdd) {
		m_listUserName.InsertItem(0, nameInfo);
	}
	else {
		int rowCount = m_listUserName.GetItemCount();
		for (int i = 0; i < rowCount; i++) {
			CString name = m_listUserName.GetItemText(i, 0);
			if (name == nameInfo) {
				m_listUserName.DeleteItem(i);
				break;
			}
		}
	}
}
void CMainChatDlg::ChatForOne2One(CHATONE2ONE &objOne2One)
{
	CString strName(objOne2One.szName);
	CString strContent(objOne2One.szContent);
	if (m_map.find(strName) == m_map.end()) {
		//创建私聊窗口
		CWhisperDlg  *pDlg = new CWhisperDlg;
		pDlg->Create(IDD_WHISPER_DIALOG, this);
		pDlg->SetWindowTextW(strName.GetBuffer());
		m_map[strName] = pDlg;
		pDlg->m_strShow += strName + L" : " + strContent;
		pDlg->m_strShow += "\r\n";
		pDlg->UpdateData(FALSE);
		pDlg->ShowWindow(SW_SHOW);
	}
	else {
		CWhisperDlg *pDlg = (CWhisperDlg*)m_map[strName];
		pDlg->UpdateData(TRUE);
		pDlg->m_strShow += strName + " : " + strContent;
		pDlg->m_strShow += "\r\n";
		pDlg->UpdateData(FALSE);
		pDlg->ShowWindow(SW_SHOW);


	}
}












void CMainChatDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}
