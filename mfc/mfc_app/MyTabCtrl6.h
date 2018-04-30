#pragma once


// CMyTabCtrl6

class CMyTabCtrl6 : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyTabCtrl6)

public:
	CMyTabCtrl6();
	virtual ~CMyTabCtrl6();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CDialogEx* m_Dia[2];
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
};


