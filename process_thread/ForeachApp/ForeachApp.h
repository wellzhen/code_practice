
// ForeachApp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CForeachAppApp: 
// �йش����ʵ�֣������ ForeachApp.cpp
//

class CForeachAppApp : public CWinApp
{
public:
	CForeachAppApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CForeachAppApp theApp;