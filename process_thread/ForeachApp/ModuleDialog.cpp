// ModuleDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "ForeachApp.h"
#include "ModuleDialog.h"
#include "afxdialogex.h"
#include <TlHelp32.h>


// CModuleDialog 对话框

IMPLEMENT_DYNAMIC(CModuleDialog, CDialogEx)

CModuleDialog::CModuleDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MODUlE, pParent)
{

}

CModuleDialog::~CModuleDialog()
{
}

void CModuleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MODULE, m_ModuleList);
}


BEGIN_MESSAGE_MAP(CModuleDialog, CDialogEx)
END_MESSAGE_MAP()


// CModuleDialog 消息处理程序


BOOL CModuleDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//初始化模块列表
	m_ModuleList.InsertColumnCustom(4, L"模块Id",L"模块名",  L"exe路径", L"父进程id");

	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 9776);
	if (hSnapShot == INVALID_HANDLE_VALUE) {
		MessageBox(L"无法创建模块快照");
		return TRUE;
	}
	MODULEENTRY32  me32 = { sizeof(MODULEENTRY32) };
	if (!Module32First(hSnapShot, &me32)) {
		MessageBox(L"无法获取快照中的模块\n");
		CloseHandle(hSnapShot);
		return TRUE;
	}

	do {
		m_ModuleList.InsertItemCustom(4, me32.th32ModuleID, me32.szModule, me32.szExePath, me32.th32ProcessID);

	} while (Module32Next(hSnapShot, &me32));
	CloseHandle(hSnapShot);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
