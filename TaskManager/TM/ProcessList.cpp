// ProcessList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TM.h"
#include "ProcessList.h"
#include "ThreadDialog.h"


// CProcessList

IMPLEMENT_DYNAMIC(CProcessList, CListCtrl)

CProcessList::CProcessList()
{

}

CProcessList::~CProcessList()
{
}


BEGIN_MESSAGE_MAP(CProcessList, CListCtrl)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CProcessList::OnNMRClick)
	ON_COMMAND(ID_SHOWTHREAD, &CProcessList::OnShowthread)
	ON_COMMAND(ID_SHOW_MODULE, &CProcessList::OnShowModule)
	ON_COMMAND(ID_SHOW_HEAP, &CProcessList::OnShowHeap)
	ON_COMMAND(ID_TERMINATE_PROCESS, &CProcessList::OnTerminateProcess)
END_MESSAGE_MAP()



// CProcessList ��Ϣ�������




void CProcessList::InsertColumnCustom(DWORD dwCount, ...)
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

		if (nWidth < 10) {
			MessageBox(L"Warning: �б�Ŀ��̫С��\n");
		}
		
		WCHAR* wStr = va_arg(list, WCHAR*);

		InsertColumn(i, wStr, 0, nWidth);
		nUsedWidth += nWidth;
	}
	va_end(list);

	return;
}


void CProcessList::InsertItemCustom(DWORD dwCount, ...)
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


void CProcessList::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
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
		VERIFY(menu.LoadMenu(IDR_MENU1));           //������������1�ж����MENU���ļ�����  
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
		m_nChoosedPid = _wtoi(strPID);
		
		
	}
}


void CProcessList::OnShowthread()
{
	// TODO: �ڴ���������������
	//CString strPID;
	//strPID.Format(L"��ʾ�߳�%d", m_nChoosedPid);
	//MessageBox(strPID);
	//��ʾ�̶߳Ի���
	
	m_pThreadDialog = new CThreadDialog();
	m_pThreadDialog->m_pid = m_nChoosedPid;
	m_pThreadDialog->DoModal();
	//m_pThreadDialog->Create(IDD_DIALOG_THREAD, this);
	//m_pThreadDialog->ShowWindow(SW_SHOW);
} 


void CProcessList::OnShowModule()
{
	// TODO: �ڴ���������������
	//CString strPID;
	//strPID.Format(L"��ʾģ���б�%d", m_nChoosedPid);
	//MessageBox(strPID);

	m_pModuleDialog = new CModuleDialog();
	m_pModuleDialog->m_pid = m_nChoosedPid;
	m_pModuleDialog->DoModal();
}


void CProcessList::OnShowHeap()
{
	// TODO: �ڴ���������������
	m_pHeapDialog = new CHeapDialog();
	m_pHeapDialog->m_pid = m_nChoosedPid;
	m_pHeapDialog->DoModal();
}


void CProcessList::OnTerminateProcess()
{
	// TODO: �ڴ���������������
	HANDLE  hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, m_nChoosedPid);
	if (hProcess == INVALID_HANDLE_VALUE) {
		MessageBox(L"�޷���ȡ���̾��");
		return;
	}
	if (!TerminateProcess(hProcess, 0)) {
		MessageBox(L"��ֹ����ʧ��");
	}
	
}
