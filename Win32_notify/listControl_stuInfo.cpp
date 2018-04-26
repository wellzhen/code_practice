// Win32_notify.cpp : 定义应用程序的入口点。
#include "stdafx.h"
#include <CommCtrl.h>
#include "Win32_notify.h"
#pragma comment(lib, "comctl32.lib")

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
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), NULL, (DLGPROC)WndProc);


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
		//获取list control的句柄
		HWND hList = GetDlgItem(hWnd, IDC_LIST2);
		//插入列结构
		LVCOLUMN lc;
		lc.mask = LVCF_WIDTH | LVCF_TEXT;
		lc.pszText = L"姓名";
		RECT rect = {};

		GetClientRect(hList, &rect);
		lc.cx = (int)(rect.right / 5);
		lc.cchTextMax = 3;

		//插入列字段
		ListView_InsertColumn(hList, 0, &lc);
		lc.pszText = L"籍贯";
		ListView_InsertColumn(hList, 1, &lc);
		lc.pszText = L"地址";
		ListView_InsertColumn(hList, 2, &lc);
		lc.pszText = L"政治面貌";
		ListView_InsertColumn(hList, 3, &lc);
		lc.pszText = L"学历";
		ListView_InsertColumn(hList, 4, &lc);


	}
	break;
	case WM_NOTIFY:
	{

	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 分析菜单选择: 
		switch (wmId)
		{
		case IDC_BUTTON1:
		{
			MessageBox(hWnd, L"默认notify消息", L"notify",MB_CANCELTRYCONTINUE); //无法点击和关闭
			//姓名
			WCHAR name[100];
			WCHAR provice[100];
			WCHAR address[100];
			WCHAR group[100];
			WCHAR edu[100];
			HWND hName = GetDlgItem(hWnd, IDC_EDIT1);
			HWND hPro = GetDlgItem(hWnd, IDC_EDIT2);
			HWND hAddr = GetDlgItem(hWnd, IDC_EDIT3);
			HWND hGroup = GetDlgItem(hWnd, IDC_EDIT4);
			HWND hEdu= GetDlgItem(hWnd, IDC_EDIT5);

			GetWindowText(hName, name, 100);
			GetWindowText(hPro, provice, 100);
			GetWindowText(hAddr, address, 100);
			GetWindowText(hGroup, group, 100);
			GetWindowText(hEdu, edu, 100);

			//获取list句柄
			HWND  hList = GetDlgItem(hWnd, IDC_LIST2);
			LVITEM  li = {}; //必须初始化
			li.mask = LVIF_TEXT;
			li.pszText = name;
			ListView_InsertItem(hList, &li);
			ListView_SetItemText(hList, 0, 1, provice);
			ListView_SetItemText(hList, 0, 2, address);
			ListView_SetItemText(hList, 0, 3, group);
			ListView_SetItemText(hList, 0, 4, edu);
			
			
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
	return DefWindowProc(hWnd, message, wParam, lParam);
	return 0;
	
}
