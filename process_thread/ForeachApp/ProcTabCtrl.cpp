// ProcTabCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "ForeachApp.h"
#include "ProcTabCtrl.h"


// CProcTabCtrl

IMPLEMENT_DYNAMIC(CProcTabCtrl, CTabCtrl)

CProcTabCtrl::CProcTabCtrl()
{

}

CProcTabCtrl::~CProcTabCtrl()
{
}

void CProcTabCtrl::InsertItemCustom(DWORD dwCount, ...)
{
	va_list list;
	va_start(list, dwCount);

	for (DWORD i = 0; i < dwCount; i++) {
		WCHAR* tabTitle = va_arg(list, WCHAR*);
		InsertItem(i, tabTitle);
	}
	va_end(list);

	m_dwTabCount = dwCount;
}

void CProcTabCtrl::InsertDialogCustom(DWORD dwCount, ...)
{
	va_list list;
	va_start(list, dwCount);
	for (DWORD i = 0; i < dwCount; i++) {
		UINT nID = va_arg(list, UINT);
		m_Dialog[i] = va_arg(list, CDialogEx*);
		m_Dialog[i]->Create(nID, this);
		//控制大小
		CRect rc;
		GetClientRect(&rc);
		rc.DeflateRect(2, 32, 2, 2);
		m_Dialog[i]->MoveWindow(rc);
		
		if (i == 0) {
			m_Dialog[i]->ShowWindow(SW_SHOW);
		}
		else {
			m_Dialog[i]->ShowWindow(SW_HIDE);
		}
	}
	va_end(list);
	M_dwDialogCout = dwCount;
}

void CProcTabCtrl::ShowTabDialog(INT nIndex)
{
	for (INT i = 0; i < m_dwTabCount; i++) {
		if (i == nIndex) {
			m_Dialog[i]->ShowWindow(SW_SHOW);
		}
		else {
			m_Dialog[i]->ShowWindow(SW_HIDE);
		}
	}
}



BEGIN_MESSAGE_MAP(CProcTabCtrl, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CProcTabCtrl::OnTcnSelchange)
END_MESSAGE_MAP()



// CProcTabCtrl 消息处理程序




void CProcTabCtrl::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int  nIndex = GetCurSel();
	ShowTabDialog(nIndex);


	*pResult = 0;
}
