#pragma once
#include "ProcessList.h"


// CProcessDialog �Ի���

class CProcessDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CProcessDialog)

public:
	CProcessDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProcessDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PROCESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CProcessList m_ProcessList;
	virtual BOOL OnInitDialog();
};
