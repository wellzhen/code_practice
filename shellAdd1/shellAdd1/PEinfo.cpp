#include "stdafx.h"
#include "PEinfo.h"


CPEinfo::CPEinfo(char* szFile, BOOL isExe)
{
	//�����ļ����ڴ�
	m_dwBufferExtraSize = 0x100000; //�ʵ��޸�
	char* Buffer;
	if (isExe) {
		Buffer = Open(szFile);
	}
	else {
		Buffer = Load(szFile);
	}
	
	if (Buffer == NULL) {
		printf("�ļ�����ʧ��\n");
		return;
	}

	if (!IsPE(Buffer)) {
		printf("������Ч��PE�ļ�\n");
		return;
	}
	
	//�����ļ�·��
	memcpy_s(m_szNewFilePath, 255, szFile, strlen(szFile));
	//��������Ҫ������
	Analyze(Buffer);
	//�������, �ֶ�����
	//AddNewSection(Buffer);
	

}



CPEinfo::~CPEinfo()
{
}


//�ļ����ص��ڴ�
char* CPEinfo::Open(char* szFile)
{
	//���ļ�
	HANDLE hFile = CreateFileA(szFile, GENERIC_ALL, FALSE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		printf("�޷��򿪴��ļ�\n");
		return NULL;
	}
	//��ȡ�ļ���С
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	if (dwFileSize == INVALID_FILE_SIZE) {
		printf("�ļ�Ϊ��\n");
		CloseHandle(hFile);
		return NULL;
	}
	m_FileSize = dwFileSize;
	//���仺��ռ�
	char* Buffer = new char[dwFileSize + m_dwBufferExtraSize] {0};  // ������Ŀռ����ڴ��������
	//��ȡ�ڴ�
	DWORD NumberOfBytesRead = 0;
	BOOL ResRead = ReadFile(hFile, Buffer, dwFileSize, &NumberOfBytesRead, NULL);
	if (ResRead == FALSE) {
		printf("��ȡ�ļ�ʧ��\n");
		CloseHandle(hFile);
		return NULL;
	}
	CloseHandle(hFile);
	return Buffer;
}


//DLL���ص��ڴ�
char* CPEinfo::Load(char* szFile)
{
	//����DLL
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

//����������, �����δ�С
BOOL CPEinfo::AddNewSection(char* chNewName, DWORD dwNewRawDataSize)
{
	if (dwNewRawDataSize > m_dwBufferExtraSize) {
		printf("exe�������λ���ռ䲻��: buffer: %d , Data: %d\n", m_dwBufferExtraSize, dwNewRawDataSize);
		return FALSE;	
	}
	DWORD dwNewVirtualSize = dwNewRawDataSize; //�����ڴ����
	//��ȡ���һ�����ε�����
	DWORD dwNumSection = m_pFileHeader->NumberOfSections;
	//���һ������
	IMAGE_SECTION_HEADER* pSectionLast = m_pSectionHeader0 + dwNumSection - 1;
	/*******���������λ�������*******/
	//1. FOA PointerToRawData
	DWORD dwFileAlignment = m_pOptionalHeader->FileAlignment;
	DWORD dwNewPointerToRawData = m_FileSize; 
	if (m_FileSize % dwFileAlignment != 0) {
		dwNewPointerToRawData = m_FileSize - m_FileSize % dwFileAlignment + dwFileAlignment; //�ļ�������ֵ, ��ΪFOA
	}
	//2. sizeOfRawData
	DWORD dwNewSizeOfRawData = dwNewRawDataSize;//����
	if (dwNewSizeOfRawData % dwFileAlignment != 0) {
		dwNewSizeOfRawData = dwNewSizeOfRawData - dwNewSizeOfRawData % dwFileAlignment + dwFileAlignment;  // �ļ����ȶ������Ϊ FSize;
	}
	//3. virtualAddress: RVA
	//	3.1 ��ȡ�ϸ����ε��ڴ��еĴ�С
	DWORD dwLastSectionVirtualSize = pSectionLast->Misc.VirtualSize;//��ȡ������ε�����С
	if (dwLastSectionVirtualSize >  pSectionLast->SizeOfRawData) {
		printf("note: ������ε� VirtualSize > SizeOfRawData, ��������\n");
		dwLastSectionVirtualSize = pSectionLast->SizeOfRawData;
	}
	//	3. 2 �ڴ����ȶ���
	DWORD dwSectAlignent = m_pOptionalHeader->SectionAlignment;
	if (dwLastSectionVirtualSize % dwSectAlignent != 0) {
		dwLastSectionVirtualSize = dwLastSectionVirtualSize - dwLastSectionVirtualSize % dwSectAlignent + dwSectAlignent;
	}
	DWORD dwNewSectionRVA = pSectionLast->VirtualAddress + dwLastSectionVirtualSize;
	//	3.3 ����ļ��
	if (dwNewSectionRVA < m_pOptionalHeader->SizeOfImage) {
		printf("error:must check: �����ε�RVA < SizeOfImage \n");
	}
	//4. virtualSize  ; �û�����
	DWORD dwNewSectionVirtualSize = dwNewVirtualSize; //����Ҫ�ڴ����ȶ���

	//5. ����������Ϣ�ĸ�ֵ
	//	5.1 ��������
	m_pFileHeader->NumberOfSections += 1;
	//	5.2 SizeOfImage ; +�������ڴ����ȶ���; ����Ҫ�ж��Ƿ��Ѿ�������, �Լ�������size�ıȽ�
	m_pOptionalHeader->SizeOfImage += (dwNewSectionVirtualSize - dwNewSectionVirtualSize % dwSectAlignent + dwSectAlignent);
	//	5.3 �����α���Ϣ
	IMAGE_SECTION_HEADER* pNewSectionHeader = pSectionLast + 1;
	memcpy_s(pNewSectionHeader->Name, 8, chNewName, strlen(chNewName)+1); //����ѿո�Ҳ����
	pNewSectionHeader->Misc.VirtualSize = dwNewVirtualSize;
	pNewSectionHeader->VirtualAddress = dwNewSectionRVA;
	pNewSectionHeader->SizeOfRawData = dwNewSizeOfRawData;
	pNewSectionHeader->PointerToRawData = dwNewPointerToRawData;
	pNewSectionHeader->Characteristics = 0xE00000E0;
	//�µ��ļ���С
	//DWORD dwNewFileSize = pNewSectionHeader->PointerToRawData + pNewSectionHeader->SizeOfRawData;
	////д���ļ�
	//memcpy_s(m_szNewFilePath + strlen(m_szNewFilePath)-4, 255, "_.exe", 5);
	//HANDLE hNewFile = CreateFileA(m_szNewFilePath, GENERIC_ALL, NULL, NULL, CREATE_ALWAYS, NULL, NULL);
	//WriteFile(hNewFile, (char*)m_dwBufferBase, dwNewFileSize, NULL, NULL);
	//CloseHandle(hNewFile);
	return TRUE;

}
