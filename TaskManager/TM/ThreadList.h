#pragma once


// CThreadList

class CThreadList : public CListCtrl
{
	DECLARE_DYNAMIC(CThreadList)

public:
	CThreadList();
	virtual ~CThreadList();

protected:
	DECLARE_MESSAGE_MAP()

public:
	void InsertColumnCustom(DWORD dwCount, ...);
	void InsertItemCustom(DWORD dwCount, ...);
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSuspendThread();
public:
	INT m_nChoosedTid;
	afx_msg void OnResumeThread();
	afx_msg void OnTerminateThread();
};


