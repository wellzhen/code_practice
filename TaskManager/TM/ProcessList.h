#pragma once
#include "ThreadDialog.h"
#include "ModuleDialog.h"
#include "HeapDialog.h"

// CProcessList

class CProcessList : public CListCtrl
{
	DECLARE_DYNAMIC(CProcessList)

public:
	CProcessList();
	virtual ~CProcessList();
protected:
	DECLARE_MESSAGE_MAP()
public:
	void InsertColumnCustom(DWORD dwCount, ...);
	void InsertItemCustom(DWORD dwCount, ...);

	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnShowthread();
	afx_msg void OnShowModule();
	afx_msg void OnShowHeap();
public:
	INT m_nChoosedPid; //保持选中的行的pid
	CThreadDialog * m_pThreadDialog;
	CModuleDialog * m_pModuleDialog;
	CHeapDialog * m_pHeapDialog;
	
	CDialogEx * m_ModuleDialogTest; // test;
	
	afx_msg void OnTerminateProcess();
protected:
	afx_msg LRESULT OnPidChoosed(WPARAM wParam, LPARAM lParam);
};


