#pragma once
#include "afxcmn.h"
#include "ProcListCtrl2.h"


// CProcDialog 对话框

class CProcDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CProcDialog)

public:
	CProcDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProcDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PROC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CListCtrl m_ProcList;
	virtual BOOL OnInitDialog();
	CProcListCtrl2 m_ProcList;
};
