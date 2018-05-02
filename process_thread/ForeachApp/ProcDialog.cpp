// ProcDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "ForeachApp.h"
#include "ProcDialog.h"
#include "afxdialogex.h"
#include <TlHelp32.h>


// CProcDialog 对话框

IMPLEMENT_DYNAMIC(CProcDialog, CDialogEx)

CProcDialog::CProcDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PROC, pParent)
{

}

CProcDialog::~CProcDialog()
{
}

void CProcDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LIST_PROC, m_ProcList);
	DDX_Control(pDX, IDC_LIST_PROC, m_ProcList);
}


BEGIN_MESSAGE_MAP(CProcDialog, CDialogEx)
END_MESSAGE_MAP()


// CProcDialog 消息处理程序


BOOL CProcDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//初始化进程列表
	m_ProcList.InsertColumnCustom(3, L"进程Id", L"父进程id", L"进程名");

	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapShot == INVALID_HANDLE_VALUE) {
		MessageBox(L"无法创建进程快照");
		return TRUE;
	}
	PROCESSENTRY32  pe32 = { sizeof(PROCESSENTRY32) };
	if (!Process32First(hSnapShot, &pe32)) {
		MessageBox(L"无法获取快照中的进程\n");
		CloseHandle(hSnapShot);
		return TRUE;
	}

	do {
		m_ProcList.InsertItemCustom(3, pe32.th32ProcessID, pe32.th32ParentProcessID, pe32.szExeFile);

	} while (Process32Next(hSnapShot, &pe32));
	CloseHandle(hSnapShot);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
