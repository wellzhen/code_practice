
// mfc_02.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "MyDialog.h"   //yz


// Cmfc_02App: 
// �йش����ʵ�֣������ mfc_02.cpp
//

class Cmfc_02App : public CWinApp
{
public:
	Cmfc_02App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cmfc_02App theApp;