// ProcessDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "tabTest001App.h"
#include "ProcessDialog.h"
#include "afxdialogex.h"


// CProcessDialog �Ի���

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


// CProcessDialog ��Ϣ�������


BOOL CProcessDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ProcessList.InsertColumnCustom(4, 0.2, L"����0", 0.2, L"����1", 0.2, L"����2", 0.2, L"����3");
	m_ProcessList.InsertItemCustom(4, L"a", L"b", L"c", L"d");
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
