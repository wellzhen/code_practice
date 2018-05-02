// ModuleListCtrl2.cpp : 实现文件
//

#include "stdafx.h"
#include "ForeachApp.h"
#include "ModuleListCtrl2.h"


// CModuleListCtrl2

IMPLEMENT_DYNAMIC(CModuleListCtrl2, CListCtrl)

CModuleListCtrl2::CModuleListCtrl2()
{

}

CModuleListCtrl2::~CModuleListCtrl2()
{
}

void CModuleListCtrl2::InsertColumnCustom(DWORD dwCount, ...)
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

void CModuleListCtrl2::InsertItemCustom(DWORD dwCount, ...)
{
	va_list list;
	va_start(list, dwCount);

	InsertItem(0, L"");
	for (DWORD i = 0; i < dwCount; i++) {

		CString str = L"";
		if (i == 1 || i== 2) {

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

BEGIN_MESSAGE_MAP(CModuleListCtrl2, CListCtrl)
END_MESSAGE_MAP()



// CModuleListCtrl2 消息处理程序


