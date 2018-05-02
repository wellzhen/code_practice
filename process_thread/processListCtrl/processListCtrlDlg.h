
// 遍历进程至ListCtrlDlg.h : 头文件
//

#pragma once
#include "MyListCtrl.h"


// C遍历进程至ListCtrlDlg 对话框
class C遍历进程至ListCtrlDlg : public CDialogEx
{
// 构造
public:
	C遍历进程至ListCtrlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LISTCTRL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMyListCtrl m_objList;
};
