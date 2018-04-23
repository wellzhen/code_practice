#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
// 函数名要加w, 或者Lpcm 为char * 
int APIENTRY wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreINstance,
	LPTSTR Lpcmd, // wchar_t * 
	int mCmdShow)
{	
	CHAR  buf[] = "好";   //ASCII
	WCHAR  bufw[] = L"好";// UNICODE
	TCHAR  buff[] = TEXT("好的");
	// TCHAR  


	char  buf3[] = "12345";
	int a = atoi(buf3);
	int b = 0;
	sscanf_s(buf3, "%d", &b);

	//数字转str
	int num = 12345;
	double fnum = 3.14;
	char numbuf[100] = {};
	sprintf_s(numbuf, 100, "%d", num);

	OutputDebugString(L"hehe");
	//格式
	//_trace("%s", buf3);

	MessageBox(0, L"好的", L"中国", 0);


	return 0;
}