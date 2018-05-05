#pragma once
#include "HeapList.h"


// CHeapDialog 对话框

class CHeapDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHeapDialog)

public:
	CHeapDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHeapDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HEAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CHeapList m_HeapList;
	INT m_pid;
	virtual BOOL OnInitDialog();
};
