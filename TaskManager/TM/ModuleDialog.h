#pragma once
#include "ModuleList.h"


// CModuleDialog �Ի���

class CModuleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CModuleDialog)

public:
	CModuleDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CModuleDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MODULE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	CModuleList m_ModuleList;
	INT m_pid;
	virtual BOOL OnInitDialog();
protected:
	afx_msg LRESULT OnPidChoosed(WPARAM wParam, LPARAM lParam);
};
