// PowerDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "TM.h"
#include "PowerDialog.h"
#include "afxdialogex.h"
#include <PowrProf.h>
#pragma comment(lib,"PowrProf.lib")


// CPowerDialog 对话框

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


// CPowerDialog 消息处理程序


BOOL CPowerDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//开启开机特权
	HANDLE hToken = NULL;
	HANDLE hProcess = GetCurrentProcess();
	OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	TOKEN_PRIVILEGES tp = {0};
	LookupPrivilegeValue(0, SE_SHUTDOWN_NAME, &tp.Privileges[0].Luid);
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	//调用函数提升权限
	AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CPowerDialog::OnBnClickedButtonPowerOff()
{
	// TODO: 在此添加控件通知处理程序代码
	ExitWindowsEx(EWX_POWEROFF , EWX_FORCE);
}


void CPowerDialog::OnBnClickedButtonRestart()
{
	// TODO: 在此添加控件通知处理程序代码
	ExitWindowsEx(EWX_REBOOT , EWX_FORCE);

}


void CPowerDialog::OnBnClickedButtonLogout()
{
	// TODO: 在此添加控件通知处理程序代码
	ExitWindowsEx(EWX_LOGOFF , EWX_FORCE);
}


void CPowerDialog::OnBnClickedButtonSleep()
{
	// TODO: 在此添加控件通知处理程序代码
	SetSuspendState(TRUE, FALSE, FALSE);
}


void CPowerDialog::OnBnClickedButtonLock()
{
	// TODO: 在此添加控件通知处理程序代码
	LockWorkStation();
}


void CPowerDialog::OnBnClickedButtonRest()
{
	// TODO: 在此添加控件通知处理程序代码
	SetSuspendState(TRUE, FALSE, FALSE);
}


void CPowerDialog::OnBnClickedButtonHotKey()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL bRes = ::RegisterHotKey(m_hWnd, 0x1234, MOD_CONTROL | MOD_SHIFT, 'h');
	if (bRes) {
		MessageBox(L"注册完成");
	}
	else {
		MessageBox(L"注册失败");
	}
}


//void CPowerDialog::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
//}


BOOL CPowerDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	//MessageBox(L"老板键");
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
