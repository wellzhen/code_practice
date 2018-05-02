// ModuleDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ForeachApp.h"
#include "ModuleDialog.h"
#include "afxdialogex.h"
#include <TlHelp32.h>


// CModuleDialog �Ի���

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


// CModuleDialog ��Ϣ�������


BOOL CModuleDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ʼ��ģ���б�
	m_ModuleList.InsertColumnCustom(4, L"ģ��Id",L"ģ����",  L"exe·��", L"������id");

	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 9776);
	if (hSnapShot == INVALID_HANDLE_VALUE) {
		MessageBox(L"�޷�����ģ�����");
		return TRUE;
	}
	MODULEENTRY32  me32 = { sizeof(MODULEENTRY32) };
	if (!Module32First(hSnapShot, &me32)) {
		MessageBox(L"�޷���ȡ�����е�ģ��\n");
		CloseHandle(hSnapShot);
		return TRUE;
	}

	do {
		m_ModuleList.InsertItemCustom(4, me32.th32ModuleID, me32.szModule, me32.szExePath, me32.th32ProcessID);

	} while (Module32Next(hSnapShot, &me32));
	CloseHandle(hSnapShot);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
