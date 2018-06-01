// MainChatDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chat.h"
#include "MainChatDlg.h"
#include "afxdialogex.h"
#include "ClientSocket.h"
#include "WhisperDlg.h"
#include "SearchDlg.h"

// CMainChatDlg �Ի���

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


// CMainChatDlg ��Ϣ�������


BOOL CMainChatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	// ���ô��ڱ���Ϊ�û��ǳ�
	//������½ʱm_pClient->m_szName �Ǹ����ֵ, ���캯���ڳ�ʼ��
	//��½��ʱ���ǵ�½�û���, ���½��ť��ʱ���ʼ��
	CString strTitle(m_pClient->m_szName);
	SetWindowText(strTitle.GetBuffer());
	//���ô���ɼ���
	ModifyStyleEx(0, WS_EX_APPWINDOW);
	//�����û��б�
	m_listUserName.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listUserName.InsertColumn(0, L"�����б�", 0, 100);
	//ʹ����Ϣѡ��ģ�Ͱ�socket�͵�ǰ�Ի���
	// 1. define �Զ�����Ϣ WM_SOCKET
	// 2. ��������Զ�����Ϣ,  WM_SOCKET ��Ӧ���� OnMySocket
	// 3. WSAAsyncSelect ��socket, ���ں���Ϣ
	WSAAsyncSelect(m_pClient->m_sClient, m_hWnd, WM_MYSOCKET, FD_READ | FD_CLOSE);
	//���߷������Լ����ǳ�
	m_pClient->Send(ANONYMOUS, m_pClient->m_szName, strlen(m_pClient->m_szName) + 1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}



void CMainChatDlg::OnClickedButtonSendWord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_strChatSend.IsEmpty()) {
		//���Ϳ������Ϊ��
		return;
	}
	CStringA str = CW2A(m_strChatSend.GetBuffer(), CP_THREAD_ACP);
	m_pClient->Send(CHAT, str.GetBuffer(), str.GetLength() + 1);
	//��ʾ���Լ��ĶԻ�����
	m_strChatShow += "[ �� ] : ";
	m_strChatShow += m_strChatSend;
	m_strChatShow += "\r\n";
	//������Ϣ�ÿ�
	m_strChatSend.Empty();
	UpdateData(FALSE);

}


void CMainChatDlg::OnDblclkListUserOnline(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		MessageBox(L"�������Լ�����");
		return;
	}

	//�½�1v1����Ի���
	CWhisperDlg * pDlg = new CWhisperDlg;
	pDlg->Create(IDD_WHISPER_DIALOG, this);
	//���ô��ڱ���ΪҪ�����Ŀ���û���
	pDlg->SetWindowTextW(title.GetBuffer());
	//�Ѹ�˽�Ĵ�����ӵ��Լ���˽��Map����
	m_map[title] = pDlg;
	pDlg->ShowWindow(SW_SHOW);

}


