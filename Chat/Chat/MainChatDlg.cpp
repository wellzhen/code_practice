// MainChatDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chat.h"
#include "MainChatDlg.h"
#include "afxdialogex.h"
#include "ClientSocket.h"


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
}


void CMainChatDlg::OnDblclkListUserOnline(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
