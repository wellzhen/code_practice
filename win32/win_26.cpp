#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
// ������Ҫ��w, ����Lpcm Ϊchar * 
int APIENTRY wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreINstance,
	LPTSTR Lpcmd, // wchar_t * 
	int mCmdShow)
{	
	CHAR  buf[] = "��";   //ASCII
	WCHAR  bufw[] = L"��";// UNICODE
	TCHAR  buff[] = TEXT("�õ�");
	// TCHAR  


	char  buf3[] = "12345";
	int a = atoi(buf3);
	int b = 0;
	sscanf_s(buf3, "%d", &b);

	//����תstr
	int num = 12345;
	double fnum = 3.14;
	char numbuf[100] = {};
	sprintf_s(numbuf, 100, "%d", num);

	OutputDebugString(L"hehe");
	//��ʽ
	//_trace("%s", buf3);

	MessageBox(0, L"�õ�", L"�й�", 0);


	return 0;
}