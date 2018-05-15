// WhisperDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Chat.h"
#include "WhisperDlg.h"
#include "afxdialogex.h"
#include "MainChatDlg.h"


// CWhisperDlg 对话框

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


// CWhisperDlg 消息处理程序


void CWhisperDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CDialogEx::OnClose();
	//只隐藏,不消失
	ShowWindow(SW_HIDE);

}


void CWhisperDlg::OnClickedButtonWhisperSend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strSend.IsEmpty()) {
		return;
	}
	CString strWisper;
	GetWindowText(strWisper);
	strWisper += L" : " + m_strSend;
	CStringA str = CW2A(strWisper.GetBuffer(), CP_THREAD_ACP);
	//获取父窗口
	CMainChatDlg *pParent = (CMainChatDlg*)GetParent();
	pParent->m_pClient->Send(ONE2ONE, str.GetBuffer(), str.GetLength() + 1);
	//显示在自己的对话框上
	m_strShow += "你说 : ";
	m_strShow += m_strSend;
	m_strShow += "\r\n";
	//发送内容置空
	m_strSend.Empty();
	UpdateData(FALSE);
	
}


void CWhisperDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}
