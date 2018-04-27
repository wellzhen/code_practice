
// MFC_ctrlDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMFC_ctrlDlg �Ի���
class CMFC_ctrlDlg : public CDialogEx
{
// ����
public:
	CMFC_ctrlDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_CTRL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnClickedButton1();
//	BOOL m_nCheck_male;
	BOOL m_check_piano;
	afx_msg void OnClickedCheck1();
	CButton m_basketball;
	afx_msg void OnClickedCheck5_baskball();
	CEdit m_edit01;
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	CString m_edit03;
	CString m_edit02;
	CProgressCtrl m_proress;
	afx_msg void OnCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnOutofmemoryProgress1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnReleasedcaptureProgress1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnThemechangedProgress1(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_sliderbar;
public:
	CBrush m_brBk;
};
