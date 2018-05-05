// ProcessDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "TM.h"
#include "ProcessDialog.h"
#include "afxdialogex.h"
#include <TlHelp32.h>


// CProcessDialog 对话框

IMPLEMENT_DYNAMIC(CProcessDialog, CDialogEx)

CProcessDialog::CProcessDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PROCESS, pParent)
{

}

CProcessDialog::~CProcessDialog()
{
}

void CProcessDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROCESS, m_ProcessList);
}


BEGIN_MESSAGE_MAP(CProcessDialog, CDialogEx)
END_MESSAGE_MAP()


// CProcessDialog 消息处理程序


BOOL CProcessDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//初始化进程列表控件
	//获取尺寸
	//CRect rc;
	//GetClientRect(&rc);
	//rc.DeflateRect(1, 1, 1, 1);
	//m_ProcessList.MoveWindow(rc); //改变尺寸无效
	
	//添加进程遍历数据
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		MessageBox(L"无法获取进程快照");
		return TRUE;
	}
	PROCESSENTRY32  pe32 = { sizeof(PROCESSENTRY32) };
	if (Process32First(hSnapshot, &pe32) != TRUE) {
		MessageBox(L"无法获取进程快照中的首个进程");
		CloseHandle(hSnapshot);
		return TRUE;
	}
	m_ProcessList.InsertColumnCustom(10, 0.1, L"PID", 0.2, L"exeFile", 0.1, L"cntThreads", 0.1, L"Size", 0.08, L"PriClassBase", 0.08, L"ParentPID", 0.08, L"MoudleID", 0.05, L"Usage", 0.05, L"Flags", 0.1, L"defHeadID");
	do {
		
		CString strPID, strMID , strPPID, strExeFile, strThreads, strUsage,strPriClassBase, strFlags, strSize, strHeadID;
		strPID.Format(L"%d", pe32.th32ProcessID);
		strPPID.Format(L"%d", pe32.th32ParentProcessID);
		strMID.Format(L"%d", pe32.th32ModuleID);
		strThreads.Format(L"%d", pe32.cntThreads);
		strUsage.Format(L"%d", pe32.cntUsage);
		
		strPriClassBase.Format(L"%d", pe32.pcPriClassBase);
		strHeadID.Format(L"%d", pe32.th32DefaultHeapID);
		strFlags.Format(L"%d", pe32.dwFlags);
		strSize.Format(L"%d", pe32.dwSize);

		strExeFile = pe32.szExeFile;

		m_ProcessList.InsertItemCustom(10, strPID, strExeFile, strThreads, strSize, strPriClassBase, strPPID, strMID,  strUsage,  strFlags, strHeadID);

	} while (Process32Next(hSnapshot, &pe32));


	CloseHandle(hSnapshot);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
