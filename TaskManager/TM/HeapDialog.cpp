// HeapDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TM.h"
#include "HeapDialog.h"
#include "afxdialogex.h"
#include <TlHelp32.h>

// CHeapDialog �Ի���

IMPLEMENT_DYNAMIC(CHeapDialog, CDialogEx)

CHeapDialog::CHeapDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_HEAP, pParent)
{

}

CHeapDialog::~CHeapDialog()
{
}

void CHeapDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_HEAP, m_HeapList);
}


BEGIN_MESSAGE_MAP(CHeapDialog, CDialogEx)
END_MESSAGE_MAP()


// CHeapDialog ��Ϣ�������


BOOL CHeapDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//typedef struct tagHEAPLIST32
	//{
	//	SIZE_T dwSize;
	//	DWORD  th32ProcessID;   // owning process
	//	ULONG_PTR  th32HeapID;      // heap (in owning process's context!)
	//	DWORD  dwFlags;
	//} HEAPLIST32;
	HEAPLIST32  hl32 = { sizeof(HEAPLIST32) };
	//he32.dwSize = sizeof(HEAPLIST32);//no use

	m_HeapList.InsertColumnCustom(4, 0.2, L"PID", 0.2, L"HeapID", 0.2, L"Size", 0.2, L"Flags");

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, m_pid);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		MessageBox(L"�޷���ȡ�˽��̵Ķѿ���");
		return TRUE;
	}
	if (!Heap32ListFirst(hSnapshot, &hl32)) {
		MessageBox(L"�޷���ȡ�ѿ��յ��׸�����Ϣ");
		return TRUE;
	}

	INT loop = 0;
	do {
		CString strPID, strHeapID, strSize, strFlags;
		strPID.Format(L"%d", hl32.th32ProcessID);
		strHeapID.Format(L"%d", hl32.th32HeapID);
		strSize.Format(L"%d", hl32.dwSize);
		strFlags.Format(L"%d", hl32.dwFlags);
		m_HeapList.InsertItemCustom(4, strPID, strHeapID, strSize, strFlags);
		if (loop > 20) {
			//break;
		}
		loop++;
	} while (Heap32ListNext(hSnapshot, &hl32));



	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
