// stub.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <Windows.h>
#include "stubconf.h"
//设置区段合并, 并导出两个符号
#pragma comment(linker, "/merge:.data=.text")
#pragma comment(linker, "/merge:.rdata=.text")
#pragma comment(linker, "/section:.text,REW")
//密码弹框
void SDK();
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

typedef void* (WINAPI* FnGetProcAddress)(HMODULE, LPCSTR);
typedef HMODULE(WINAPI* FnLoadLibraryA)(LPCSTR);
typedef HMODULE(WINAPI* FnGetModuleHandleA)(LPCSTR);
typedef LPVOID (WINAPI* FnVirtualAlloc)(LPVOID, SIZE_T, DWORD, DWORD);
typedef BOOL (WINAPI* FnVirtualProtect)(LPVOID, SIZE_T, DWORD, PDWORD);


typedef void (WINAPI *FnPostQuitMessage)(int);
typedef BOOL(WINAPI *FnShowWindow)(HWND, int);
typedef BOOL(WINAPI *FnTranslateMessage)(CONST MSG *);
typedef LRESULT(WINAPI *FnDispatchMessageA)(CONST MSG *);
typedef ATOM (WINAPI* FnRegisterClassA)(const WNDCLASSA *);
typedef HWND (WINAPI* FnCreateWindowExA)(DWORD,LPCSTR,LPCSTR,DWORD,int,int,int,int,HWND,HMENU,HINSTANCE,LPVOID);
typedef BOOL (WINAPI* FnGetMessageA)(LPMSG,HWND,UINT,UINT);
typedef int (WINAPI* FnGetWindowTextA)(HWND,LPCSTR,int);
typedef int (WINAPI* FnMessageBoxA)(HWND,LPCSTR,LPCSTR,UINT);
typedef LRESULT (WINAPI* FnDefWindowProcA)(HWND,UINT,WPARAM,LPARAM);
typedef LRESULT(WINAPI* FnSendMessageA)(HWND, UINT, WPARAM, LPARAM);

typedef HWND (WINAPI* FnFindWindowA)(LPCSTR,	LPCSTR );
typedef  VOID (WINAPI* FnExitProcess)(UINT);

struct APIS {
	FnGetProcAddress GetProcAddress;
	FnLoadLibraryA	 LoadLibraryA;
	FnGetModuleHandleA GetModuleHandleA;
	FnVirtualAlloc	VirtualAlloc;
	FnVirtualProtect VirtualProtect;

	FnPostQuitMessage  PostQuitMessage;
	FnShowWindow	ShowWindow;
	FnTranslateMessage  TranslateMessage;
	FnDispatchMessageA DispatchMessageA;
	FnRegisterClassA	RegisterClassA;
	FnCreateWindowExA	CreateWindowExA;
	FnGetMessageA  GetMessageA;
	FnGetWindowTextA GetWindowTextA;
	FnMessageBoxA MessageBoxA;
	FnDefWindowProcA DefWindowProcA;
	FnSendMessageA  SendMessageA;
	FnFindWindowA   FindWindowA;
	FnExitProcess   ExitProcess;
};
APIS g_APIs;
DWORD g_ImageBase;

void Decrypt();
void GetApis();
void FillIAT();
void FixReloc();
void callTLS();
BOOL isDbg();

DWORD AsmStrcmp(char* src, char* dest, DWORD len);
DWORD AsmStrlen(char* src);
extern "C"
{
	_declspec(dllexport) StubConf  g_conf;
	_declspec(dllexport) DWORD g_oep = 0x11223344;
	_declspec(dllexport) 
		void _declspec(naked) start() {
		_asm
		{
			jmp tag_noise
			_EMIT 0x1  //花指令
			_EMIT 0x2
			_EMIT 0x3
			_EMIT 0x4
			tag_noise:
			
		}
			//获取api
			GetApis();
			g_ImageBase = (DWORD)g_APIs.GetModuleHandleA(NULL);//获取基址, FixIAT需要使用
			//密码弹框-验证-解密
			SDK();

			//修复重定位
			FixReloc();
			
			//填充IAT
			FillIAT();
			_asm {
				add esi, 1
				add esi, 1
				sub esi, 1
				sub esi, 1
			}
			
			callTLS();
			
			if (isDbg()) { //检测是否被调试
				g_APIs.ExitProcess(0);
			}
			g_conf.dwOEP += g_ImageBase;
			_asm {
				jmp g_conf.dwOEP
			}
	}
}

