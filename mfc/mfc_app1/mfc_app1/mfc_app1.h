
// mfc_app1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cmfc_app1App: 
// �йش����ʵ�֣������ mfc_app1.cpp
//

class Cmfc_app1App : public CWinApp
{
public:
	Cmfc_app1App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cmfc_app1App theApp;