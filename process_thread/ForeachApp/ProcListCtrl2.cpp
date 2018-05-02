// ProcListCtrl2.cpp : 实现文件
//

#include "stdafx.h"
#include "ForeachApp.h"
#include "ProcListCtrl2.h"


// CProcListCtrl2

IMPLEMENT_DYNAMIC(CProcListCtrl2, CListCtrl)

CProcListCtrl2::CProcListCtrl2()
{

}

CProcListCtrl2::~CProcListCtrl2()
{
}

void CProcListCtrl2::InsertColumnCustom(DWORD dwCount, ...)
{
	//设置扩展样式
	SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	//获取尺寸
	CRect rc;
	GetClientRect(&rc);
	int nWidth = int(rc.Width() / dwCount);

	//插入数据
	va_list list;
	va_start(list, dwCount);
	for (DWORD i = 0; i < dwCount; i++) {
		WCHAR* title = va_arg(list, WCHAR*);
		InsertColumn(i, title, 0, nWidth);
	}
	ShowWindow(SW_SHOW);
}

void CProcListCtrl2::InsertItemCustom(DWORD dwCount, ...)
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


BEGIN_MESSAGE_MAP(CProcListCtrl2, CListCtrl)
END_MESSAGE_MAP()



// CProcListCtrl2 消息处理程序