void GetApis()
{
	//获取kernel32的基址
	HMODULE hKernel32;
	HMODULE hUser32;
	_asm {
		push esi
		mov esi, fs:[0x30]
		mov esi, [esi + 0x0C]
		mov esi, [esi + 0x1C]
		mov esi, [esi]
		mov esi, [esi + 0x08]
		mov hKernel32, esi
		pop esi
	}
	DWORD dwKernel32Base = (DWORD)hKernel32;
	//1. 获取GetProcAddress的函数地址
	//1.1 获取头信息
	IMAGE_DOS_HEADER* pDosHeader = (IMAGE_DOS_HEADER*)hKernel32;
	IMAGE_NT_HEADERS32* pNtHeader = (IMAGE_NT_HEADERS32*)(pDosHeader->e_lfanew + dwKernel32Base);
	IMAGE_FILE_HEADER* pFileHeader = (IMAGE_FILE_HEADER*)&pNtHeader->FileHeader;
	IMAGE_OPTIONAL_HEADER* pOptionalHeader = (IMAGE_OPTIONAL_HEADER*)&pNtHeader->OptionalHeader;

	//1.2 导出表信息
	IMAGE_DATA_DIRECTORY pExportDataDir = pOptionalHeader->DataDirectory[0];
	IMAGE_EXPORT_DIRECTORY* pExportDir = (IMAGE_EXPORT_DIRECTORY*)(pExportDataDir.VirtualAddress + dwKernel32Base);
	DWORD dwNumOfFuncs = pExportDir->NumberOfFunctions;
	DWORD dwNumOfNames = pExportDir->NumberOfNames;
	DWORD* AddressOfFuncsVA = (DWORD*)(pExportDir->AddressOfFunctions + dwKernel32Base);
	DWORD* AddressOfNamesVA = (DWORD*)(pExportDir->AddressOfNames + dwKernel32Base);
	WORD * AddressOfOrdinalsVA = (WORD*)(pExportDir->AddressOfNameOrdinals + dwKernel32Base);

	//1.3 获取函数地址
	for (DWORD i = 0; i < dwNumOfNames; i++) {
		
		char* FuncName = (char*)(AddressOfNamesVA[i] + dwKernel32Base);
		if (AsmStrcmp(FuncName, "GetProcAddress", 0xE) == 0) {
			//序号
			WORD order = AddressOfOrdinalsVA[i];
			g_APIs.GetProcAddress = (FnGetProcAddress)(AddressOfFuncsVA[order] + dwKernel32Base);
			break;
		}
	}


	//1.4 其它Api
	g_APIs.GetModuleHandleA = (FnGetModuleHandleA)g_APIs.GetProcAddress(hKernel32, "GetModuleHandleA");
	g_APIs.LoadLibraryA = (FnLoadLibraryA)g_APIs.GetProcAddress(hKernel32, "LoadLibraryA");
	g_APIs.VirtualAlloc = (FnVirtualAlloc)g_APIs.GetProcAddress(hKernel32, "VirtualAlloc");
	g_APIs.VirtualProtect = (FnVirtualProtect)g_APIs.GetProcAddress(hKernel32, "VirtualProtect");
	g_APIs.ExitProcess = (FnExitProcess)g_APIs.GetProcAddress(hKernel32, "ExitProcess");

	hUser32 = g_APIs.LoadLibraryA("user32.dll");
	g_APIs.CreateWindowExA = (FnCreateWindowExA)g_APIs.GetProcAddress(hUser32, "CreateWindowExA");//
	g_APIs.DefWindowProcA = (FnDefWindowProcA)g_APIs.GetProcAddress(hUser32, "DefWindowProcA");//
	g_APIs.DispatchMessageA = (FnDispatchMessageA)g_APIs.GetProcAddress(hUser32, "DispatchMessageA");//
	g_APIs.GetMessageA = (FnGetMessageA)g_APIs.GetProcAddress(hUser32, "GetMessageA");//
	g_APIs.GetWindowTextA = (FnGetWindowTextA)g_APIs.GetProcAddress(hUser32, "GetWindowTextA");
	g_APIs.PostQuitMessage = (FnPostQuitMessage)g_APIs.GetProcAddress(hUser32, "PostQuitMessage");
	g_APIs.RegisterClassA = (FnRegisterClassA)g_APIs.GetProcAddress(hUser32, "RegisterClassA");//
	g_APIs.ShowWindow = (FnShowWindow)g_APIs.GetProcAddress(hUser32, "ShowWindow");
	g_APIs.TranslateMessage	= (FnTranslateMessage)g_APIs.GetProcAddress(hUser32, "TranslateMessage");
	g_APIs.MessageBoxA = (FnMessageBoxA)g_APIs.GetProcAddress(hUser32, "MessageBoxA");
	g_APIs.SendMessageA = (FnSendMessageA)g_APIs.GetProcAddress(hUser32, "SendMessageA");
	g_APIs.FindWindowA = (FnFindWindowA)g_APIs.GetProcAddress(hUser32, "FindWindowA");


}

