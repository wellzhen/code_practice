#pragma once
#include "ModuleListCtrl2.h"


// CModuleDialog �Ի���

class CModuleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CModuleDialog)

public:
	CModuleDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CModuleDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MODUlE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CModuleListCtrl2 m_ModuleList;
	virtual BOOL OnInitDialog();
};
