// pe_importTable.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>

//定义变量
char* g_pFileBuffer;
IMAGE_DOS_HEADER* g_pDosHeader;
IMAGE_NT_HEADERS* g_pNtHeaders;
IMAGE_FILE_HEADER* g_pFileHeader;
IMAGE_OPTIONAL_HEADER* g_pOptionalHeader;
IMAGE_SECTION_HEADER* g_pSectionHeader;
IMAGE_DATA_DIRECTORY* g_pDataDir;
IMAGE_EXPORT_DIRECTORY* g_pExportDir;

BOOL LoadFile(WCHAR* pFileName);
BOOL IsPeFile();
bool ShowImportTableInfo();
int _tmain(int argc, _TCHAR* argv[])
{
	WCHAR* pFileName = L"C:\\Program Files (x86)\\Notepad++\\SciLexer.dll";
	if (!LoadFile(pFileName)) {
		return 0;
	}
	if (!IsPeFile()) {
		return 0;
	}
	ShowImportTableInfo();
    return 0;
}

BOOL LoadFile(WCHAR* pFileName)
{
	HANDLE hFile = CreateFile(pFileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		printf("打开文件失败\n");
		return FALSE;
	}
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	if (dwFileSize == INVALID_FILE_SIZE) {
		printf("无法读取文件大小\n");
		CloseHandle(hFile);
		return FALSE;
	}
	g_pFileBuffer = new char[dwFileSize];
	ZeroMemory(g_pFileBuffer, dwFileSize);
	BOOL  bRead = ReadFile(hFile, g_pFileBuffer, dwFileSize, NULL, NULL);
	if (bRead == FALSE) {
		printf("无法读取文件数据\n");
		CloseHandle(hFile);
		return FALSE;
	}
	g_pDosHeader = (IMAGE_DOS_HEADER*)g_pFileBuffer;
	g_pNtHeaders = (IMAGE_NT_HEADERS*)(g_pDosHeader->e_lfanew + (DWORD)g_pFileBuffer ); // error + fileBase
	g_pFileHeader = (IMAGE_FILE_HEADER*)(&g_pNtHeaders->FileHeader);
	g_pOptionalHeader = (IMAGE_OPTIONAL_HEADER*)(&g_pNtHeaders->OptionalHeader);
	g_pSectionHeader = IMAGE_FIRST_SECTION(g_pNtHeaders);
	g_pDataDir = (IMAGE_DATA_DIRECTORY*)g_pOptionalHeader->DataDirectory;
	g_pExportDir = (IMAGE_EXPORT_DIRECTORY*)g_pDataDir[0].VirtualAddress;
	
	CloseHandle(hFile);
	return TRUE;
}

BOOL IsPeFile()
{
	if (g_pDosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
		printf("没有MZ签名\n");
		return FALSE;
	}
	if (g_pNtHeaders->Signature != IMAGE_NT_SIGNATURE) {
		printf("没有NT头的PE签名\n");
		return FALSE;
	}
	return TRUE;
}

bool ShowImportTableInfo()
{
	if (g_pDataDir[0].Size == 0) {
		printf("没有导出表\n");
		return FALSE;
	}



	return TRUE;
}
