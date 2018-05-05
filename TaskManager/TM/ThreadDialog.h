#pragma once
#include "ThreadList.h"


// CThreadDialog 对话框

class CThreadDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CThreadDialog)

public:
	CThreadDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CThreadDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_THREAD};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CThreadList m_ThreadList;
	INT m_pid; //自定义
	virtual BOOL OnInitDialog();
};
