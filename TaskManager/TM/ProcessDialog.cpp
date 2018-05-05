// ProcessDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TM.h"
#include "ProcessDialog.h"
#include "afxdialogex.h"
#include <TlHelp32.h>


// CProcessDialog �Ի���

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


// CProcessDialog ��Ϣ�������


BOOL CProcessDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ʼ�������б�ؼ�
	//��ȡ�ߴ�
	//CRect rc;
	//GetClientRect(&rc);
	//rc.DeflateRect(1, 1, 1, 1);
	//m_ProcessList.MoveWindow(rc); //�ı�ߴ���Ч
	
	//��ӽ��̱�������
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		MessageBox(L"�޷���ȡ���̿���");
		return TRUE;
	}
	PROCESSENTRY32  pe32 = { sizeof(PROCESSENTRY32) };
	if (Process32First(hSnapshot, &pe32) != TRUE) {
		MessageBox(L"�޷���ȡ���̿����е��׸�����");
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
				  // �쳣: OCX ����ҳӦ���� FALSE
}
