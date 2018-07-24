#pragma once
#include <windows.h>

class CPEinfo
{
public:
	CPEinfo(char* szFile, BOOL isExe);
	~CPEinfo();

public:
	char* Open(char* szFile);
	char* Load(char* szFile);
	BOOL IsPE(char* buffer);
	BOOL Analyze(char* buffer);
	IMAGE_SECTION_HEADER* GetSectionByName(char* name);
	BOOL AddNewSection(char* chNewName, DWORD dwNewRawDataSize);

public: 
	char  m_szNewFilePath[255] = { 0 };
	DWORD m_FileSize;
	DWORD m_dwBufferBase; //缓冲基址
	DWORD m_dwBufferExtraSize; //缓冲附加大小
	IMAGE_FILE_HEADER* m_pFileHeader;
	IMAGE_OPTIONAL_HEADER32* m_pOptionalHeader;
	IMAGE_SECTION_HEADER* m_pSectionHeader0; //第一个区段地址
};

