// MyTabCtrl7.cpp : 实现文件
//

#include "stdafx.h"
#include "mfc_app2.h"
#include "MyTabCtrl7.h"


// CMyTabCtrl7

IMPLEMENT_DYNAMIC(CMyTabCtrl7, CTabCtrl)

CMyTabCtrl7::CMyTabCtrl7()
{

}

CMyTabCtrl7::~CMyTabCtrl7()
{
}

void CMyTabCtrl7::InserTab(DWORD dwCount, ...)
{
	va_list list;
	va_start(list, dwCount);
	for (DWORD i = 0; i < dwCount; i++) {
		WCHAR* pTabName = va_arg(list, WCHAR*);
		InsertItem(i, pTabName);
	}
	va_end(list);
	m_dwCount = dwCount;
}

void CMyTabCtrl7::AddDlg(DWORD dwCount, ...)
{
	va_list list;
	va_start(list, dwCount);
	for (int i = 0; i < dwCount; i++) {
		UINT uID = va_arg(list, UINT);
		m_Dia[i] = va_arg(list, CDialogEx*);
		m_Dia[i]->Create(uID, this);
	}
	va_end(list);
}

void CMyTabCtrl7::SetSelAndShow(int nSec)
{
	for (int i = 0; i < m_dwCount; i++) {
		CRect rc;
		GetClientRect(rc);
		rc.DeflateRect(2, 23, 2, 2);
		m_Dia[i]->MoveWindow(rc);
		if (i == nSec) {
			m_Dia[i]->ShowWindow(SW_SHOW);
		}
		else {
			m_Dia[i]->ShowWindow(SW_HIDE);
		}
	}
}


BEGIN_MESSAGE_MAP(CMyTabCtrl7, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CMyTabCtrl7::OnTcnSelchange)
END_MESSAGE_MAP()



// CMyTabCtrl7 消息处理程序




void CMyTabCtrl7::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int nNum = GetCurSel();
	SetSelAndShow(nNum);
	*pResult = 0;
}
