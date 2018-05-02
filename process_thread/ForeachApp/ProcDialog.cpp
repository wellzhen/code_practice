// ProcDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ForeachApp.h"
#include "ProcDialog.h"
#include "afxdialogex.h"
#include <TlHelp32.h>


// CProcDialog �Ի���

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


// CProcDialog ��Ϣ�������


BOOL CProcDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ʼ�������б�
	m_ProcList.InsertColumnCustom(3, L"����Id", L"������id", L"������");

	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapShot == INVALID_HANDLE_VALUE) {
		MessageBox(L"�޷��������̿���");
		return TRUE;
	}
	PROCESSENTRY32  pe32 = { sizeof(PROCESSENTRY32) };
	if (!Process32First(hSnapShot, &pe32)) {
		MessageBox(L"�޷���ȡ�����еĽ���\n");
		CloseHandle(hSnapShot);
		return TRUE;
	}

	do {
		m_ProcList.InsertItemCustom(3, pe32.th32ProcessID, pe32.th32ParentProcessID, pe32.szExeFile);

	} while (Process32Next(hSnapShot, &pe32));
	CloseHandle(hSnapShot);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
