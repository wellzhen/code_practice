#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>
#include"resource.h" 
#pragma comment(lib, "winmm.lib")

HINSTANCE g_hInstance = NULL;

LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	HDC hdc, hMem;
	PAINTSTRUCT ps;
	TCHAR info[100] = _T("�ȿ�����д����������ѽ");
	HBITMAP  hBitmap;
	static POINT  pt; //�洢�ͻ������

	switch (uMsg) {	
	case WM_CHAR:
	{
		TCHAR  pszDest[100];
		TCHAR  ch = (TCHAR)wParam;
		LRESULT  hr =  StringCchPrintf(pszDest, 100, TEXT("Sound\\Sound_%c.wav"), ch);

		// MessageBox(hWnd, _T("Wsss"), _T("Caption"), MB_OK);
		PlaySound(pszDest , NULL, SND_FILENAME | SND_ASYNC);
		break;

	}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hBitmap = LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
		hMem = CreateCompatibleDC(hdc);
		SelectObject(hMem, hBitmap);
		TextOut(hMem, 0, 100, info, lstrlen(info));
		BitBlt(hdc, 0, 0, pt.x, pt.y, hMem, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE:
		pt.x = LOWORD(lParam);//�ͻ������
		pt.y = HIWORD(lParam);//�ͻ����߶�
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}
	return 0;
}

//���

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPTSTR cmdLine, INT nShow)
{
	g_hInstance = hInstance;
	// ���һ��������
	WNDCLASS  wndClass;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = TEXT("well");

	//ע�ᴰ����
	RegisterClass(&wndClass);

	//��������piano
	HWND hWnd = CreateWindow(TEXT("well"), TEXT("Title_piano"), WS_OVERLAPPED, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,NULL, NULL,  hInstance, NULL);

	//��ʾ��ˢ�´���piano
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	//�����Զ����ʹ���send_char
	HWND hWnd2 = CreateWindow(TEXT("well"), TEXT("Title_send"), WS_OVERLAPPED, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	//��ȡ�ı��ַ�
	FILE * pFile;
	fopen_s(&pFile, "Sound.txt", "rb");
	CHAR str[200] = {};
	fread(str, 1, 200, pFile);
	int len = strlen(str);
	char chChar;
	for (int i = 0; i < len; i++) {	
		chChar = str[i];
		if (chChar >= 65 && chChar <= 90) {
			SendMessage(hWnd, WM_CHAR, chChar, chChar);
			Sleep(900);
		}
		else {
			Sleep(1000);
		}
	}
	

	fclose(pFile);


	//ѭ��������Ϣ
	MSG msg = {};
	while (GetMessage(&msg, hWnd, 0, 0)) {

		TranslateMessage(&msg);
		
		DispatchMessage(&msg);
	}

	return msg.wParam;
}