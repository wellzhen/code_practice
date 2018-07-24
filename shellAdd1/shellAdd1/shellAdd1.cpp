// shellAdd1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "PEinfo.h"
#include "../stub/stubconf.h"

BOOL FixStubReloc(CPEinfo* pStubInfo, CPEinfo* pExeInfo);

int _tmain(int argc, _TCHAR argv[])
{
	char szFile[255]{ 0 };
	printf("PE·��:  ");
	scanf_s("%s", szFile, 255);
	//����exe�ļ�
	CPEinfo*  pExeInfo = new CPEinfo(szFile, TRUE);
	//����stub.dll
	CPEinfo*  pStubInfo = new CPEinfo("W:\\code_practice\\shellAdd1\\bin\\stub.dll", FALSE);

	//��ȡstub����ε���Ϣ
	IMAGE_SECTION_HEADER* pStubTextSectionHeader = pStubInfo->GetSectionByName(".text");
	if (pStubTextSectionHeader == NULL) {
		printf("�޷���ȡ.text���α���Ϣ\n");
		return 0;
	}
	//���һ���µ����ε�exe
	char chNewSectionName[8] = "moon";
	BOOL AddRes = pExeInfo->AddNewSection(chNewSectionName, pStubTextSectionHeader->SizeOfRawData);
	if (AddRes == FALSE) {
		printf("buffer�ռ䲻��\n");
		system("pause");
	}

	//�޸�Stub��.text�ε��ض�λ(�ض�λ��ַ������RVA)
	FixStubReloc(pStubInfo, pExeInfo);

	//�ض�λ��������start��RVA: star����Ҫ��Ϊexe����OEP
	DWORD dwStubStartRVA = (DWORD)GetProcAddress((HMODULE)pStubInfo->m_dwBufferBase, "start") - pStubInfo->m_dwBufferBase; //GetProcAddress()�������VA,����RVA
	dwStubStartRVA -= pStubTextSectionHeader->VirtualAddress; //�޸ĵ����ε�RVA
	IMAGE_SECTION_HEADER* pExeLastSection = pExeInfo->m_pSectionHeader0 + pExeInfo->m_pFileHeader->NumberOfSections - 1;
	dwStubStartRVA += pExeLastSection->VirtualAddress;

	//OEP����: ����exe��OEP, �޸�exe��OEP
	//   ����exe������ StubConf: oep��DataDir
	StubConf* stubConf = (StubConf*)GetProcAddress((HMODULE)pStubInfo->m_dwBufferBase, "g_conf");
	stubConf->dwOEP = pExeInfo->m_pOptionalHeader->AddressOfEntryPoint;  // ����exe��ԭʼOEP
	//	 �޸�exe��OEP, ָ��start����
	pExeInfo->m_pOptionalHeader->AddressOfEntryPoint = dwStubStartRVA;


	//����exe������Ŀ¼��stubConf
	memcpy_s(stubConf->dataDir,sizeof(IMAGE_DATA_DIRECTORY)*16, pExeInfo->m_pOptionalHeader->DataDirectory, sizeof(IMAGE_DATA_DIRECTORY) * 16);
	
	//��stub.dll�Ĵ���ο���exe : note: Ҫ�ӻ�ַ
	memcpy_s((char*)(pExeLastSection->PointerToRawData + pExeInfo->m_dwBufferBase), pStubTextSectionHeader->SizeOfRawData,
			(char*)(pStubTextSectionHeader->VirtualAddress + pStubInfo->m_dwBufferBase), pStubTextSectionHeader->SizeOfRawData);

	//�µ��ļ���С: ���ڱ����ļ�
	DWORD dwNewFileSize = pExeLastSection->PointerToRawData + pStubTextSectionHeader->SizeOfRawData;
	// ��exe������Ŀ¼���
	ZeroMemory(pExeInfo->m_pOptionalHeader->DataDirectory, sizeof(IMAGE_DATA_DIRECTORY) * 16);

	//д���ļ�
	memcpy_s(pExeInfo->m_szNewFilePath + strlen(pExeInfo->m_szNewFilePath) - 4, 255, "_.exe", 5);
	HANDLE hNewFile = CreateFileA(pExeInfo->m_szNewFilePath, GENERIC_ALL, NULL, NULL, CREATE_ALWAYS, NULL, NULL);
	WriteFile(hNewFile, (char*)pExeInfo->m_dwBufferBase, dwNewFileSize, NULL, NULL);
	CloseHandle(hNewFile);
    return 0;
}

BOOL FixStubReloc(CPEinfo* pStubInfo, CPEinfo* pExeInfo)
{
	//Stub�ض�λ��
	IMAGE_DATA_DIRECTORY RelocTableDir = pStubInfo->m_pOptionalHeader->DataDirectory[5];
	DWORD dwRelocTableRVA = RelocTableDir.VirtualAddress;
	DWORD dwRelocTableVA = dwRelocTableRVA + pStubInfo->m_dwBufferBase;
	IMAGE_BASE_RELOCATION*  baseReloc = (IMAGE_BASE_RELOCATION*)dwRelocTableVA;
	typedef struct __TypeOffset {
		WORD offset : 12; //ƫ����
		WORD type : 4;  //�ض�λ����
	} TypeOffset;
	while (baseReloc->SizeOfBlock != 0) {
		DWORD count = (baseReloc->SizeOfBlock - 8) / 2; //��Ҫ�ض�λ�ĸ���
		for (DWORD i = 0; i < count; i++) {
			TypeOffset* pTypeOffset = (TypeOffset*)((DWORD)baseReloc + 8 + i * 2); //��ַͨ��i����
			IMAGE_SECTION_HEADER* pStubTextSectionHeader = pStubInfo->GetSectionByName(".text"); //��ȡstub����ε���Ϣ
			IMAGE_SECTION_HEADER* pExeTextSectionHeader = pExeInfo->GetSectionByName("moon"); //��ȡexe����ε���Ϣ
			if (pTypeOffset->type == 3 
				&& baseReloc->VirtualAddress >= pStubTextSectionHeader->VirtualAddress
				&& baseReloc->VirtualAddress <= pStubTextSectionHeader->VirtualAddress + pStubTextSectionHeader->Misc.VirtualSize ) 
			{
				// to do : �޸��ڴ��д����

				DWORD dwNeedRelocRVA = baseReloc->VirtualAddress + pTypeOffset->offset;
				DWORD dwNeedRelocVA = dwNeedRelocRVA + pStubInfo->m_dwBufferBase;
				//�޸ĸ�λ�õ�ֵ
				//	�滻���ػ�ַ
				*(DWORD*)dwNeedRelocVA -= pStubInfo->m_dwBufferBase;
				*(DWORD*)dwNeedRelocVA += pExeInfo->m_pOptionalHeader->ImageBase;
				//	�滻����RVA
				*(DWORD*)dwNeedRelocVA -= pStubTextSectionHeader->VirtualAddress;
				*(DWORD*)dwNeedRelocVA +=  pExeTextSectionHeader->VirtualAddress;
			}
		}
		//baseReloc++; //����, ����++ Ӧ�ü�SizeOfBlock
		baseReloc = (IMAGE_BASE_RELOCATION*)((DWORD)baseReloc + baseReloc->SizeOfBlock);
	}

	return TRUE;
}