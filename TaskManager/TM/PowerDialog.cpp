// PowerDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TM.h"
#include "PowerDialog.h"
#include "afxdialogex.h"
#include <PowrProf.h>
#pragma comment(lib,"PowrProf.lib")


// CPowerDialog �Ի���

IMPLEMENT_DYNAMIC(CPowerDialog, CDialogEx)

CPowerDialog::CPowerDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_POWER, pParent)
{

}

CPowerDialog::~CPowerDialog()
{
}

void CPowerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPowerDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_POWER_OFF, &CPowerDialog::OnBnClickedButtonPowerOff)
	ON_BN_CLICKED(IDC_BUTTON_RESTART, &CPowerDialog::OnBnClickedButtonRestart)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CPowerDialog::OnBnClickedButtonLogout)
	ON_BN_CLICKED(IDC_BUTTON_SLEEP, &CPowerDialog::OnBnClickedButtonSleep)
	ON_BN_CLICKED(IDC_BUTTON_LOCK, &CPowerDialog::OnBnClickedButtonLock)
	ON_BN_CLICKED(IDC_BUTTON_REST, &CPowerDialog::OnBnClickedButtonRest)
	ON_BN_CLICKED(IDC_BUTTON_HOT_KEY, &CPowerDialog::OnBnClickedButtonHotKey)
//	ON_WM_HOTKEY()
END_MESSAGE_MAP()


// CPowerDialog ��Ϣ�������


BOOL CPowerDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//����������Ȩ
	HANDLE hToken = NULL;
	HANDLE hProcess = GetCurrentProcess();
	OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	TOKEN_PRIVILEGES tp = {0};
	LookupPrivilegeValue(0, SE_SHUTDOWN_NAME, &tp.Privileges[0].Luid);
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	//���ú�������Ȩ��
	AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CPowerDialog::OnBnClickedButtonPowerOff()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ExitWindowsEx(EWX_POWEROFF , EWX_FORCE);
}


void CPowerDialog::OnBnClickedButtonRestart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ExitWindowsEx(EWX_REBOOT , EWX_FORCE);

}


void CPowerDialog::OnBnClickedButtonLogout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ExitWindowsEx(EWX_LOGOFF , EWX_FORCE);
}


void CPowerDialog::OnBnClickedButtonSleep()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetSuspendState(TRUE, FALSE, FALSE);
}


void CPowerDialog::OnBnClickedButtonLock()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	LockWorkStation();
}


void CPowerDialog::OnBnClickedButtonRest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetSuspendState(TRUE, FALSE, FALSE);
}


void CPowerDialog::OnBnClickedButtonHotKey()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL bRes = ::RegisterHotKey(m_hWnd, 0x1234, MOD_CONTROL | MOD_SHIFT, 'h');
	if (bRes) {
		MessageBox(L"ע�����");
	}
	else {
		MessageBox(L"ע��ʧ��");
	}
}


//void CPowerDialog::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
//}


BOOL CPowerDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	//MessageBox(L"�ϰ��");
	if(pMsg->message == WM_HOTKEY && pMsg->wParam == 0x1234) {
		if (IsWindowVisible() == TRUE) {
			ShowWindow(SW_HIDE);
		}
		else {
			ShowWindow(SW_SHOW);
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
