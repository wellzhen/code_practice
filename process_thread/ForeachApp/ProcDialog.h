#pragma once
#include "afxcmn.h"
#include "ProcListCtrl2.h"


// CProcDialog �Ի���

class CProcDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CProcDialog)

public:
	CProcDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProcDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PROC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	CListCtrl m_ProcList;
	virtual BOOL OnInitDialog();
	CProcListCtrl2 m_ProcList;
};
