// ThreadDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "tabTest001App.h"
#include "ThreadDialog.h"
#include "afxdialogex.h"


// CThreadDialog 对话框

IMPLEMENT_DYNAMIC(CThreadDialog, CDialogEx)

CThreadDialog::CThreadDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_THREAD, pParent)
{

}

CThreadDialog::~CThreadDialog()
{
}

void CThreadDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_THREAD, m_ThreadList);
}


BEGIN_MESSAGE_MAP(CThreadDialog, CDialogEx)
END_MESSAGE_MAP()


// CThreadDialog 消息处理程序


BOOL CThreadDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ThreadList.InsertColumnCustom(4, 0.2, L"线程0", 0.2, L"线程1", 0.2, L"线程2", 0.2, L"线程3");
	m_ThreadList.InsertItemCustom(4, L"a", L"b", L"c", L"d");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
