#pragma once
#include "ProcDialog.h"
#include "ModuleDialog.h"

// CProcTabCtrl

class CProcTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CProcTabCtrl)

public:
	CProcTabCtrl();
	virtual ~CProcTabCtrl();
	void InsertItemCustom(DWORD dwCount, ...);
	void InsertDialogCustom(DWORD dwCount, ...);
	void ShowTabDialog(INT nIndex);
protected:
	DECLARE_MESSAGE_MAP()
public:
	CDialog* m_Dialog[2];
	DWORD m_dwTabCount;
	DWORD M_dwDialogCout;

	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
};


