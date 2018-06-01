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
	ON_BN_CLICKED(IDC_BTN_SEND_FILE, &CWhisperDlg::OnBnClickedBtnSendFile)
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


void CWhisperDlg::OnBnClickedBtnSendFile()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取图片路径
	CString filePath;
	GetDlgItemText(IDC_FILE_BROWSER, filePath);
	if (filePath.IsEmpty()) {
		MessageBox(L"请选择图片");
		return;
	}
	else {
		m_strShow.Append(filePath);
		m_strShow.Append(L"\r\n");
		UpdateData(FALSE);
	}
	//MessageBox(filePath);
	HANDLE hFile;
	hFile = CreateFile(filePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	unsigned long long fileSize = 0;
	fileSize = GetFileSize(hFile, NULL);
	CString strSize;
	strSize.Format(L"		发送的文件大小; %d\r\n", fileSize);
	m_strShow.Append(strSize);
	UpdateData(false);
	//获取父窗口
	CMainChatDlg *pParent = (CMainChatDlg*)GetParent();
	char buffer[1024];
	//好友信息
	CString strFrdName;
	GetWindowText(strFrdName);
	CStringA FrdName= CW2A(strFrdName.GetBuffer(), CP_THREAD_ACP);
	CStringA startData;
	//具体内容
	const char * content = "startfile";
	startData = FrdName;
	startData += ":";
	startData += content;
	//长度为总长度
	//strcpy_s(buffer, startData.GetLength() + 1, startData);
	// 好友账号:内容
	pParent->m_pClient->Send(FILETRANS, startData.GetBuffer(), strlen(content) + 1); // 长度是内容的长度, 不是总长度
	//循环发送文件真实内容
	DWORD dwSizeOfReaded;
	m_strShow += L" 发送中          ";
	UpdateData(FALSE);
	do {
		ZeroMemory(buffer, 1024);
		::ReadFile(hFile, buffer, sizeof(buffer), &dwSizeOfReaded, NULL);
		//拼凑数据包
		DWORD nameLen = FrdName.GetLength();
		char * data = new char[nameLen + 1 + dwSizeOfReaded];
		ZeroMemory(data, nameLen + 1 + dwSizeOfReaded);
		memcpy_s(data, nameLen, FrdName.GetBuffer(), nameLen);
		memcpy_s(data + nameLen, 1, ":", 1);
		memcpy_s(data + nameLen + 1,dwSizeOfReaded,  buffer, dwSizeOfReaded);
		pParent->m_pClient->Send(FILETRANS, data, dwSizeOfReaded); // 长度是内容的长度
		m_strShow += L"*";
		UpdateData(FALSE);
		delete[] data;
		Sleep(1000);

	} while (dwSizeOfReaded == 1024);
	CloseHandle(hFile);
	m_strShow += L"\r\n        文件内容传输完成\r\n";
	UpdateData(FALSE);
	//发送结束提示
	const char * endTip = "endfile";
	CStringA endData;
	endData = FrdName;
	endData += ":";
	endData += endTip;
	// 好友账号:内容
	pParent->m_pClient->Send(FILETRANS, endData.GetBuffer(), strlen(endTip) + 1); // 长度是内容的长度, 不是总长度
	
	m_strShow += L"         文件传输已完成\r\n";
	UpdateData(FALSE);
}
