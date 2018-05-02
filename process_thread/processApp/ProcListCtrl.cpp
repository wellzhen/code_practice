// ProcListCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "processApp.h"
#include "ProcListCtrl.h"


// CProcListCtrl

IMPLEMENT_DYNAMIC(CProcListCtrl, CListCtrl)

CProcListCtrl::CProcListCtrl()
{

}

CProcListCtrl::~CProcListCtrl()
{
}

void CProcListCtrl::InsertColumnCustom(DWORD dwCount, ...)
{
	//������չ��ʽ
	SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	//��ȡ�ߴ�
	CRect rc;
	GetClientRect(&rc);
	int nWidth = int(rc.Width() / dwCount);

	//��������
	va_list list;
	va_start(list, dwCount);
	for (DWORD i = 0; i < dwCount; i++) {
		WCHAR* title = va_arg(list, WCHAR*);
		InsertColumn(i, title, 0, nWidth);
	}
	ShowWindow(SW_SHOW);
}

void CProcListCtrl::InsertItemCustom(DWORD dwCount, ...)
{
	va_list list;
	va_start(list, dwCount);
	
	InsertItem(0, L"");
	for (DWORD i = 0; i < dwCount; i++) {
		
		CString str = L"";
		if (i == 2) {

			WCHAR*  content = va_arg(list, WCHAR*);
			str.Append(content);
		}
		else {
			DWORD content = va_arg(list, DWORD);
			str.Format(L"%d", content);
		}
		
		SetItemText(0, i, str);
	}
}


BEGIN_MESSAGE_MAP(CProcListCtrl, CListCtrl)
END_MESSAGE_MAP()



// CProcListCtrl ��Ϣ�������


