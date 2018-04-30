#pragma once


// CMyTabCtrl

class CMyTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyTabCtrl)

public:
	CMyTabCtrl();
	virtual ~CMyTabCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CDialogEx* m_Dia[2];
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
};