afx_msg LRESULT CMainChatDlg::OnMysocket(WPARAM wParam, LPARAM lParam)
{
	//wparam��socket
	//lparam   ��word: �¼�   ��word: ������
	SOCKET s = wParam;
	WORD wEvent = WSAGETSELECTEVENT(lParam);
	WORD wErrorCode = WSAGETSELECTERROR(lParam);
	//���ж��Ƿ�����������¼�����, ��������
	if (wErrorCode) {
		exit(0);
		MessageBox(L"�������");
		CDialogEx::OnClose();
	}
	switch(wEvent) {
	case FD_READ:
	{
		char* szRecv = m_pClient->Recv();
		if (szRecv == nullptr) {
			if (m_pClient->m_pObjUpdate) {
				//�����û��б�, �ж��û��Ǽ��뻹���˳�, RecvForUpdateUserlist�������ش���
				InsertOrDeleteUser(*m_pClient->m_pObjUpdate);
				delete  m_pClient->m_pObjUpdate;
				m_pClient->m_pObjUpdate = nullptr;
			}
			else if (m_pClient->m_pObjOne2One) {
				// 1V1�����õ�, RecvForOne2One�������ش���
				ChatForOne2One(*m_pClient->m_pObjOne2One);
				delete m_pClient->m_pObjOne2One;
				m_pClient->m_pObjOne2One = nullptr;
			}
			else if (m_pClient->m_pObjFileTrans) {
				//�ļ������õ�
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
		//����˽�Ĵ���
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
//���ļ�
void CMainChatDlg::ChatForFileRecv(CHATFILETRANS &objFileTrans)
{

	CString strName(objFileTrans.szName);
	CString strContent(objFileTrans.szContent);
	int ContentSize = objFileTrans.dwLen;
	//�����ļ�
	CWhisperDlg  *pDlg = NULL;
	if (m_map.find(strName) == m_map.end()) {
		//����˽�Ĵ���
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
	//��һ������?
	CStringA strGet = CW2A(strContent.GetBuffer(), CP_THREAD_ACP);
	if (strcmp(strGet, "startfile") == 0 ){
		//��һ�ν����ļ�����	
		pDlg->m_strShow += L"                    ��ʼ�����ļ�";
		pDlg->UpdateData(FALSE);
		m_vecFileRecord.clear();
	}
	else if(strcmp(strGet, "endfile") == 0 ){
		//�������
		pDlg->m_strShow += L"\r\n                 �ļ��������, ��ʼд����� \r\n";
		pDlg->UpdateData(FALSE);

		HANDLE hFileRecv = CreateFile(L".\\a.png", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		//ѭ��д�����
		DWORD WrittenSize;
		for (DWORD i = 0; i < m_vecFileRecord.size(); i++) {
			::WriteFile(hFileRecv, m_vecFileRecord[i].szContent, m_vecFileRecord[i].dwLen, &WrittenSize, NULL);
			pDlg->m_strShow += L"*";
			pDlg->UpdateData(false);
		}
		pDlg->m_strShow += L"�ļ��Ѿ�����\r\n";
		pDlg->UpdateData(false);
		//�ر��ļ����
		CloseHandle(hFileRecv);
		m_vecFileRecord.clear();
	}
	else {
		//�����ļ�����
		m_vecFileRecord.push_back(objFileTrans);
		pDlg->m_strShow += L".";
		pDlg->UpdateData(false);
	}
}


void CMainChatDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}


void CMainChatDlg::OnRclickListUserOnline(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		//����̲߳���  
		menu.LoadMenu(IDR_MENU_INTERACT);           //������������1�ж����MENU���ļ�����  
		CMenu* popup = menu.GetSubMenu(0);
		ASSERT(popup != NULL);
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		//���õ��������
		POSITION pstion = m_listUserName.GetFirstSelectedItemPosition();
		int nIndex = m_listUserName.GetNextSelectedItem(pstion);
		m_dwNameIndex = nIndex;
	}
}


void CMainChatDlg::OnAddFriend()
{
	// TODO: �ڴ���������������
	//Ŀ������
	CString strFriend = m_listUserName.GetItemText(m_dwNameIndex, 0);
	//��ǰ�û�:Ŀ������
	CString strUserFrd;
	GetWindowTextW(strUserFrd);
	strUserFrd += L":";
	strUserFrd += strFriend;
	CStringA strSend = CW2A(strUserFrd.GetBuffer(), CP_THREAD_ACP);
	m_pClient->Send(ADDFRIEND, strSend.GetBuffer(), strSend.GetLength() + 1);
}


void CMainChatDlg::OnSearchFriend()
{
	// TODO: �ڴ���������������
	CSearchDlg dlgSearch;
	dlgSearch.DoModal();
	if (dlgSearch.m_strSearch.IsEmpty()) {
		//MessageBox(L"��������Ϊ��2");
		return;
	}
	//MessageBox(dlgSearch.m_strSearch);
	CStringA strSearch = CW2A(dlgSearch.m_strSearch.GetBuffer(), CP_THREAD_ACP);
	m_pClient->Send(SEARCHUSER, strSearch.GetBuffer(), strSearch.GetLength() + 1);

}


void CMainChatDlg::OnQueryRecord()
{
	// TODO: �ڴ���������������
	//�����¼�ͬ��
	m_pClient->m_hEvent = CreateEvent(NULL, false, true, NULL);
	DWORD dwRet = WaitForSingleObject(m_pClient->m_hEvent, 100);
	if (dwRet == WAIT_FAILED || dwRet == WAIT_TIMEOUT) {
		MessageBox(L"�ȴ���ʱ");
		return;
	}
	m_pClient->Send(MSGRECORD, NULL, NULL);
	m_pClient->m_vecMsgRecord.clear();
	//���ö�ʱ���ȴ���Ϣ����
	SetTimer(0x1001, 1000, NULL);

}


void CMainChatDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == 0x1001) {
		//�ȴ���Ϣ��¼����, ��Ϣ��¼����¼�������Ϊtrue
		DWORD dwRet = WaitForSingleObject(m_pClient->m_hEvent, 100);
		if (dwRet == WAIT_OBJECT_0) {
			KillTimer(nIDEvent);
			SetEvent(m_pClient->m_hEvent);
			//��ʾ�´���
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
