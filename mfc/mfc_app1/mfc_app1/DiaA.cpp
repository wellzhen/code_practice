// DiaA.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfc_app1.h"
#include "DiaA.h"
#include "afxdialogex.h"


// CDiaA �Ի���

IMPLEMENT_DYNAMIC(CDiaA, CDialogEx)

CDiaA::CDiaA(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CDiaA::~CDiaA()
{
}

void CDiaA::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
}


BEGIN_MESSAGE_MAP(CDiaA, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDiaA::OnClickedButton1)
END_MESSAGE_MAP()


// CDiaA ��Ϣ�������


BOOL CDiaA::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ʼ��List
	//list style
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	m_List.InsertColumn(0, L"���", 0, 50);
	m_List.InsertColumn(1, L"Ʒ��", 0, 50);
	m_List.InsertColumn(2, L"��ɫ", 0, 50);
	m_List.InsertColumn(3, L"�۸�", 0, 50);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CDiaA::OnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_List.InsertItem(0, L"1");
	m_List.SetItemText(0, 1, L"Dell");
	m_List.SetItemText(0, 2, L"Red");
	m_List.SetItemText(0, 3, L"7199");
}
