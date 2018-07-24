#include "stdafx.h"
#include "PEinfo.h"


CPEinfo::CPEinfo(char* szFile, BOOL isExe)
{
	//加载文件到内存
	m_dwBufferExtraSize = 0x100000; //适当修改
	char* Buffer;
	if (isExe) {
		Buffer = Open(szFile);
	}
	else {
		Buffer = Load(szFile);
	}
	
	if (Buffer == NULL) {
		printf("文件加载失败\n");
		return;
	}

	if (!IsPE(Buffer)) {
		printf("不是有效的PE文件\n");
		return;
	}
	
	//保存文件路径
	memcpy_s(m_szNewFilePath, 255, szFile, strlen(szFile));
	//解析出需要的数据
	Analyze(Buffer);
	//添加区段, 手动调用
	//AddNewSection(Buffer);
	

}



CPEinfo::~CPEinfo()
{
}


//文件加载到内存
char* CPEinfo::Open(char* szFile)
{
	//打开文件
	HANDLE hFile = CreateFileA(szFile, GENERIC_ALL, FALSE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		printf("无法打开此文件\n");
		return NULL;
	}
	//获取文件大小
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	if (dwFileSize == INVALID_FILE_SIZE) {
		printf("文件为空\n");
		CloseHandle(hFile);
		return NULL;
	}
	m_FileSize = dwFileSize;
	//分配缓冲空间
	char* Buffer = new char[dwFileSize + m_dwBufferExtraSize] {0};  // 多申请的空间用于存放新区段
	//读取内存
	DWORD NumberOfBytesRead = 0;
	BOOL ResRead = ReadFile(hFile, Buffer, dwFileSize, &NumberOfBytesRead, NULL);
	if (ResRead == FALSE) {
		printf("读取文件失败\n");
		CloseHandle(hFile);
		return NULL;
	}
	CloseHandle(hFile);
	return Buffer;
}


//DLL加载到内存
char* CPEinfo::Load(char* szFile)
{
	//加载DLL
	HMODULE hStub = LoadLibraryExA(szFile, NULL, DONT_RESOLVE_DLL_REFERENCES);
	if (hStub == NULL) {
		return NULL;
	}
	return (char*)hStub;
}

BOOL CPEinfo::IsPE(char* Buffer)
{
	IMAGE_DOS_HEADER* pDosHeader = (IMAGE_DOS_HEADER*)Buffer;
	char sign[3] = "MZ";
	if (pDosHeader->e_magic != 0x5a4d) {
		return FALSE;
	}
	return TRUE;
}

BOOL CPEinfo::Analyze(char* Buffer)
{
	DWORD dwBuffer = (DWORD)Buffer;
	m_dwBufferBase = dwBuffer;
	IMAGE_DOS_HEADER* pDosHeader = (IMAGE_DOS_HEADER*)Buffer;
	DWORD dwNtHeaderRVA = pDosHeader->e_lfanew;
	IMAGE_NT_HEADERS32* pNtHeader = (IMAGE_NT_HEADERS32*)(dwBuffer + dwNtHeaderRVA);
	m_pFileHeader = (IMAGE_FILE_HEADER*)&(pNtHeader->FileHeader);
	m_pOptionalHeader = (IMAGE_OPTIONAL_HEADER*)&pNtHeader->OptionalHeader;
	m_pSectionHeader0 = (IMAGE_SECTION_HEADER*)((DWORD)m_pOptionalHeader + m_pFileHeader->SizeOfOptionalHeader);
	return TRUE;
}


IMAGE_SECTION_HEADER* CPEinfo::GetSectionByName(char* name)
{
	for (DWORD i = 0; i < m_pFileHeader->NumberOfSections; i++) {
		IMAGE_SECTION_HEADER* pHeader = m_pSectionHeader0 + i;
		char* sectionName = (char*)pHeader->Name;
		if (strcmp(sectionName, name) == 0) {
			return pHeader;
		}
	}
	return NULL;
}

