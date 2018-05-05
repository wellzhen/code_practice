// PerformDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "TM.h"
#include "PerformDialog.h"
#include "afxdialogex.h"


// CPerformDialog 对话框

IMPLEMENT_DYNAMIC(CPerformDialog, CDialogEx)

CPerformDialog::CPerformDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PERFORMANCE, pParent)
{

}

CPerformDialog::~CPerformDialog()
{
}

void CPerformDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress_MemoryLoad);
	DDX_Control(pDX, IDC_STATIC_TOTAL_PHYS, m_Static_TotalPhys);
	DDX_Control(pDX, IDC_STATIC_AVAIL_PHYS, m_static_AvailPhys);
	DDX_Control(pDX, IDC_STATIC_TOTAL_PAGE_FILE, m_Static_TotalPageFile);
	DDX_Control(pDX, IDC_STATIC_AVAIL_PAGE_FILE, m_Static_AvailPageFile);
	DDX_Control(pDX, IDC_STATIC_TOTAL_VIRTUAL, m_Static_TotalVirtual);
	DDX_Control(pDX, IDC_STATIC_AVAIL_VIRTUAL, m_Static_AvailVirtual);
	DDX_Control(pDX, IDC_STATIC_MEMORY_LOAD, m_Static_MemoryLoad);
	DDX_Control(pDX, IDC_PROGRESS_USAGE, m_Progress_CpuUsage);
	DDX_Control(pDX, IDC_STATIC_CPU_USAGE, m_Static_CpuUsage);
}


BEGIN_MESSAGE_MAP(CPerformDialog, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CPerformDialog 消息处理程序


BOOL CPerformDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdatePerformanceData();
	SetTimer(100, 10000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CPerformDialog::UpdatePerformanceData()
{
	MEMORYSTATUS  memStatus;
	GlobalMemoryStatus(&memStatus);


	//显示数据
	DWORD m = 1024 * 1024;
	CString str;

	m_Progress_MemoryLoad.SetPos(memStatus.dwMemoryLoad);
	str.Format(L"%d / 100", memStatus.dwMemoryLoad);
	m_Static_MemoryLoad.SetWindowTextW(str);
	str.Format(L"%d M", memStatus.dwTotalPhys / m);

	m_Static_TotalPhys.SetWindowTextW(str);
	str.Format(L"%d M", memStatus.dwAvailPhys / m);
	m_static_AvailPhys.SetWindowTextW(str);
	str.Format(L"%d M", memStatus.dwTotalPageFile / m);
	m_Static_TotalPageFile.SetWindowTextW(str);
	str.Format(L"%d M", memStatus.dwAvailPageFile / m);
	m_Static_AvailPageFile.SetWindowTextW(str);
	str.Format(L"%d M", memStatus.dwTotalVirtual / m);
	m_Static_TotalVirtual.SetWindowTextW(str);
	str.Format(L"%d M", memStatus.dwAvailVirtual / m);
	m_Static_AvailVirtual.SetWindowTextW(str);


	//CPU占用率
	INT cpuUsage = GetCpuUsage();
	m_Progress_CpuUsage.SetPos(cpuUsage);
	str.Format(L"%d / 100", cpuUsage);
	m_Static_CpuUsage.SetWindowTextW(str);
}


INT CPerformDialog::GetCpuUsage()
{
	//		    空闲事件  内核事件   用户事件
	_FILETIME  idleTime, kernelTime, userTime;
	//获取时间
	GetSystemTimes(&idleTime, &kernelTime, &userTime);
	//等待1000毫秒
	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	WaitForSingleObject(hEvent, 1000);
	//获取新的时间
	_FILETIME  newIdleTime, newKernelTime, newUserTime;
	GetSystemTimes(&newIdleTime, &newKernelTime, &newUserTime);
	//将各个时间转换
	double dOldIdleTime = FILETIME2Double(idleTime);
	double dNewIdleTime = FILETIME2Double(newIdleTime);
	double dOldKernelTime = FILETIME2Double(kernelTime);
	double dNewKernelTime = FILETIME2Double(newKernelTime);
	double dOldUserTime = FILETIME2Double(userTime);
	double dNewUserTime = FILETIME2Double(newUserTime);
	//计算出使用率
	return  int(100.0 - (dNewIdleTime - dOldIdleTime) /
		(dNewKernelTime - dOldKernelTime + dNewUserTime - dOldUserTime) * 100.0);
}

double CPerformDialog::FILETIME2Double(const _FILETIME& fileTime)
{
	return double(fileTime.dwHighDateTime*4.294967296e9) + double(fileTime.dwLowDateTime);

}


void CPerformDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 100) {
		UpdatePerformanceData();
	}
	
	CDialogEx::OnTimer(nIDEvent);
}
