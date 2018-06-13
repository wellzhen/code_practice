// DLL_TEST.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <Windows.h>

void AlertBox()
{
	MessageBox(0, L"AlertBox v3 Hello", L"AlertBox", 0);
}

void AlertBoxEnd()
{
	MessageBox(0, L"AlertBox v3 End", L"AlertBox", 0);
}

