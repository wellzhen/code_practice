
// calcDlg.h : 头文件
//

#pragma once


// calcDlg 对话框
class calcDlg : public CDialogEx
{
// 构造
public:
	calcDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_CALC_DIALOG };
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
	afx_msg void OnBnClickedButton6();
	CString m_string;
	afx_msg void OnClickedButton26_0();
	afx_msg void OnClickedButton21_1();
	afx_msg void OnClickedButton22_2();
	afx_msg void OnClickedButton23_3();
	afx_msg void OnClickedButton16_4();
	afx_msg void OnClickedButton17_5();
	afx_msg void OnClickedButton18_6();
	afx_msg void OnClickedButton11_7();
	afx_msg void OnClickedButton12_8();
	afx_msg void OnClickedButton13_9();
	afx_msg void OnClickedButton27_dot();
	afx_msg void OnClickedButton28_add();
	afx_msg void OnClickedButton24_sub();
	afx_msg void OnClickedButton19_multi();
	afx_msg void OnClickedButton14_div();
	afx_msg void OnClickedButton15_model();
	afx_msg void OnClickedButton25_result();
	
	afx_msg void OnClickedButton1_clear();
	CString m_strResult;
};
