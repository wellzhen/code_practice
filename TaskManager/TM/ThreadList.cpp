// ThreadList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TM.h"
#include "ThreadList.h"


// CThreadList

IMPLEMENT_DYNAMIC(CThreadList, CListCtrl)

CThreadList::CThreadList()
{

}

CThreadList::~CThreadList()
{
}


BEGIN_MESSAGE_MAP(CThreadList, CListCtrl)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CThreadList::OnNMRClick)
	ON_COMMAND(ID_SUSPEND_THREAD, &CThreadList::OnSuspendThread)
	ON_COMMAND(ID_RESUME_THREAD, &CThreadList::OnResumeThread)
	ON_COMMAND(ID_TERMINATE_THREAD, &CThreadList::OnTerminateThread)
END_MESSAGE_MAP()



// CThreadList ��Ϣ�������


void CThreadList::InsertColumnCustom(DWORD dwCount, ...)
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
			MessageBox(L"Warning: �߳��б�Ŀ��̫С��\n");
		}

		WCHAR* wStr = va_arg(list, WCHAR*);

		InsertColumn(i, wStr, 0, nWidth);
		nUsedWidth += nWidth;
	}
	va_end(list);

	return;
}


void CThreadList::InsertItemCustom(DWORD dwCount, ...)
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

void CThreadList::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point(LOWORD(dwPos), HIWORD(dwPos));
		CMenu menu;
		//����̲߳���  
		VERIFY(menu.LoadMenu(IDR_MENU2));           //������������1�ж����MENU���ļ�����  
		CMenu* popup = menu.GetSubMenu(0);
		ASSERT(popup != NULL);
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

		//��������д�����Ҫ��Ϊ�˺���Ĳ���Ϊ׼����  
		//��ȡ�б���ͼ�ؼ��е�һ����ѡ�����λ��    
		POSITION m_pstion = GetFirstSelectedItemPosition();
		//�ú�����ȡ��posָ�����б����������Ȼ��pos����Ϊ��һ��λ�õ�POSITIONֵ  
		INT m_nIndex = GetNextSelectedItem(m_pstion);

		//��ȡPID
		int nColumn = 0; //pid���ڵ���
		CString strPID = GetItemText(m_nIndex, nColumn);
		//MessageBox(strPID);
		m_nChoosedTid = _wtoi(strPID);
	}

}


void CThreadList::OnSuspendThread()
{
	// TODO: �ڴ���������������
	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, false, m_nChoosedTid);
	if (hThread == INVALID_HANDLE_VALUE) {
		MessageBox(L"�޷���ȡ�߳̾��");
		return;
	}
	SuspendThread(hThread);
}


void CThreadList::OnResumeThread()
{
	// TODO: �ڴ���������������
	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, false, m_nChoosedTid);
	if (hThread == INVALID_HANDLE_VALUE) {
		MessageBox(L"�޷���ȡ�߳̾��");
		return;
	}
	ResumeThread(hThread);
}


void CThreadList::OnTerminateThread()
{
	// TODO: �ڴ���������������
	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, false, m_nChoosedTid);
	if (hThread == INVALID_HANDLE_VALUE) {
		MessageBox(L"�޷���ȡ�߳̾��");
		return;
	}
	if (! TerminateThread(hThread, 0)) {
		MessageBox(L"��ֹ�߳�ʧ��");
	}
}
