#pragma once
#include "afxcmn.h"


// CDiaA �Ի���

class CDiaA : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaA)

public:
	CDiaA(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDiaA();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedButton1();
};
