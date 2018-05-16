// SearchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Chat.h"
#include "SearchDlg.h"
#include "afxdialogex.h"


// CSearchDlg 对话框

IMPLEMENT_DYNAMIC(CSearchDlg, CDialogEx)

CSearchDlg::CSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SEARCH_DIALOG, pParent)
	, m_strSearch(_T(""))
{

}

CSearchDlg::~CSearchDlg()
{
}

void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEARCH_USER, m_strSearch);
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_USER, &CSearchDlg::OnClickedButtonSearchUser)
END_MESSAGE_MAP()


// CSearchDlg 消息处理程序


void CSearchDlg::OnClickedButtonSearchUser()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strSearch.IsEmpty()) {
		MessageBox(L"搜索内容为空");
		return;
	}
	CDialogEx::OnOK();
}
