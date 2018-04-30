// MyListCtrl2.cpp : 实现文件
//

#include "stdafx.h"
#include "mfc_list_app.h"
#include "MyListCtrl2.h"


// CMyListCtrl2

IMPLEMENT_DYNAMIC(CMyListCtrl2, CListCtrl)

CMyListCtrl2::CMyListCtrl2()
{

}

CMyListCtrl2::~CMyListCtrl2()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl2, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CMyListCtrl2::OnNMClick)
END_MESSAGE_MAP()



// CMyListCtrl2 消息处理程序




void CMyListCtrl2::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(L"哦");
	*pResult = 0;
}
