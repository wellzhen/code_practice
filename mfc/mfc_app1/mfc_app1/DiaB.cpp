// DiaB.cpp : 实现文件
//

#include "stdafx.h"
#include "mfc_app1.h"
#include "DiaB.h"
#include "afxdialogex.h"


// CDiaB 对话框

IMPLEMENT_DYNAMIC(CDiaB, CDialogEx)

CDiaB::CDiaB(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CDiaB::~CDiaB()
{
}

void CDiaB::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDiaB, CDialogEx)
END_MESSAGE_MAP()


// CDiaB 消息处理程序
