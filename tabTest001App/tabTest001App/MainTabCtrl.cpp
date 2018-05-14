// MainTabCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "tabTest001App.h"
#include "MainTabCtrl.h"


// CMainTabCtrl

IMPLEMENT_DYNAMIC(CMainTabCtrl, CTabCtrl)

CMainTabCtrl::CMainTabCtrl()
{

}

CMainTabCtrl::~CMainTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CMainTabCtrl, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CMainTabCtrl::OnTcnSelchange)
END_MESSAGE_MAP()



// CMainTabCtrl 消息处理程序




void CMainTabCtrl::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	INT nNum = GetCurSel();
	ShowDialogCustom(nNum);
	
}


void CMainTabCtrl::InsertItemCustom(DWORD dwCount, ...)
{
	va_list list;
	va_start(list, dwCount);

	for (DWORD i = 0; i < dwCount; i++) {
		WCHAR* title = va_arg(list, WCHAR*);
		InsertItem(i, title);
	}
	va_end(list);
}

void CMainTabCtrl::AddDialogCustom(DWORD dwCount, ...)
{
	va_list list;
	va_start(list, dwCount);
	//获取尺寸
	CRect rc;
	GetClientRect(&rc);
	rc.DeflateRect(2, 23, 2, 2);
	for (DWORD i = 0; i < dwCount; i++) {
		UINT IDD = va_arg(list, UINT); //资源ID
		m_Dialog[i] = va_arg(list, CDialogEx *);
		m_Dialog[i]->Create(IDD, this);
		m_Dialog[i]->MoveWindow(&rc);
	}
	va_end(list);

	m_dwDlgCount = dwCount;
	return;
}

void CMainTabCtrl::ShowDialogCustom(INT nIndex)
{
	for (DWORD i = 0; i < m_dwDlgCount; i++) {
		if (i == nIndex) {
			m_Dialog[i]->ShowWindow(SW_SHOW);
		}
		else {
			//m_Dialog[i]->ShowWindow(SW_HIDE);
			m_Dialog[i]->EndDialog(IDCANCEL);
		}
	}

	return;
}
