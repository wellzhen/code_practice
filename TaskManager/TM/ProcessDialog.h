#pragma once
#include "ProcessList.h"


// CProcessDialog 对话框

class CProcessDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CProcessDialog)

public:
	CProcessDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProcessDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PROCESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CProcessList m_ProcessList;
	virtual BOOL OnInitDialog();
};
