
// mfc_listApp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cmfc_listAppApp: 
// �йش����ʵ�֣������ mfc_listApp.cpp
//

class Cmfc_listAppApp : public CWinApp
{
public:
	Cmfc_listAppApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cmfc_listAppApp theApp;