// MyTabCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfc_app1.h"
#include "MyTabCtrl.h"


// CMyTabCtrl

IMPLEMENT_DYNAMIC(CMyTabCtrl, CTabCtrl)

CMyTabCtrl::CMyTabCtrl()
{

}

CMyTabCtrl::~CMyTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyTabCtrl, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CMyTabCtrl::OnTcnSelchange)
END_MESSAGE_MAP()



// CMyTabCtrl ��Ϣ�������




void CMyTabCtrl::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nNum = GetCurSel();
	m_Dia[0]->ShowWindow(SW_HIDE);
	m_Dia[1]->ShowWindow(SW_HIDE);
	m_Dia[nNum]->ShowWindow(SW_SHOW);
	*pResult = 0;
}
