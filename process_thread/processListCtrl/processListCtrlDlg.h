
// ����������ListCtrlDlg.h : ͷ�ļ�
//

#pragma once
#include "MyListCtrl.h"


// C����������ListCtrlDlg �Ի���
class C����������ListCtrlDlg : public CDialogEx
{
// ����
public:
	C����������ListCtrlDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LISTCTRL_DIALOG };
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
	CMyListCtrl m_objList;
};
