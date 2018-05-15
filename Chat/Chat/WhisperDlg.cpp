// WhisperDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chat.h"
#include "WhisperDlg.h"
#include "afxdialogex.h"
#include "MainChatDlg.h"


// CWhisperDlg �Ի���

IMPLEMENT_DYNAMIC(CWhisperDlg, CDialogEx)

CWhisperDlg::CWhisperDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WHISPER_DIALOG, pParent)
	, m_strShow(_T(""))
	, m_strSend(_T(""))
{

}

CWhisperDlg::~CWhisperDlg()
{
}

void CWhisperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_WHISPER_SHOW, m_strShow);
	//  DDX_Control(pDX, IDC_EDIT_WHISPER_SEND, m_strSend);
	DDX_Text(pDX, IDC_EDIT_WHISPER_SEND, m_strSend);
}


BEGIN_MESSAGE_MAP(CWhisperDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_WHISPER_SEND, &CWhisperDlg::OnClickedButtonWhisperSend)
END_MESSAGE_MAP()


// CWhisperDlg ��Ϣ�������


void CWhisperDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//CDialogEx::OnClose();
	//ֻ����,����ʧ
	ShowWindow(SW_HIDE);

}


void CWhisperDlg::OnClickedButtonWhisperSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_strSend.IsEmpty()) {
		return;
	}
	CString strWisper;
	GetWindowText(strWisper);
	strWisper += L" : " + m_strSend;
	CStringA str = CW2A(strWisper.GetBuffer(), CP_THREAD_ACP);
	//��ȡ������
	CMainChatDlg *pParent = (CMainChatDlg*)GetParent();
	pParent->m_pClient->Send(ONE2ONE, str.GetBuffer(), str.GetLength() + 1);
	//��ʾ���Լ��ĶԻ�����
	m_strShow += "��˵ : ";
	m_strShow += m_strSend;
	m_strShow += "\r\n";
	//���������ÿ�
	m_strSend.Empty();
	UpdateData(FALSE);
	
}


void CWhisperDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}
