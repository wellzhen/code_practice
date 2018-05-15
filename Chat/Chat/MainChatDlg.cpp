// MainChatDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chat.h"
#include "MainChatDlg.h"
#include "afxdialogex.h"
#include "ClientSocket.h"
#include "WhisperDlg.h"


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
	m_strChatShow += "��˵ : ";
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

	if (pNMItemActivate->iSubItem == -1) {
		return;
	}
	//�½�1v1����Ի���
	CWhisperDlg * pDlg = new CWhisperDlg;
	pDlg->Create(IDD_WHISPER_DIALOG, this);
	//���ô��ڱ���ΪҪ�����Ŀ���û���
	CString title = m_listUserName.GetItemText(pNMItemActivate->iSubItem, 0);
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
	// TODO: �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}
