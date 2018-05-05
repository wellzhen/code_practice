// TabMain.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TM.h"
#include "TabMain.h"



// CTabMain

IMPLEMENT_DYNAMIC(CTabMain, CTabCtrl)

CTabMain::CTabMain()
{

}

CTabMain::~CTabMain()
{
}

void CTabMain::InsertItemCustom(DWORD dwCount, ...)
{
	va_list list;
	va_start(list, dwCount);

	for (DWORD i = 0; i < dwCount; i++) {
		WCHAR* title = va_arg(list, WCHAR*);
		InsertItem(i, title);
	}
	va_end(list);
}

void CTabMain::AddDialogCustom(DWORD dwCount, ...)
{
	va_list list;
	va_start(list, dwCount);
	//��ȡ�ߴ�
	CRect rc;
	GetClientRect(&rc);
	rc.DeflateRect(2, 23, 2, 2);
	for (DWORD i = 0; i < dwCount; i++) {
		UINT IDD = va_arg(list, UINT); //��ԴID
		m_Dialog[i] = va_arg(list, CDialogEx *);
		m_Dialog[i]->Create(IDD, this);
		m_Dialog[i]->MoveWindow(&rc);
	}
	va_end(list);

	m_dwDialogCount = dwCount;
	return;
}

void CTabMain::ShowDialogCustom(INT nIndex)
{
	for (DWORD i = 0; i < m_dwDialogCount; i++) {
		if (i == nIndex) {
			m_Dialog[i]->ShowWindow(SW_SHOW);
		}
		else {
			m_Dialog[i]->ShowWindow(SW_HIDE);
		}
	}

	return;
}

BEGIN_MESSAGE_MAP(CTabMain, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CTabMain::OnTcnSelchange)
END_MESSAGE_MAP()



// CTabMain ��Ϣ�������




void CTabMain::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	//���Tab��ǩʱ�л�ҳ��
	int nNum = GetCurSel();
	if (nNum > m_dwDialogCount - 1) {
		MessageBox(L"��ǰ��ǩ����δ����");
		return;
	}

	for (int i = 0; i < m_dwDialogCount; i++) {
		if (nNum == i) {
			m_Dialog[i]->ShowWindow(SW_SHOW);
		}
		else {
			m_Dialog[i]->ShowWindow(SW_HIDE);
		}
	}
	
}
