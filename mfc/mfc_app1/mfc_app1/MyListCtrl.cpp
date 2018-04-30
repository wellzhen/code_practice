// MyListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "mfc_app1.h"
#include "MyListCtrl.h"


// CMyListCtrl

IMPLEMENT_DYNAMIC(CMyListCtrl, CListCtrl)

CMyListCtrl::CMyListCtrl()
{

}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CMyListCtrl::OnNMClick)
END_MESSAGE_MAP()



// CMyListCtrl 消息处理程序




void CMyListCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	POSITION ps;
	int nIndex;
	ps =GetFirstSelectedItemPosition();
	nIndex = GetNextSelectedItem(ps);//nIndex为选中的列表项Item值 
	*pResult = 0;
}
