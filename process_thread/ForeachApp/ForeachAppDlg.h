
// ForeachAppDlg.h : ͷ�ļ�
//

#pragma once
#include "ProcTabCtrl.h"


// CForeachAppDlg �Ի���
class CForeachAppDlg : public CDialogEx
{
// ����
public:
	CForeachAppDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FOREACHAPP_DIALOG };
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
	CProcTabCtrl m_ProcTabCtrl;
};
