// MyDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfc_02.h"
#include "MyDialog.h"
#include "afxdialogex.h"


// CMyDialog �Ի���

IMPLEMENT_DYNAMIC(CMyDialog, CDialogEx)

CMyDialog::CMyDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CMyDialog::~CMyDialog()
{
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyDialog, CDialogEx)
	ON_WM_MOUSEHOVER()
END_MESSAGE_MAP()


// CMyDialog ��Ϣ�������
// add by yz


void CMyDialog::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnMouseHover(nFlags, point);
}
