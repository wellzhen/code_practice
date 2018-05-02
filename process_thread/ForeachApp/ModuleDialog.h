#pragma once
#include "ModuleListCtrl2.h"


// CModuleDialog 对话框

class CModuleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CModuleDialog)

public:
	CModuleDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CModuleDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MODUlE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CModuleListCtrl2 m_ModuleList;
	virtual BOOL OnInitDialog();
};
