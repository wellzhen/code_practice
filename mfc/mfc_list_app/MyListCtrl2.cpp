// MyListCtrl2.cpp : ʵ���ļ�
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



// CMyListCtrl2 ��Ϣ�������




void CMyListCtrl2::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(L"Ŷ");
	*pResult = 0;
}
