#pragma once


// CMyTabCtrl7

class CMyTabCtrl7 : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyTabCtrl7)

public:
	CMyTabCtrl7();
	virtual ~CMyTabCtrl7();
	void InserTab(DWORD dwCount, ...); //插入选项卡
	void AddDlg(DWORD dwCount, ...); //增加对话框
	void SetSelAndShow(int nSec);

protected:
	DECLARE_MESSAGE_MAP()
public:
	CDialogEx* m_Dia[20];
	DWORD m_dwCount; //选项卡数量 
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
};


