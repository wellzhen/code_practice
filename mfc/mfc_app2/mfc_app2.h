
// mfc_app2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cmfc_app2App: 
// �йش����ʵ�֣������ mfc_app2.cpp
//

class Cmfc_app2App : public CWinApp
{
public:
	Cmfc_app2App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cmfc_app2App theApp;