#pragma once
#include "afxwin.h"


// CWhisperDlg �Ի���

class CWhisperDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWhisperDlg)

public:
	CWhisperDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWhisperDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WHISPER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
