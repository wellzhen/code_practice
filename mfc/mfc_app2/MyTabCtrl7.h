#pragma once


// CMyTabCtrl7

class CMyTabCtrl7 : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyTabCtrl7)

public:
	CMyTabCtrl7();
	virtual ~CMyTabCtrl7();
	void InserTab(DWORD dwCount, ...); //����ѡ�
	void AddDlg(DWORD dwCount, ...); //���ӶԻ���
	void SetSelAndShow(int nSec);

protected:
	DECLARE_MESSAGE_MAP()
public:
	CDialogEx* m_Dia[20];
	DWORD m_dwCount; //ѡ����� 
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
};


