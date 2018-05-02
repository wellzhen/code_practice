
// 遍历进程至ListCtrl.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// C遍历进程至ListCtrlApp: 
// 有关此类的实现，请参阅 遍历进程至ListCtrl.cpp
//

class C遍历进程至ListCtrlApp : public CWinApp
{
public:
	C遍历进程至ListCtrlApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern C遍历进程至ListCtrlApp theApp;