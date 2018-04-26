// win32_window.cpp : ����Ӧ�ó������ڵ㡣
//
#include <tchar.h>
#include "stdafx.h"
#include "win32_window.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������

HWND g_hCalcWnd = NULL;

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: �ڴ˷��ô��롣
	//������ȡ�������ľ��
	HWND hWnd = GetDesktopWindow();
	hWnd = GetWindow(hWnd, GW_CHILD);
	WCHAR  szName[266] = { 0 };
	while (hWnd != NULL) {
		memset(szName, 0, 266);
		GetWindowTextW(hWnd, szName, 266);	
		if (lstrcmpW(szName, L"������") == 0) {
			g_hCalcWnd = hWnd;
			break;
		}
		hWnd = GetNextWindow(hWnd, GW_HWNDNEXT);
	}
	//��������������
	g_hCalcWnd = GetWindow(g_hCalcWnd, GW_CHILD);//��ȡ�˵�һ���Ӵ��ھ��
	g_hCalcWnd = GetWindow(g_hCalcWnd, GW_CHILD); //��ȡ��-�Ӵ���
	g_hCalcWnd = GetNextWindow(g_hCalcWnd, GW_HWNDNEXT);
	g_hCalcWnd = GetNextWindow(g_hCalcWnd, GW_HWNDNEXT);
	g_hCalcWnd = GetWindow(g_hCalcWnd, GW_CHILD); //��ť�ĵ�һ�����




    // ��ʼ��ȫ���ַ���
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32_WINDOW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32_WINDOW));

    MSG msg;

    // ����Ϣѭ��: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }



    return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32_WINDOW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32_WINDOW);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	char msg[100];
	WCHAR msgw[100];
	_itoa_s(message, msg, 10);
	MultiByteToWideChar(CP_ACP, NULL,msg, -1, msgw, _countof(msgw));
	//OutputDebugStringW((LPCWSTR)msgw);
	//OutputDebugStringW(LPCWSTR("\n"));

	int nWidth = 50;
	int nHeight = 35;
    switch (message)
    {
	case WM_CREATE:
		//��ť
		CreateWindow(L"button", L"<-", WS_CHILD | WS_VISIBLE |WS_BORDER,    0,  0, nWidth, nHeight, hWnd, (HMENU)1001, hInst, 0);
		CreateWindow(L"button", L"CE", WS_CHILD | WS_VISIBLE |WS_BORDER, nWidth,  0, nWidth, nHeight, hWnd, (HMENU)1007, hInst, 0);
		CreateWindow(L"button", L"c", WS_CHILD | WS_VISIBLE | WS_BORDER, nWidth * 2, 0, nWidth, nHeight, hWnd, (HMENU)1012, hInst, 0);
		CreateWindow(L"button", L"��", WS_CHILD | WS_VISIBLE | WS_BORDER, nWidth * 3, 0, nWidth, nHeight, hWnd, (HMENU)1018, hInst, 0);
		CreateWindow(L"button", L"��", WS_CHILD | WS_VISIBLE | WS_BORDER, nWidth * 4, 0, nWidth, nHeight, hWnd, (HMENU)1024, hInst, 0);
		
		CreateWindow(L"button", L"7", WS_CHILD | WS_VISIBLE | WS_BORDER,          0, nHeight, nWidth, nHeight, hWnd, (HMENU)1002, hInst, 0);
		CreateWindow(L"button", L"8", WS_CHILD | WS_VISIBLE | WS_BORDER, nWidth    , nHeight, nWidth, nHeight, hWnd, (HMENU)1008, hInst, 0);
		CreateWindow(L"button", L"9", WS_CHILD | WS_VISIBLE | WS_BORDER, nWidth * 2, nHeight, nWidth, nHeight, hWnd, (HMENU)1013, hInst, 0);
		CreateWindow(L"button", L"/", WS_CHILD | WS_VISIBLE | WS_BORDER, nWidth * 3,  nHeight, nWidth,  nHeight, hWnd, (HMENU)1019, hInst, 0);
		CreateWindow(L"button", L"%", WS_CHILD | WS_VISIBLE | WS_BORDER, nWidth * 4, nHeight,  nWidth,  nHeight, hWnd, (HMENU)1025, hInst, 0);

		CreateWindow(L"button", L"4", WS_CHILD | WS_VISIBLE | WS_BORDER, 0, nHeight * 2, nWidth, nHeight, hWnd, (HMENU)1003, hInst, 0);
		CreateWindow(L"button", L"5", WS_CHILD | WS_VISIBLE | WS_BORDER, nWidth, nHeight *2, nWidth, nHeight, hWnd, (HMENU)1009, hInst, 0);
		CreateWindow(L"button", L"6", WS_CHILD | WS_VISIBLE | WS_BORDER, nWidth * 2, nHeight*2, nWidth, nHeight, hWnd, (HMENU)1014, hInst, 0);
		CreateWindow(L"button", L"*", WS_CHILD | WS_VISIBLE | WS_BORDER, nWidth * 3, nHeight*2, nWidth, nHeight, hWnd, (HMENU)1020, hInst, 0);
		CreateWindow(L"button", L"1/x", WS_CHILD | WS_VISIBLE | WS_BORDER, nWidth * 4, nHeight*2, nWidth, nHeight, hWnd, (HMENU)1026, hInst, 0);

		CreateWindow(L"button", L"1", WS_CHILD | WS_VISIBLE | WS_BORDER, 0, nHeight * 3, nWidth, nHeight, hWnd, (HMENU)1004, hInst, 0);
		CreateWindow(L"button", L"2", WS_CHILD | WS_VISIBLE | WS_BORDER, nWidth, nHeight * 3, nWidth, nHeight, hWnd, (HMENU)1010, hInst, 0);
		CreateWindow(L"button", L"3", WS_CHILD | WS_VISIBLE | WS_BORDER, nWidth * 2, nHeight * 3, nWidth, nHeight, hWnd, (HMENU)1015, hInst, 0);
		CreateWindow(L"button", L"-", WS_CHILD | WS_VISIBLE | WS_BORDER, nWidth * 3, nHeight * 3, nWidth, nHeight, hWnd, (HMENU)1021, hInst, 0);
		CreateWindow(L"button", L"=", WS_CHILD | WS_VISIBLE | WS_BORDER, nWidth * 4, nHeight * 3, nWidth, nHeight * 2, hWnd, (HMENU)1027, hInst, 0);

		CreateWindow(L"button", L"0", WS_CHILD | WS_VISIBLE | WS_BORDER, 0, nHeight * 4, nWidth * 2, nHeight, hWnd, (HMENU)1005, hInst, 0);
		CreateWindow(L"button", L".", WS_CHILD | WS_VISIBLE | WS_BORDER, nWidth * 2, nHeight * 4, nWidth, nHeight, hWnd, (HMENU)1016, hInst, 0);
		CreateWindow(L"button", L"+", WS_CHILD | WS_VISIBLE | WS_BORDER, nWidth * 3, nHeight * 4, nWidth, nHeight, hWnd, (HMENU)1022, hInst, 0);

		//CreateWindow(L"button", L"����", WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 0, 50, 100, 50, hWnd, (HMENU)1002, hInst, 0);
		//CreateWindow(L"button", L"����", WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 101, 50, 100, 50, hWnd, (HMENU)1003, hInst, 0);
		//CreateWindow(L"button", L"��", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 0, 100, 100, 50, hWnd, (HMENU)1004, hInst, 0);
		//CreateWindow(L"button", L"Ů", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 101, 100, 100, 50, hWnd, (HMENU)1005, hInst, 0);
		//��̬�ı�
		//CreateWindow(L"static", L"�ı�", WS_CHILD | WS_VISIBLE , 0, 150, 100, 50, hWnd, (HMENU)1006, hInst, 0);
		//���Ͽ�
		//CreateWindow(L"combobox", L"���Ͽ�", WS_CHILD | WS_VISIBLE, 0, 200, 100, 100, hWnd, (HMENU)1007, hInst, 0);
		//�༭
		//CreateWindow(L"edit", L"�༭��", WS_CHILD | WS_VISIBLE | WS_BORDER, 0, 300, 100, 50, hWnd, (HMENU)1008, hInst, 0);
		break;
    case WM_COMMAND:
        {
			int wmId = LOWORD(wParam);
			if (wmId >= 1000 && wmId <= 1027) {
				HWND hTmpWnd = g_hCalcWnd;
				for (int i = 0; i < wmId - 1000; i++) {
					hTmpWnd = GetNextWindow(hTmpWnd, GW_HWNDNEXT);
				}
				SendMessage(hTmpWnd, WM_LBUTTONDOWN, MK_LBUTTON, 0);
				SendMessage(hTmpWnd, WM_LBUTTONUP, MK_LBUTTON, 0);

			

		

				
				return DefWindowProc(hWnd, message, wParam, lParam);
			}

            // �����˵�ѡ��: 
            switch (wmId)
            {
            case IDM_ABOUT:
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			}
				break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
