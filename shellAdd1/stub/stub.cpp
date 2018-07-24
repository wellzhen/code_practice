// stub.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <Windows.h>
#include "stubconf.h"
//设置区段合并, 并导出两个符号
#pragma comment(linker, "/merge:.data=.text")
#pragma comment(linker, "/merge:.rdata=.text")
#pragma comment(linker, "/section:.text,REW")

typedef void* (WINAPI* FnGetProcAddress)(HMODULE, LPCSTR);
typedef HMODULE(WINAPI* FnLoadLibraryA)(LPCSTR);
typedef HMODULE(WINAPI* FnGetModuleHandleA)(LPCSTR);
typedef LPVOID (WINAPI* FnVirtualAlloc)(LPVOID, SIZE_T, DWORD, DWORD);
typedef BOOL (WINAPI* FnVirtualProtect)(LPVOID, SIZE_T, DWORD, PDWORD);

struct APIS {
	FnGetProcAddress GetProcAddress;
	FnLoadLibraryA	 LoadLibraryA;
	FnGetModuleHandleA GetModuleHandleA;
	FnVirtualAlloc	VirtualAlloc;
	FnVirtualProtect VirtualProtect;
};

APIS g_APIs;
DWORD g_ImageBase;

void GetApis();
void FixIAT();
void FixReloc();

DWORD AsmStrcmp(char* src, char* dest, DWORD len);
extern "C"
{
	_declspec(dllexport) StubConf  g_conf;
	_declspec(dllexport) DWORD g_oep = 0x11223344;
	_declspec(dllexport) 
		void _declspec(naked) start() {
			GetApis();
			__asm {
				add eax, 1
				add eax, 1
				sub eax, 1
				sub eax, 1
			}
			g_ImageBase = (DWORD)g_APIs.GetModuleHandleA(NULL);//获取基址, FixIAT需要使用


			FixIAT();

			FixReloc();


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


}

void FixIAT()
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
			DWORD funcVA = (DWORD)g_APIs.GetProcAddress(hDll, chName);
			//写入IAT表
			DWORD oldProt;
			g_APIs.VirtualProtect(pIAT, 4, PAGE_EXECUTE_READWRITE, &oldProt);
			*pIAT = funcVA;
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

struct TypeOffset {
	WORD  Offset : 12;
	WORD  Type : 4;
};

void FixReloc()
{
	return;
	//重定位表
	IMAGE_BASE_RELOCATION* pBaseReloc = (IMAGE_BASE_RELOCATION*)(g_conf.dataDir[5].VirtualAddress + g_ImageBase);
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
	//		//*(DWORD*)dwFixVA -= pOptionalHeader->ImageBase;
			*(DWORD*)dwFixVA -= 0x400000;
			*(DWORD*)dwFixVA += g_ImageBase;
			g_APIs.VirtualProtect((DWORD*)dwFixVA, 4, dwOldProtect, &dwOldProtect);
		}
		pBaseReloc = (IMAGE_BASE_RELOCATION*)((DWORD)pBaseReloc + pBaseReloc->SizeOfBlock);
	}

}
