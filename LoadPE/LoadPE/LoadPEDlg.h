
// LoadPEDlg.h : ͷ�ļ�
//

#pragma once
#include "afxeditbrowsectrl.h"


// CLoadPEDlg �Ի���
class CLoadPEDlg : public CDialogEx
{
// ����
public:
	CLoadPEDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOADPE_DIALOG };
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
//	CMFCEditBrowseCtrl m_strFileName;
	CString m_strFileName;
	afx_msg void OnClickedBtnOk();
};
