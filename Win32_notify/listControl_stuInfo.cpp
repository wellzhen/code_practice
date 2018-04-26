// Win32_notify.cpp : ����Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include <CommCtrl.h>
#include "Win32_notify.h"
#pragma comment(lib, "comctl32.lib")

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
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), NULL, (DLGPROC)WndProc);


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
		//��ȡlist control�ľ��
		HWND hList = GetDlgItem(hWnd, IDC_LIST2);
		//�����нṹ
		LVCOLUMN lc;
		lc.mask = LVCF_WIDTH | LVCF_TEXT;
		lc.pszText = L"����";
		RECT rect = {};

		GetClientRect(hList, &rect);
		lc.cx = (int)(rect.right / 5);
		lc.cchTextMax = 3;

		//�������ֶ�
		ListView_InsertColumn(hList, 0, &lc);
		lc.pszText = L"����";
		ListView_InsertColumn(hList, 1, &lc);
		lc.pszText = L"��ַ";
		ListView_InsertColumn(hList, 2, &lc);
		lc.pszText = L"������ò";
		ListView_InsertColumn(hList, 3, &lc);
		lc.pszText = L"ѧ��";
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
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDC_BUTTON1:
		{
			MessageBox(hWnd, L"Ĭ��notify��Ϣ", L"notify",MB_CANCELTRYCONTINUE); //�޷�����͹ر�
			//����
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

			//��ȡlist���
			HWND  hList = GetDlgItem(hWnd, IDC_LIST2);
			LVITEM  li = {}; //�����ʼ��
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
	return DefWindowProc(hWnd, message, wParam, lParam);
	return 0;
	
}
