#pragma once
#include "WndList.h"


// CWndDialog �Ի���

class CWndDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CWndDialog)

public:
	CWndDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWndDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CWndList m_WndList;
	INT m_pid;
};
