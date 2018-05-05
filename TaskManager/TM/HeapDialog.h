#pragma once
#include "HeapList.h"


// CHeapDialog �Ի���

class CHeapDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHeapDialog)

public:
	CHeapDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHeapDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HEAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CHeapList m_HeapList;
	INT m_pid;
	virtual BOOL OnInitDialog();
};
