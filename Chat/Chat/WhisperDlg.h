#pragma once
#include "afxwin.h"


// CWhisperDlg 对话框

class CWhisperDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWhisperDlg)

public:
	CWhisperDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWhisperDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WHISPER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strShow;
//	CEdit m_strSend;
	CString m_strSend;
	afx_msg void OnClose();
	afx_msg void OnClickedButtonWhisperSend();
	virtual void OnOK();
	afx_msg void OnBnClickedBtnSendFile();
};
