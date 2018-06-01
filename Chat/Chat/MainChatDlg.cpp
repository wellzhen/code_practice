// MainChatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Chat.h"
#include "MainChatDlg.h"
#include "afxdialogex.h"
#include "ClientSocket.h"
#include "WhisperDlg.h"
#include "SearchDlg.h"

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
	ON_NOTIFY(NM_RCLICK, IDC_LIST_USER_ONLINE, &CMainChatDlg::OnRclickListUserOnline)
	ON_COMMAND(ID_ADD_FRIEND, &CMainChatDlg::OnAddFriend)
	ON_COMMAND(ID_SEARCH_FRIEND, &CMainChatDlg::OnSearchFriend)
	ON_COMMAND(ID_QUERY_RECORD, &CMainChatDlg::OnQueryRecord)
	ON_WM_TIMER()
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
	m_strChatShow += "[ 你 ] : ";
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
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem == -1) {
		//MessageBox(L"over");
		return;
	}
	int rowCount = m_listUserName.GetItemCount();
	POSITION pstion = m_listUserName.GetFirstSelectedItemPosition();
	int nIndex = m_listUserName.GetNextSelectedItem(pstion);
	CString test;
	test.Format(L"%d  %d", rowCount, nIndex);
	//MessageBox(test);
	if (nIndex > rowCount - 1) {
		//MessageBox(L"out index");
		return;
	}
	CString title = m_listUserName.GetItemText(nIndex, 0);
	if (title == m_pClient->m_szName) {
		MessageBox(L"不能与自己聊天");
		return;
	}

	//新建1v1聊天对话框
	CWhisperDlg * pDlg = new CWhisperDlg;
	pDlg->Create(IDD_WHISPER_DIALOG, this);
	//设置窗口标题为要聊天的目标用户名
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
			else if (m_pClient->m_pObjFileTrans) {
				//文件传输用到
				ChatForFileRecv(*m_pClient->m_pObjFileTrans);
				delete m_pClient->m_pObjFileTrans;
				m_pClient->m_pObjFileTrans = nullptr;
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
		pDlg->m_strShow += L"\r\n";
		pDlg->UpdateData(FALSE);
		pDlg->ShowWindow(SW_SHOW);
	}
	else {
		CWhisperDlg *pDlg = (CWhisperDlg*)m_map[strName];
		pDlg->UpdateData(TRUE);
		pDlg->m_strShow += strName + L" : " + strContent;
		pDlg->m_strShow += L"\r\n";
		pDlg->UpdateData(FALSE);
		pDlg->ShowWindow(SW_SHOW);


	}
}
//收文件
void CMainChatDlg::ChatForFileRecv(CHATFILETRANS &objFileTrans)
{

	CString strName(objFileTrans.szName);
	CString strContent(objFileTrans.szContent);
	int ContentSize = objFileTrans.dwLen;
	//接收文件
	CWhisperDlg  *pDlg = NULL;
	if (m_map.find(strName) == m_map.end()) {
		//创建私聊窗口
		pDlg = new CWhisperDlg;
		pDlg->Create(IDD_WHISPER_DIALOG, this);
		pDlg->SetWindowTextW(strName.GetBuffer());
		m_map[strName] = pDlg;
	}
	else {
		pDlg = (CWhisperDlg*)m_map[strName];
	}
	pDlg->UpdateData(TRUE);
	pDlg->ShowWindow(SW_SHOW);
	//第一个接收?
	CStringA strGet = CW2A(strContent.GetBuffer(), CP_THREAD_ACP);
	if (strcmp(strGet, "startfile") == 0 ){
		//第一次接收文件提醒	
		pDlg->m_strShow += L"                    开始接收文件";
		pDlg->UpdateData(FALSE);
		m_vecFileRecord.clear();
	}
	else if(strcmp(strGet, "endfile") == 0 ){
		//接收完成
		pDlg->m_strShow += L"\r\n                 文件接收完成, 开始写入磁盘 \r\n";
		pDlg->UpdateData(FALSE);

		HANDLE hFileRecv = CreateFile(L".\\a.png", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		//循环写入磁盘
		DWORD WrittenSize;
		for (DWORD i = 0; i < m_vecFileRecord.size(); i++) {
			::WriteFile(hFileRecv, m_vecFileRecord[i].szContent, m_vecFileRecord[i].dwLen, &WrittenSize, NULL);
			pDlg->m_strShow += L"*";
			pDlg->UpdateData(false);
		}
		pDlg->m_strShow += L"文件已经生成\r\n";
		pDlg->UpdateData(false);
		//关闭文件句柄
		CloseHandle(hFileRecv);
		m_vecFileRecord.clear();
	}
	else {
		//保存文件内容
		m_vecFileRecord.push_back(objFileTrans);
		pDlg->m_strShow += L".";
		pDlg->UpdateData(false);
	}
}


void CMainChatDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CMainChatDlg::OnRclickListUserOnline(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	if (!m_bLogin) {
		return;
	}
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point(LOWORD(dwPos), HIWORD(dwPos));
		CMenu menu;
		//添加线程操作  
		menu.LoadMenu(IDR_MENU_INTERACT);           //这里是我们在1中定义的MENU的文件名称  
		CMenu* popup = menu.GetSubMenu(0);
		ASSERT(popup != NULL);
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		//设置点击的索引
		POSITION pstion = m_listUserName.GetFirstSelectedItemPosition();
		int nIndex = m_listUserName.GetNextSelectedItem(pstion);
		m_dwNameIndex = nIndex;
	}
}


