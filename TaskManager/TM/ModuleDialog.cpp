// ModuleDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TM.h"
#include "ModuleDialog.h"
#include "afxdialogex.h"
#include <TlHelp32.h>

#define WM_PID_CHOOSED  (WM_USER+10)

// CModuleDialog �Ի���

IMPLEMENT_DYNAMIC(CModuleDialog, CDialogEx)

CModuleDialog::CModuleDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MODULE, pParent)
{

}

CModuleDialog::~CModuleDialog()
{
	int a = 111; //test
}

void CModuleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MODULE, m_ModuleList);
}


BEGIN_MESSAGE_MAP(CModuleDialog, CDialogEx)

	ON_MESSAGE(WM_PID_CHOOSED, &CModuleDialog::OnPidChoosed)
END_MESSAGE_MAP()


// CModuleDialog ��Ϣ�������



BOOL CModuleDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//typedef struct tagMODULEENTRY32W
	//{
	//	DWORD   dwSize;
	//	DWORD   th32ModuleID;       // This module
	//	DWORD   th32ProcessID;      // owning process
	//	DWORD   GlblcntUsage;       // Global usage count on the module
	//	DWORD   ProccntUsage;       // Module usage count in th32ProcessID's context
	//	BYTE  * modBaseAddr;        // Base address of module in th32ProcessID's context
	//	DWORD   modBaseSize;        // Size in bytes of module starting at modBaseAddr
	//	HMODULE hModule;            // The hModule of this module in th32ProcessID's context
	//	WCHAR   szModule[MAX_MODULE_NAME32 + 1];
	//	WCHAR   szExePath[MAX_PATH];
	//} MODULEENTRY32W;
	MODULEENTRY32 me32 = { sizeof(MODULEENTRY32) };
	m_ModuleList.InsertColumnCustom(8, 0.08, L"PID", 0.07, L"ModuleID", 0.05, L"Size", 0.08, L"GlblcntUsage", 0.08, L"ProccntUsage", 0.08, L"modBaseSize", 0.15, L"Module", 0.1, L"ExePath" );
	
	/*CString msg;
	msg.Format(L"����id��: %d", m_pid);
	MessageBox(msg);*/
	//����ģ������
	HANDLE  hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, m_pid);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		MessageBox(L"Ȩ�޲���,�޷���ȡģ�����");
		return TRUE;
	}
	if (!Module32First(hSnapshot, &me32)) {
		MessageBox(L"�޷���ȡģ����յ�������Ϣ");
		CloseHandle(hSnapshot);
		return TRUE;
	}

	do {
		CString strPID, strMID, strSize, strGlbUsage, strProcUsage,strModBaseSize, strModule, strExePath;
		strPID.Format(L"%d", me32.th32ProcessID);
		strMID.Format(L"%d", me32.th32ModuleID);
		strSize.Format(L"%d", me32.dwSize);
		strGlbUsage.Format(L"%d", me32.GlblcntUsage);
		strProcUsage.Format(L"%d", me32.ProccntUsage);
		strModBaseSize.Format(L"%d", me32.modBaseSize);
		strModule.Format(L"%s", me32.szModule); //ֻ��һ���ַ�
		strExePath.Format(L"%s", me32.szExePath);
		
		m_ModuleList.InsertItemCustom(8, strPID, strMID, strSize, strGlbUsage, strProcUsage, strModBaseSize, strModule, strExePath);
	} while (Module32Next(hSnapshot, &me32));
	
	CloseHandle(hSnapshot);
	//SendMessage(WM_PID_CHOOSED, NULL, 255);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


afx_msg LRESULT CModuleDialog::OnPidChoosed(WPARAM wParam, LPARAM lParam)
{
	INT B = 1;
	return 0;
}
