
// LoadPE.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLoadPEApp: 
// �йش����ʵ�֣������ LoadPE.cpp
//

class CLoadPEApp : public CWinApp
{
public:
	CLoadPEApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLoadPEApp theApp;