//新区段名字, 新区段大小
BOOL CPEinfo::AddNewSection(char* chNewName, DWORD dwNewRawDataSize)
{
	if (dwNewRawDataSize > m_dwBufferExtraSize) {
		printf("exe的新区段缓冲空间不足: buffer: %d , Data: %d\n", m_dwBufferExtraSize, dwNewRawDataSize);
		return FALSE;	
	}
	DWORD dwNewVirtualSize = dwNewRawDataSize; //无需内存对齐
	//获取最后一个区段的数据
	DWORD dwNumSection = m_pFileHeader->NumberOfSections;
	//最后一个区段
	IMAGE_SECTION_HEADER* pSectionLast = m_pSectionHeader0 + dwNumSection - 1;
	/*******计算新区段基本数据*******/
	//1. FOA PointerToRawData
	DWORD dwFileAlignment = m_pOptionalHeader->FileAlignment;
	DWORD dwNewPointerToRawData = m_FileSize; 
	if (m_FileSize % dwFileAlignment != 0) {
		dwNewPointerToRawData = m_FileSize - m_FileSize % dwFileAlignment + dwFileAlignment; //文件对齐后的值, 作为FOA
	}
	//2. sizeOfRawData
	DWORD dwNewSizeOfRawData = dwNewRawDataSize;//参数
	if (dwNewSizeOfRawData % dwFileAlignment != 0) {
		dwNewSizeOfRawData = dwNewSizeOfRawData - dwNewSizeOfRawData % dwFileAlignment + dwFileAlignment;  // 文件粒度对齐后作为 FSize;
	}
	//3. virtualAddress: RVA
	//	3.1 获取上个区段的内存中的大小
	DWORD dwLastSectionVirtualSize = pSectionLast->Misc.VirtualSize;//求取最后区段的最大大小
	if (dwLastSectionVirtualSize >  pSectionLast->SizeOfRawData) {
		printf("note: 最后区段的 VirtualSize > SizeOfRawData, 将做处理\n");
		dwLastSectionVirtualSize = pSectionLast->SizeOfRawData;
	}
	//	3. 2 内存粒度对齐
	DWORD dwSectAlignent = m_pOptionalHeader->SectionAlignment;
	if (dwLastSectionVirtualSize % dwSectAlignent != 0) {
		dwLastSectionVirtualSize = dwLastSectionVirtualSize - dwLastSectionVirtualSize % dwSectAlignent + dwSectAlignent;
	}
	DWORD dwNewSectionRVA = pSectionLast->VirtualAddress + dwLastSectionVirtualSize;
	//	3.3 额外的检测
	if (dwNewSectionRVA < m_pOptionalHeader->SizeOfImage) {
		printf("error:must check: 新区段的RVA < SizeOfImage \n");
	}
	//4. virtualSize  ; 用户传参
	DWORD dwNewSectionVirtualSize = dwNewVirtualSize; //不需要内存粒度对齐

	//5. 最后的区段信息的赋值
	//	5.1 区段数量
	m_pFileHeader->NumberOfSections += 1;
	//	5.2 SizeOfImage ; +新区段内存粒度对齐; 还需要判断是否已经对齐了, 以及跟物理size的比较
	m_pOptionalHeader->SizeOfImage += (dwNewSectionVirtualSize - dwNewSectionVirtualSize % dwSectAlignent + dwSectAlignent);
	//	5.3 新区段表信息
	IMAGE_SECTION_HEADER* pNewSectionHeader = pSectionLast + 1;
	memcpy_s(pNewSectionHeader->Name, 8, chNewName, strlen(chNewName)+1); //必须把空格也加上
	pNewSectionHeader->Misc.VirtualSize = dwNewVirtualSize;
	pNewSectionHeader->VirtualAddress = dwNewSectionRVA;
	pNewSectionHeader->SizeOfRawData = dwNewSizeOfRawData;
	pNewSectionHeader->PointerToRawData = dwNewPointerToRawData;
	pNewSectionHeader->Characteristics = 0xE00000E0;
	//新的文件大小
	//DWORD dwNewFileSize = pNewSectionHeader->PointerToRawData + pNewSectionHeader->SizeOfRawData;
	////写入文件
	//memcpy_s(m_szNewFilePath + strlen(m_szNewFilePath)-4, 255, "_.exe", 5);
	//HANDLE hNewFile = CreateFileA(m_szNewFilePath, GENERIC_ALL, NULL, NULL, CREATE_ALWAYS, NULL, NULL);
	//WriteFile(hNewFile, (char*)m_dwBufferBase, dwNewFileSize, NULL, NULL);
	//CloseHandle(hNewFile);
	return TRUE;

}
