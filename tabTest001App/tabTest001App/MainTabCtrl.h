#pragma once


// CMainTabCtrl

class CMainTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CMainTabCtrl)

public:
	CMainTabCtrl();
	virtual ~CMainTabCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	void InsertItemCustom(DWORD dwCount, ...);
	void AddDialogCustom(DWORD dwCount, ...);
	void ShowDialogCustom(INT nIndex);
public:
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CDialogEx* m_Dialog[10];
	DWORD m_dwDlgCount;
	
};


