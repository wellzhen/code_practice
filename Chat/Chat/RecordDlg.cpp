// RecordDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chat.h"
#include "RecordDlg.h"
#include "afxdialogex.h"
#include "MainChatDlg.h"


// CRecordDlg �Ի���

IMPLEMENT_DYNAMIC(CRecordDlg, CDialogEx)

CRecordDlg::CRecordDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RECORD_DIALOG, pParent)
{

}

CRecordDlg::~CRecordDlg()
{
}

void CRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RECORD, m_listRecord);
}


BEGIN_MESSAGE_MAP(CRecordDlg, CDialogEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CRecordDlg ��Ϣ�������


BOOL CRecordDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_listRecord.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listRecord.InsertColumn(0, L"������", 0, 50);
	m_listRecord.InsertColumn(1, L"������", 0, 50);
	m_listRecord.InsertColumn(2, L"����", 0, 300);
	UpdateList();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CRecordDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnClose();
}

void CRecordDlg::UpdateList() 
{
	m_listRecord.DeleteAllItems(); 
	CMainChatDlg *pParent = (CMainChatDlg*)GetParent();
	auto &vec = pParent->m_pClient->m_vecMsgRecord;
	DWORD dwCount = vec.size();
	CString  strTemp;
	for (DWORD i = 0; i < dwCount; i++) {
		//���췢��
		strTemp = vec[i].szFrom;
		m_listRecord.InsertItem(i, strTemp.GetBuffer());
		strTemp = vec[i].szTo;
		m_listRecord.SetItemText(i, 1, strTemp.GetBuffer());
		strTemp = vec[i].szConent;
		m_listRecord.SetItemText(i, 2, strTemp.GetBuffer());
	}

} 