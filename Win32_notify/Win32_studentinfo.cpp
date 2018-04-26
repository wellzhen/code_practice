// Win32_notify.cpp : ����Ӧ�ó������ڵ㡣
//
#include "resource.h"
#include "stdafx.h"
#include "Win32_notify.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������

// �˴���ģ���а����ĺ�����ǰ������: 
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: �ڴ˷��ô��롣

    // ��ʼ��ȫ���ַ���
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32_NOTIFY, szWindowClass, MAX_LOADSTRING);
    
	//����Dialog
	DialogBox(hInst,MAKEINTRESOURCE(IDD_DIALOG2), NULL, (DLGPROC)WndProc);


    return (int)1;
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
    switch (message)
    {
	case WM_INITDIALOG:
	{
		int wmId = LOWORD(wParam);
		HWND hPic = GetDlgItem(hWnd, IDC_STATIC);
		HBITMAP hBitMap = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1));
		SendMessage(hPic, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitMap);

		//������
		static int pos = 10;
		HWND hProcess= GetDlgItem(hWnd, IDC_PROGRESS1);
		SendMessage(hProcess, SBM_SETPOS, pos, 0);
		pos += 10;

		//����
		HWND hSlider= GetDlgItem(hWnd, IDC_PROGRESS1);
		SendMessage(hSlider, SBM_SETRANGE, true, MAKELONG(0, 300));//���û���ķ�Χ

	}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �����˵�ѡ��: 
            switch (wmId)
            {
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
