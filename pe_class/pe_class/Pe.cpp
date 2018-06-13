#include "stdafx.h"
#include "Pe.h"


CPe::CPe()
{
}


CPe::~CPe()
{
	delete[] m_pFileBuffer;
}


BOOL CPe::LoadFile(WCHAR* pFileName)
{
	m_pFileName = pFileName;
	HANDLE hFile = CreateFile(pFileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		MessageBoxW(NULL, L"打开文件失败", L"tip", MB_OK);
		return FALSE;
	}
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	if (dwFileSize == INVALID_FILE_SIZE) {
		MessageBoxW(NULL, L"无法读取文件大小", L"tip", MB_OK);
		CloseHandle(hFile);
		return FALSE;
	}
	m_pFileBuffer = new char[dwFileSize];
	ZeroMemory(m_pFileBuffer, dwFileSize);
	BOOL  bRead = ReadFile(hFile, m_pFileBuffer, dwFileSize, NULL, NULL);
	if (bRead == FALSE) {
		MessageBoxW(NULL, L"无法读取文件数据", L"tip", MB_OK);
		CloseHandle(hFile);
		return FALSE;
	}
	m_pDosHeader = (IMAGE_DOS_HEADER*)m_pFileBuffer;
	m_pNtHeaders = (IMAGE_NT_HEADERS*)(m_pDosHeader->e_lfanew + m_pFileBuffer); // error + fileBase
	m_pFileHeader = (IMAGE_FILE_HEADER*)(&m_pNtHeaders->FileHeader);
	m_pOptionalHeader = (IMAGE_OPTIONAL_HEADER*)(&m_pNtHeaders->OptionalHeader);
	m_pSectionHeader = IMAGE_FIRST_SECTION(m_pNtHeaders);
	m_pDataDir = (IMAGE_DATA_DIRECTORY*)m_pOptionalHeader->DataDirectory;

	CloseHandle(hFile);
}
BOOL CPe::IsPeFile()
{
	if (m_pDosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
		MessageBoxW(NULL, L"没有MZ签名", L"tip", MB_OK);
		return FALSE;
	}
	if (m_pNtHeaders->Signature != IMAGE_NT_SIGNATURE) {
		MessageBoxW(NULL, L"没有NT头的PE签名\n", L"tip", MB_OK);
		return FALSE;
	}
	return TRUE;
}
DWORD CPe::RVA2FOA(DWORD RVA)
{
	WORD dwCount = m_pFileHeader->NumberOfSections;
	IMAGE_SECTION_HEADER* pSectionHeader = m_pSectionHeader;
	BOOL bFind = false;
	for (WORD i = 0; i < dwCount; i++) {
		if (RVA >= pSectionHeader->VirtualAddress && RVA < (pSectionHeader->VirtualAddress + pSectionHeader->Misc.VirtualSize)) {
			bFind = true;
			break;
		}
		pSectionHeader++;
	}
	if (!bFind) {
		MessageBoxW(NULL, L"RVA2FOA转换失败", L"tip", MB_OK);
		return 0;
	}
	return RVA - pSectionHeader->VirtualAddress + pSectionHeader->PointerToRawData;

}

DWORD CPe::GetSectionFoaByRva(DWORD RVA)
{
	WORD dwCount = m_pFileHeader->NumberOfSections;
	IMAGE_SECTION_HEADER* pSectionHeader = m_pSectionHeader;
	BOOL bFind = false;
	for (WORD i = 0; i < dwCount; i++) {
		if (RVA >= pSectionHeader->VirtualAddress && RVA < (pSectionHeader->VirtualAddress + pSectionHeader->Misc.VirtualSize)) {
			bFind = true;
			break;
		}
		pSectionHeader++;
	}
	if (!bFind) {
		MessageBoxW(NULL, L"GetSectionFoaByRva error", L"tip", MB_OK);
		return 0;
	}
	return pSectionHeader->PointerToRawData;
}

IMAGE_SECTION_HEADER* CPe::GetSectionHeaderByRva(DWORD RVA)
{
	WORD dwCount = m_pFileHeader->NumberOfSections;
	IMAGE_SECTION_HEADER* pSectionHeader = m_pSectionHeader;
	BOOL bFind = false;
	for (WORD i = 0; i < dwCount; i++) {
		if (RVA >= pSectionHeader->VirtualAddress && RVA < (pSectionHeader->VirtualAddress + pSectionHeader->Misc.VirtualSize)) {
			bFind = true;
			break;
		}
		pSectionHeader++;
	}
	if (!bFind) {
		MessageBoxW(NULL, L"GetSectionHeaderByRva error", L"tip", MB_OK);
		return 0;
	}
	return pSectionHeader;

}
