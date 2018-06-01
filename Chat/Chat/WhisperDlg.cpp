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
	ON_BN_CLICKED(IDC_BTN_SEND_FILE, &CWhisperDlg::OnBnClickedBtnSendFile)
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


void CWhisperDlg::OnBnClickedBtnSendFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ȡͼƬ·��
	CString filePath;
	GetDlgItemText(IDC_FILE_BROWSER, filePath);
	if (filePath.IsEmpty()) {
		MessageBox(L"��ѡ��ͼƬ");
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
	strSize.Format(L"		���͵��ļ���С; %d\r\n", fileSize);
	m_strShow.Append(strSize);
	UpdateData(false);
	//��ȡ������
	CMainChatDlg *pParent = (CMainChatDlg*)GetParent();
	char buffer[1024];
	//������Ϣ
	CString strFrdName;
	GetWindowText(strFrdName);
	CStringA FrdName= CW2A(strFrdName.GetBuffer(), CP_THREAD_ACP);
	CStringA startData;
	//��������
	const char * content = "startfile";
	startData = FrdName;
	startData += ":";
	startData += content;
	//����Ϊ�ܳ���
	//strcpy_s(buffer, startData.GetLength() + 1, startData);
	// �����˺�:����
	pParent->m_pClient->Send(FILETRANS, startData.GetBuffer(), strlen(content) + 1); // ���������ݵĳ���, �����ܳ���
	//ѭ�������ļ���ʵ����
	DWORD dwSizeOfReaded;
	m_strShow += L" ������          ";
	UpdateData(FALSE);
	do {
		ZeroMemory(buffer, 1024);
		::ReadFile(hFile, buffer, sizeof(buffer), &dwSizeOfReaded, NULL);
		//ƴ�����ݰ�
		DWORD nameLen = FrdName.GetLength();
		char * data = new char[nameLen + 1 + dwSizeOfReaded];
		ZeroMemory(data, nameLen + 1 + dwSizeOfReaded);
		memcpy_s(data, nameLen, FrdName.GetBuffer(), nameLen);
		memcpy_s(data + nameLen, 1, ":", 1);
		memcpy_s(data + nameLen + 1,dwSizeOfReaded,  buffer, dwSizeOfReaded);
		pParent->m_pClient->Send(FILETRANS, data, dwSizeOfReaded); // ���������ݵĳ���
		m_strShow += L"*";
		UpdateData(FALSE);
		delete[] data;
		Sleep(1000);

	} while (dwSizeOfReaded == 1024);
	CloseHandle(hFile);
	m_strShow += L"\r\n        �ļ����ݴ������\r\n";
	UpdateData(FALSE);
	//���ͽ�����ʾ
	const char * endTip = "endfile";
	CStringA endData;
	endData = FrdName;
	endData += ":";
	endData += endTip;
	// �����˺�:����
	pParent->m_pClient->Send(FILETRANS, endData.GetBuffer(), strlen(endTip) + 1); // ���������ݵĳ���, �����ܳ���
	
	m_strShow += L"         �ļ����������\r\n";
	UpdateData(FALSE);
}
