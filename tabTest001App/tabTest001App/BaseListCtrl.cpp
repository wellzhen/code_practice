// BaseListCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "tabTest001App.h"
#include "BaseListCtrl.h"


// CBaseListCtrl

IMPLEMENT_DYNAMIC(CBaseListCtrl, CListCtrl)

CBaseListCtrl::CBaseListCtrl()
{

}

CBaseListCtrl::~CBaseListCtrl()
{
}


BEGIN_MESSAGE_MAP(CBaseListCtrl, CListCtrl)
END_MESSAGE_MAP()



// CBaseListCtrl ��Ϣ�������


void CBaseListCtrl::InsertColumnCustom(DWORD dwCount, ...)
{
	//������չ��ʽ
	SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	//��ȡ�ߴ�
	CRect rc;
	GetClientRect(&rc);
	INT nTotalWidth = (INT)rc.Width();
	INT nUsedWidth = 0;
	INT nWidth; //ÿ��column�Ŀ��
	va_list list;
	va_start(list, dwCount);
	for (DWORD i = 0; i < dwCount; i++) {
		DOUBLE  fWidthRate = va_arg(list, DOUBLE);
		if (i != dwCount - 1) {
			nWidth = (INT)(nTotalWidth * fWidthRate);
		}
		else {
			nWidth = nTotalWidth - nUsedWidth; //����п�ʹ��ʣ������п��
		}

		if (nWidth < 5) {
			MessageBox(L"Warning: ���б�Ŀ��̫С��\n");
		}

		WCHAR* wStr = va_arg(list, WCHAR*);

		InsertColumn(i, wStr, 0, nWidth);
		nUsedWidth += nWidth;
	}
	va_end(list);

	return;
}


void CBaseListCtrl::InsertItemCustom(DWORD dwCount, ...)
{
	va_list list;
	va_start(list, dwCount);
	//����λ�ò���һ��
	InsertItem(0, L"");
	for (DWORD i = 0; i < dwCount; i++) {
		WCHAR* wStr = va_arg(list, WCHAR*);
		SetItemText(0, i, wStr);
	}

	va_end(list);
	return;
}