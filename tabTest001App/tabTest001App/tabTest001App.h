
// tabTest001App.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CtabTest001AppApp: 
// �йش����ʵ�֣������ tabTest001App.cpp
//

class CtabTest001AppApp : public CWinApp
{
public:
	CtabTest001AppApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CtabTest001AppApp theApp;