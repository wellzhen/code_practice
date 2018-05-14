// ProcessDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "tabTest001App.h"
#include "ProcessDialog.h"
#include "afxdialogex.h"


// CProcessDialog 对话框

IMPLEMENT_DYNAMIC(CProcessDialog, CDialogEx)

CProcessDialog::CProcessDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PROCESS, pParent)
{

}

CProcessDialog::~CProcessDialog()
{
	int a = 1;
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
	m_ProcessList.InsertColumnCustom(4, 0.2, L"进程0", 0.2, L"进程1", 0.2, L"进程2", 0.2, L"进程3");
	m_ProcessList.InsertItemCustom(4, L"a", L"b", L"c", L"d");
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
