
// mfc_app.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cmfc_appApp: 
// �йش����ʵ�֣������ mfc_app.cpp
//

class Cmfc_appApp : public CWinApp
{
public:
	Cmfc_appApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cmfc_appApp theApp;