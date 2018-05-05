// WndDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "TM.h"
#include "WndDialog.h"
#include "afxdialogex.h"



// CWndDialog 对话框

IMPLEMENT_DYNAMIC(CWndDialog, CDialogEx)

CWndDialog::CWndDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_WND, pParent)
{

}

CWndDialog::~CWndDialog()
{
}

void CWndDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_WND, m_WndList);
}


BEGIN_MESSAGE_MAP(CWndDialog, CDialogEx)
END_MESSAGE_MAP()


// CWndDialog 消息处理程序


BOOL CWndDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//初始化窗口列表控件
	m_WndList.InsertColumnCustom(2, 0.7, L"窗口名称", 0.3, L"状态");
	//得到桌面窗口
	HWND  hWnd = ::GetDesktopWindow();
	//得到屏幕上的第一个子窗口
	hWnd = ::GetWindow(hWnd, GW_CHILD);
	WCHAR szName[266] = { 0 };
	//循环获取子窗口
	while (hWnd != NULL) {
		memset(szName, 0, sizeof(szName));
		::GetWindowText(hWnd, szName, 266);
		if (wcslen(szName) != 0) {
			if (::IsWindowVisible(hWnd)) {
				m_WndList.InsertItemCustom(2, szName, L"");
			}
			else {
				m_WndList.InsertItemCustom(2, szName, L"不可见");
			}
			
		}
		
		hWnd = ::GetNextWindow(hWnd, GW_HWNDNEXT);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
