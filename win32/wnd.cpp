#include <Windows.h>
#include <tchar.h>
#include <stdio.h>




int WINAPI  _tWinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPTSTR cmdLine, INT nShow)
{
	//�õ���������
	HWND hWnd = GetDesktopWindow();
	//�õ���Ļ�ϵĵ�һ���Ӵ���
	hWnd = GetWindow(hWnd, GW_CHILD);
	TCHAR  szName[266] = { 0 };
	
	//ѭ���õ����Ӵ���

	while (hWnd != NULL) {
		memset(szName, 0, 266);
		GetWindowText(hWnd, szName, 266);
		//printf("%s \n", szName);
		OutputDebugString((LPCWSTR)szName);
		OutputDebugString(TEXT("\n"));
		hWnd = GetNextWindow(hWnd, GW_HWNDNEXT);
	}



	return 0;
}
