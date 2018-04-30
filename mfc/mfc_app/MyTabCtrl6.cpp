// MyTabCtrl6.cpp : 实现文件
//

#include "stdafx.h"
#include "mfc_app.h"
#include "MyTabCtrl6.h"


// CMyTabCtrl6

IMPLEMENT_DYNAMIC(CMyTabCtrl6, CTabCtrl)

CMyTabCtrl6::CMyTabCtrl6()
{

}

CMyTabCtrl6::~CMyTabCtrl6()
{
}


BEGIN_MESSAGE_MAP(CMyTabCtrl6, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CMyTabCtrl6::OnTcnSelchange)
END_MESSAGE_MAP()



// CMyTabCtrl6 消息处理程序




void CMyTabCtrl6::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int nNum = GetCurSel();
	m_Dia[0]->ShowWindow(SW_HIDE);
	m_Dia[1]->ShowWindow(SW_HIDE);
	m_Dia[nNum]->ShowWindow(SW_SHOW);

	*pResult = 0;
}
