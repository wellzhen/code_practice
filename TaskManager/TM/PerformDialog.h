#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CPerformDialog �Ի���

class CPerformDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPerformDialog)

public:
	CPerformDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPerformDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PERFORMANCE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void UpdatePerformanceData();
	INT GetCpuUsage();
	double FILETIME2Double(const _FILETIME& fileTime);
	CProgressCtrl m_Progress_MemoryLoad;
	CStatic m_Static_TotalPhys;
	CStatic m_static_AvailPhys;
	CStatic m_Static_TotalPageFile;
	CStatic m_Static_AvailPageFile;
	CStatic m_Static_TotalVirtual;
	CStatic m_Static_AvailVirtual;
	CStatic m_Static_MemoryLoad;
	CProgressCtrl m_Progress_CpuUsage;
	CStatic m_Static_CpuUsage;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
