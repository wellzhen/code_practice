#pragma once


// CPowerDialog �Ի���

class CPowerDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPowerDialog)

public:
	CPowerDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPowerDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_POWER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonPowerOff();
	afx_msg void OnBnClickedButtonRestart();
	afx_msg void OnBnClickedButtonLogout();
	afx_msg void OnBnClickedButtonSleep();
	afx_msg void OnBnClickedButtonLock();
	afx_msg void OnBnClickedButtonRest();
	afx_msg void OnBnClickedButtonHotKey();
//	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
