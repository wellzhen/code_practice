// ThreadDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "tabTest001App.h"
#include "ThreadDialog.h"
#include "afxdialogex.h"


// CThreadDialog �Ի���

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


// CThreadDialog ��Ϣ�������


BOOL CThreadDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ThreadList.InsertColumnCustom(4, 0.2, L"�߳�0", 0.2, L"�߳�1", 0.2, L"�߳�2", 0.2, L"�߳�3");
	m_ThreadList.InsertItemCustom(4, L"a", L"b", L"c", L"d");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
