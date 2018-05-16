// SearchDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chat.h"
#include "SearchDlg.h"
#include "afxdialogex.h"


// CSearchDlg �Ի���

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


// CSearchDlg ��Ϣ�������


void CSearchDlg::OnClickedButtonSearchUser()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_strSearch.IsEmpty()) {
		MessageBox(L"��������Ϊ��");
		return;
	}
	CDialogEx::OnOK();
}
