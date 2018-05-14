#pragma once
#include "BaseListCtrl.h"


// CThreadDialog 对话框

class CThreadDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CThreadDialog)

public:
	CThreadDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CThreadDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_THREAD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CBaseListCtrl m_ThreadList;
	virtual BOOL OnInitDialog();
};
