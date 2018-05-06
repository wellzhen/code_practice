#pragma once
#include "ModuleList.h"


// CModuleDialog 对话框

class CModuleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CModuleDialog)

public:
	CModuleDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CModuleDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MODULE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	CModuleList m_ModuleList;
	INT m_pid;
	virtual BOOL OnInitDialog();
protected:
	afx_msg LRESULT OnPidChoosed(WPARAM wParam, LPARAM lParam);
};
