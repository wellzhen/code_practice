
// MFC_ctrl.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFC_ctrlApp: 
// �йش����ʵ�֣������ MFC_ctrl.cpp
//

class CMFC_ctrlApp : public CWinApp
{
public:
	CMFC_ctrlApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFC_ctrlApp theApp;