void FillIAT()
{
	//依据exe的数据目录表修复IAT表, 
	IMAGE_DATA_DIRECTORY* pDataDir = g_conf.dataDir;
	//导入表信息
	IMAGE_IMPORT_DESCRIPTOR* pImportDesp = (IMAGE_IMPORT_DESCRIPTOR*)((pDataDir +1)->VirtualAddress + g_ImageBase);

	while (pImportDesp->Name != 0) {
		//获取导入的名字
		char*  chNameVA = (char*)(pImportDesp->Name + g_ImageBase);
		HMODULE hDll = g_APIs.LoadLibraryA(chNameVA);
		IMAGE_THUNK_DATA32* pINT = (IMAGE_THUNK_DATA32*)(pImportDesp->OriginalFirstThunk + g_ImageBase);
		DWORD* pIAT = (DWORD*)(pImportDesp->FirstThunk + g_ImageBase);

		while (pINT->u1.AddressOfData != 0) {
			//判断是否是名称导入的
			char* chName;
			if (!IMAGE_SNAP_BY_ORDINAL32(pINT->u1.AddressOfData)) {//名称导入的
				IMAGE_IMPORT_BY_NAME* pByName = (IMAGE_IMPORT_BY_NAME*)(pINT->u1.AddressOfData + g_ImageBase);
				chName = pByName->Name;
			}
			else {//序号导入
				chName = (char*)(pINT->u1.Ordinal & 0xFFFF);
			}
			DWORD funcVA = (DWORD)g_APIs.GetProcAddress(hDll, chName);//真正的函数地址
			//申请空间, 构造花指令
			char* pNoiseAddr = (char*)g_APIs.VirtualAlloc(NULL, 1, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			*(DWORD*)pNoiseAddr = 0x46464646; // inc esi
			*(DWORD*)(pNoiseAddr + 4) = 0x4E4E4E4E; // dec esi
			pNoiseAddr[8] = 0xE9;
			*(DWORD*)(pNoiseAddr + 9) = funcVA - (DWORD)pNoiseAddr - 8 - 5;

			//写入IAT表
			DWORD oldProt;
			g_APIs.VirtualProtect(pIAT, 4, PAGE_EXECUTE_READWRITE, &oldProt);
			//*pIAT = funcVA;
			*pIAT = (DWORD)pNoiseAddr;
			g_APIs.VirtualProtect(pIAT, 4, oldProt, &oldProt);
			pIAT++;
			pINT++;
		}
		pImportDesp++;
	}
}

DWORD AsmStrcmp(char* src, char* dest, DWORD len)
{
	__asm {
		push ecx
		push esi
		push edi
		mov ecx, len
		mov esi, src
		mov edi, dest
		cld
		repe cmpsb
		je tag_equal
		mov eax, 1;
		jmp tag_end
	tag_equal:
		mov eax, 0;
	tag_end:	
		pop edi
		pop esi
		pop ecx
	}
}

DWORD AsmStrlen(char* src) 
{
	__asm {
		push ecx
		push esi
		mov ecx, 0
		mov esi, src
	tag_loop:
		cmp byte ptr [esi], 0
		je tag_end
		add ecx, 1
		add esi, 1
		jmp tag_loop
	tag_end:
		mov eax, ecx
		pop esi
		pop ecx

	}
}


void FixReloc()
{

	struct TypeOffset {
		WORD  Offset : 12;
		WORD  Type : 4;
	};

	
	//重定位表
	_asm {
		add esi,1
		sub esi, 1
	}
	IMAGE_BASE_RELOCATION* pBaseReloc = (IMAGE_BASE_RELOCATION*)(g_conf.dataDir[5].VirtualAddress + g_ImageBase); //全局变量没有重定位,不能使用
	_asm {
		add esi, 2
		add esi, 3
		sub esi, 3
		sub esi, 2
	}
	////开始重定位
	while (pBaseReloc->SizeOfBlock != 0) {
		DWORD count = (pBaseReloc->SizeOfBlock - 8) / 2;
		for (DWORD i = 0; i < count; i++) {
			DWORD RelocVA = (DWORD)pBaseReloc + 8 + i * 2;
			TypeOffset* pTypeOffset = (TypeOffset*)RelocVA;
			DWORD dwFixVA = 0;
			if (pTypeOffset->Type == 3) {
				dwFixVA = pTypeOffset->Offset + pBaseReloc->VirtualAddress + g_ImageBase;
			}
			else {
				break;
			}
			//修改重定位处的值

			DWORD dwOldProtect;
			g_APIs.VirtualProtect((DWORD*)dwFixVA, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	//		//*(DWORD*)dwFixVA -= pOptionalHeader->ImageBase;//加载后就变了??
			*(DWORD*)dwFixVA -= 0x400000;
			*(DWORD*)dwFixVA += g_ImageBase;
			g_APIs.VirtualProtect((DWORD*)dwFixVA, 4, dwOldProtect, &dwOldProtect);
		}
		pBaseReloc = (IMAGE_BASE_RELOCATION*)((DWORD)pBaseReloc + pBaseReloc->SizeOfBlock);
	}

}

void Decrypt()
{
	//1.1 获取头信息
	IMAGE_DOS_HEADER* pDosHeader = (IMAGE_DOS_HEADER*)g_ImageBase;
	IMAGE_NT_HEADERS32* pNtHeader = (IMAGE_NT_HEADERS32*)(pDosHeader->e_lfanew + g_ImageBase);
	IMAGE_FILE_HEADER* pFileHeader = (IMAGE_FILE_HEADER*)&pNtHeader->FileHeader;
	IMAGE_OPTIONAL_HEADER* pOptionalHeader = (IMAGE_OPTIONAL_HEADER*)&pNtHeader->OptionalHeader;

	IMAGE_SECTION_HEADER* pSectionHeader0 = (IMAGE_SECTION_HEADER*)((DWORD)pOptionalHeader + pFileHeader->SizeOfOptionalHeader);
	DWORD dwSectionCount = pFileHeader->NumberOfSections - 1; //不加密最后一个区段
	for (DWORD i = 0; i < dwSectionCount; i++) {
		IMAGE_SECTION_HEADER* pSection = pSectionHeader0 + i;
		DWORD dwSectionVA = pSection->VirtualAddress + g_ImageBase;
		DWORD dwSectionLength = pSection->Misc.VirtualSize;
		DWORD dwOldProtect;
		char * name = (char*)pSection->Name;
		if (AsmStrcmp(name, ".text", 6) != 0) {
			continue;
		}
		if (pSection->SizeOfRawData == 0) {
			continue;
		}
		g_APIs.VirtualProtect((char*)dwSectionVA, dwSectionLength, PAGE_READWRITE, &dwOldProtect);
		DWORD userPwdLen = AsmStrlen(g_conf.szKey);
		for (DWORD j = 0; j < dwSectionLength; j++) {
			*((char*)dwSectionVA + j) = ~*((char*)dwSectionVA + j);
			*((char*)dwSectionVA + j) ^= g_conf.szKey[j %userPwdLen];
		}
		g_APIs.VirtualProtect((char*)dwSectionVA, dwSectionLength, dwOldProtect, &dwOldProtect);
	}

}


/***************密码弹框********************/

HWND g_hBtn;
HWND g_hPwd;
char chPwd[10] = { 0 };//用于接收Edit中字符串



void SDK()
{
	HINSTANCE  hInstance = g_APIs.GetModuleHandleA(NULL);
	// 创建窗口的过程
	// 1. 注册窗口类
	// 2. 根据窗口类创建窗口
	// 3. 消息循环
	WNDCLASSA wndMain = {};
	// 下面两个是必须的
	wndMain.lpszClassName = "mainClass"; //父类
										 // 所有通过父类创建的窗口,他们的消息回调函数都是WindowProc
	wndMain.lpfnWndProc = WndProc;
	// 设置窗口背景色
	wndMain.hbrBackground = (HBRUSH)(COLOR_INACTIVECAPTION);
	// 注册窗口
	if (!g_APIs.RegisterClassA(&wndMain))
	{
		hInstance = 0;
	}
	HWND hWnd = g_APIs.CreateWindowExA(0,
		"mainClass",// 窗口类名
		"请输入密码",// 窗口名
		WS_OVERLAPPEDWINDOW,// 窗口风格,个性话定义
		300, 100,// 窗口的起始位置
		300, 150,// 窗口的宽高
		NULL,// 父窗口
		NULL,// 菜单句柄
		hInstance,// 实例句柄
		NULL);// 附加信息
	g_APIs.ShowWindow(hWnd, SW_SHOW);
	// 消息循环
	MSG msg = {};
	// 接收消息,分发给不同的窗口
	while (g_APIs.GetMessageA(&msg, NULL, NULL, NULL))
	{
		g_APIs.TranslateMessage(&msg);
		// 把不同窗口的消息分发给对应的回调函数->WindowProc
		g_APIs.DispatchMessageA(&msg);
	}
}


// 窗口处理过程
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE  hInstance = (HINSTANCE)g_ImageBase;

	switch (message)
	{
	case WM_CREATE:
	{
		//创建密码输入框
		g_hPwd = g_APIs.CreateWindowExA(0,"edit", "password", WS_CHILD | WS_VISIBLE, 100, 10, 100, 20, hWnd, (HMENU)0x1000, hInstance, NULL);
		g_APIs.ShowWindow(g_hPwd, SW_SHOW);
		g_hBtn = g_APIs.CreateWindowExA(0,"button", "submit", WS_CHILD | WS_VISIBLE, 100, 50, 100, 20, hWnd, (HMENU)0x2000, hInstance, NULL);
		g_APIs.ShowWindow(g_hBtn, SW_SHOW);

	} break;
	case WM_COMMAND:
	{
		WORD wHight = HIWORD(wParam);
		WORD wLow = LOWORD(wParam);
		switch (wLow)
		{
		case 0x2000:
			g_APIs.GetWindowTextA(g_hPwd, chPwd, 10);
			DWORD len = AsmStrlen(chPwd);
			DWORD keyLen = AsmStrlen(g_conf.szKey);
			if (len == 0) {
				g_APIs.MessageBoxA(0, "must not empty !", 0, 0);
			}
			else if(AsmStrcmp(chPwd, g_conf.szKey,keyLen + 1) == 0) {

				g_APIs.MessageBoxA(0, "开始运行", "密码正确", MB_OK);
				//关闭密码窗口, 解密
				//解密
				Decrypt();
				g_APIs.SendMessageA(hWnd, WM_CLOSE, NULL, NULL);
				g_APIs.PostQuitMessage(0);
			}
			else {
				g_APIs.MessageBoxA(0, "wrong", 0, 0);
			}
			break;
		}
	}
	break;
	default:
		return g_APIs.DefWindowProcA(hWnd, message, wParam, lParam);
	}
	return (LRESULT)0;
}

void callTLS()
{
	DWORD i = 0; 
	while (g_conf.dwTlsCallBackValue[i] != 0) {
		PIMAGE_TLS_CALLBACK* pTlsFun = (PIMAGE_TLS_CALLBACK*)(g_conf.dwTlsCallBackValue[i] - 0x400000 + g_ImageBase);
		(*pTlsFun)((PVOID)g_ImageBase, DLL_PROCESS_ATTACH, NULL);
		g_APIs.MessageBoxA(NULL, "tls", "tls", MB_OK);
		i++;
	}
}


BOOL isDbg()
{
	HWND ret1 = g_APIs.FindWindowA(NULL, "x32_dbg");
	HWND ret2 = g_APIs.FindWindowA(NULL, "吾愛破解 - [LCG]");
	if (ret1 != NULL || ret2 != NULL)
	{
		g_APIs.MessageBoxA(NULL, "正在被调试, 程序即将退出", "警告", MB_OK);
		return TRUE;
	}

	return FALSE;
}
