// DiaA11.cpp : 实现文件
//

#include "stdafx.h"
#include "mfc_app.h"
#include "DiaA11.h"
#include "afxdialogex.h"


// CDiaA11 对话框

IMPLEMENT_DYNAMIC(CDiaA11, CDialogEx)

CDiaA11::CDiaA11(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CDiaA11::~CDiaA11()
{
}

void CDiaA11::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDiaA11, CDialogEx)
END_MESSAGE_MAP()


// CDiaA11 消息处理程序
