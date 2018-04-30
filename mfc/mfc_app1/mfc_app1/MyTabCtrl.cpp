// MyTabCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "mfc_app1.h"
#include "MyTabCtrl.h"


// CMyTabCtrl

IMPLEMENT_DYNAMIC(CMyTabCtrl, CTabCtrl)

CMyTabCtrl::CMyTabCtrl()
{

}

CMyTabCtrl::~CMyTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyTabCtrl, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CMyTabCtrl::OnTcnSelchange)
END_MESSAGE_MAP()



// CMyTabCtrl 消息处理程序




void CMyTabCtrl::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int nNum = GetCurSel();
	m_Dia[0]->ShowWindow(SW_HIDE);
	m_Dia[1]->ShowWindow(SW_HIDE);
	m_Dia[nNum]->ShowWindow(SW_SHOW);
	*pResult = 0;
}
