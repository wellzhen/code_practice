
// mfc_app1Dlg.h : ͷ�ļ�
//

#pragma once
#include "MyTabCtrl.h"


// Cmfc_app1Dlg �Ի���
class Cmfc_app1Dlg : public CDialogEx
{
// ����
public:
	Cmfc_app1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_APP1_DIALOG };
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
	CMyTabCtrl m_MyTab;
};
