#include <Windows.h>
#include <tchar.h>
#include <stdio.h>




int WINAPI  _tWinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPTSTR cmdLine, INT nShow)
{
	//得到窗口桌面
	HWND hWnd = GetDesktopWindow();
	//得到屏幕上的第一个子窗口
	hWnd = GetWindow(hWnd, GW_CHILD);
	TCHAR  szName[266] = { 0 };
	
	//循环得到的子窗口

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
