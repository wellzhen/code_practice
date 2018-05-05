#pragma once
#include "WndList.h"


// CWndDialog 对话框

class CWndDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CWndDialog)

public:
	CWndDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWndDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CWndList m_WndList;
	INT m_pid;
};
