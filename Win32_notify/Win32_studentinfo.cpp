// Win32_notify.cpp : 定义应用程序的入口点。
//
#include "resource.h"
#include "stdafx.h"
#include "Win32_notify.h"

#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明: 
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32_NOTIFY, szWindowClass, MAX_LOADSTRING);
    
	//创建Dialog
	DialogBox(hInst,MAKEINTRESOURCE(IDD_DIALOG2), NULL, (DLGPROC)WndProc);


    return (int)1;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
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

		//进度条
		static int pos = 10;
		HWND hProcess= GetDlgItem(hWnd, IDC_PROGRESS1);
		SendMessage(hProcess, SBM_SETPOS, pos, 0);
		pos += 10;

		//滑块
		HWND hSlider= GetDlgItem(hWnd, IDC_PROGRESS1);
		SendMessage(hSlider, SBM_SETRANGE, true, MAKELONG(0, 300));//设置滑块的范围

	}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
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
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
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
