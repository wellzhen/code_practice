
// tabTest001AppDlg.h : ͷ�ļ�
//

#pragma once
#include "MainTabCtrl.h"


// CtabTest001AppDlg �Ի���
class CtabTest001AppDlg : public CDialogEx
{
// ����
public:
	CtabTest001AppDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TABTEST001APP_DIALOG };
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
	afx_msg void OnBnClickedOk2();
	CMainTabCtrl m_MainTabCtrl;
};
