// ThreadDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TM.h"
#include "ThreadDialog.h"
#include "afxdialogex.h"
#include <TlHelp32.h>
#include "ProcessList.h"


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
	//�����߳��б�
	//typedef struct tagTHREADENTRY32
	//{
	//	DWORD   dwSize;
	//	DWORD   cntUsage;
	//	DWORD   th32ThreadID;       // this thread
	//	DWORD   th32OwnerProcessID; // Process this thread is associated with
	//	LONG    tpBasePri;
	//	LONG    tpDeltaPri;
	//	DWORD   dwFlags;
	//} THREADENTRY32;
	m_ThreadList.InsertColumnCustom(7, 0.13, L"OwerPID", 0.13, L"ThreadID",0.13, L"BasePri", 0.13, L"DeltaPri", 0.13, L"Size", 0.13, L"Flags", 0.13, L"Usage");
	
	//��ȡ�����µ��߳��б�
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, m_pid);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		MessageBox(L"�޷���ȡ��ǰ���̵��߳̿���");
		return TRUE;
	}
	THREADENTRY32 te32;
	te32.dwSize = sizeof(THREADENTRY32);
	if (! Thread32First(hSnapshot, &te32)) {
		MessageBox(L"�޷���ȡ��ǰ�߳̿����е��׸��߳���Ϣ");
		return TRUE;
	}
	CString  strTid, strPid, strBasePri, strDeltaPri, strSize, strFlags, strUsage;
	
	do {
		if (te32.th32OwnerProcessID == m_pid) {
			strTid.Format(L"%d", te32.th32ThreadID);
			strPid.Format(L"%d", te32.th32OwnerProcessID);
			strBasePri.Format(L"%d", te32.tpBasePri);
			strDeltaPri.Format(L"%d", te32.tpDeltaPri);
			strSize.Format(L"%d", te32.dwSize);
			strFlags.Format(L"%d", te32.dwFlags);
			strUsage.Format(L"%d", te32.cntUsage);
			m_ThreadList.InsertItemCustom(7, strPid, strTid, strBasePri, strDeltaPri, strSize, strFlags, strUsage);
		}
	} while(Thread32Next(hSnapshot, &te32));

	CloseHandle(hSnapshot);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
