
// mfc_list_app.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cmfc_list_appApp: 
// �йش����ʵ�֣������ mfc_list_app.cpp
//

class Cmfc_list_appApp : public CWinApp
{
public:
	Cmfc_list_appApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cmfc_list_appApp theApp;