void CMainChatDlg::OnAddFriend()
{
	// TODO: 在此添加命令处理程序代码
	//目标名字
	CString strFriend = m_listUserName.GetItemText(m_dwNameIndex, 0);
	//当前用户:目标名字
	CString strUserFrd;
	GetWindowTextW(strUserFrd);
	strUserFrd += L":";
	strUserFrd += strFriend;
	CStringA strSend = CW2A(strUserFrd.GetBuffer(), CP_THREAD_ACP);
	m_pClient->Send(ADDFRIEND, strSend.GetBuffer(), strSend.GetLength() + 1);
}


void CMainChatDlg::OnSearchFriend()
{
	// TODO: 在此添加命令处理程序代码
	CSearchDlg dlgSearch;
	dlgSearch.DoModal();
	if (dlgSearch.m_strSearch.IsEmpty()) {
		//MessageBox(L"搜索内容为空2");
		return;
	}
	//MessageBox(dlgSearch.m_strSearch);
	CStringA strSearch = CW2A(dlgSearch.m_strSearch.GetBuffer(), CP_THREAD_ACP);
	m_pClient->Send(SEARCHUSER, strSearch.GetBuffer(), strSearch.GetLength() + 1);

}


void CMainChatDlg::OnQueryRecord()
{
	// TODO: 在此添加命令处理程序代码
	//设置事件同步
	m_pClient->m_hEvent = CreateEvent(NULL, false, true, NULL);
	DWORD dwRet = WaitForSingleObject(m_pClient->m_hEvent, 100);
	if (dwRet == WAIT_FAILED || dwRet == WAIT_TIMEOUT) {
		MessageBox(L"等待超时");
		return;
	}
	m_pClient->Send(MSGRECORD, NULL, NULL);
	m_pClient->m_vecMsgRecord.clear();
	//设置定时器等待消息返回
	SetTimer(0x1001, 1000, NULL);

}


void CMainChatDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 0x1001) {
		//等待消息记录返回, 消息记录会把事件对象置为true
		DWORD dwRet = WaitForSingleObject(m_pClient->m_hEvent, 100);
		if (dwRet == WAIT_OBJECT_0) {
			KillTimer(nIDEvent);
			SetEvent(m_pClient->m_hEvent);
			//显示新窗口
			if (m_pDlgRecord) {
				m_pDlgRecord->UpdateList();
				m_pDlgRecord->ShowWindow(SW_SHOW);
			}
			else {
				m_pDlgRecord = new CRecordDlg;
				m_pDlgRecord->Create(IDD_RECORD_DIALOG, this);
				m_pDlgRecord->ShowWindow(SW_SHOW);
			}
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}
