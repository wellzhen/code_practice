#pragma once
#include "BaseListCtrl.h"


// CThreadDialog �Ի���

class CThreadDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CThreadDialog)

public:
	CThreadDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CThreadDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_THREAD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CBaseListCtrl m_ThreadList;
	virtual BOOL OnInitDialog();
};
