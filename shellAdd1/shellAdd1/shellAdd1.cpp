// shellAdd1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "PEinfo.h"
#include "../stub/stubconf.h"

//�޸�stub���ض�λ���virtualAddress;
void FixStubRelocRVA(CPEinfo* pStubInfo, CPEinfo* pExeInfo);
BOOL FixStubTextReloc(CPEinfo* pStubInfo, CPEinfo* pExeInfo);

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
	FixStubTextReloc(pStubInfo, pExeInfo);

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

	//��������
	printf("���������� > ");
	scanf_s("%s", stubConf->szKey, 16);

	//����exe������Ŀ¼��stubConf
	memcpy_s(stubConf->dataDir,sizeof(IMAGE_DATA_DIRECTORY)*16, pExeInfo->m_pOptionalHeader->DataDirectory, sizeof(IMAGE_DATA_DIRECTORY) * 16);
	
	//��stub.dll�Ĵ���ο���exe : note: Ҫ�ӻ�ַ
	memcpy_s((char*)(pExeLastSection->PointerToRawData + pExeInfo->m_dwBufferBase), pStubTextSectionHeader->SizeOfRawData,
			(char*)(pStubTextSectionHeader->VirtualAddress + pStubInfo->m_dwBufferBase), pStubTextSectionHeader->SizeOfRawData);

	
	// ��exe������Ŀ¼���
	//	1. ����TLS
	DWORD dwTlsRVA = pExeInfo->m_pOptionalHeader->DataDirectory[9].VirtualAddress;
	DWORD dwTlsSize = pExeInfo->m_pOptionalHeader->DataDirectory[9].Size;
	if (dwTlsRVA != 0) {
		//	2. ���
		ZeroMemory(pExeInfo->m_pOptionalHeader->DataDirectory, sizeof(IMAGE_DATA_DIRECTORY) * 16);
		//	3. �ָ�TLS����Ŀ¼
		pExeInfo->m_pOptionalHeader->DataDirectory[9].VirtualAddress = dwTlsRVA;
		pExeInfo->m_pOptionalHeader->DataDirectory[9].Size = dwTlsSize;
		//	4. ת����FOA
		DWORD dwTlsFOA = pExeInfo->RVA2FOA(dwTlsRVA);
		if (dwTlsFOA == 0) {
			MessageBoxA(NULL, "�޷�ת����FOA", "note", MB_OK);
			return 0;
		}
		//  4. ���TLS�Ļص�������: 
		IMAGE_TLS_DIRECTORY* pTlsDir = (IMAGE_TLS_DIRECTORY*)(dwTlsFOA+ pExeInfo->m_dwBufferBase);
		DWORD dwAddrOfCallBackRVA = (pTlsDir->AddressOfCallBacks - pExeInfo->m_pOptionalHeader->ImageBase);
		DWORD dwAddrOfCallBackFOA = pExeInfo->RVA2FOA(dwAddrOfCallBackRVA);
		DWORD* pCallBack = (DWORD*)(dwAddrOfCallBackFOA+pExeInfo->m_dwBufferBase);
		DWORD index = 0;
		while (*pCallBack != 0) {
			//����
			stubConf->dwTlsCallBackValue[index] = *pCallBack;
			//���
			DWORD dwOldProtect;
			VirtualProtect((char*)pCallBack, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect);
			*pCallBack = 0;
			VirtualProtect((char*)pCallBack, 4, dwOldProtect, &dwOldProtect);

			pCallBack++;
			index++;

		}

		
	}
	else {
		ZeroMemory(pExeInfo->m_pOptionalHeader->DataDirectory, sizeof(IMAGE_DATA_DIRECTORY) * 16);
	}



	//����
	pExeInfo->Encrypt(stubConf);

	//�޸�������stub���ض�λ��, ���½����µ�����
	FixStubRelocRVA(pStubInfo, pExeInfo);
	pExeLastSection++;
	//�µ��ļ���С: ���ڱ����ļ�
	//д���ļ�
	DWORD dwNewFileSize = pExeLastSection->PointerToRawData + pStubTextSectionHeader->SizeOfRawData;
	memcpy_s(pExeInfo->m_szNewFilePath + strlen(pExeInfo->m_szNewFilePath) - 4, 255, "_.exe", 5);
	HANDLE hNewFile = CreateFileA(pExeInfo->m_szNewFilePath, GENERIC_ALL, NULL, NULL, CREATE_ALWAYS, NULL, NULL);
	WriteFile(hNewFile, (char*)pExeInfo->m_dwBufferBase, dwNewFileSize, NULL, NULL);
	CloseHandle(hNewFile);
    return 0;
}

//֧�������ַ: �޸�.reloc���ε�VirtualAddress��Ϣ
void FixStubRelocRVA(CPEinfo* pStubInfo, CPEinfo* pExeInfo)
{
	//exe
	IMAGE_SECTION_HEADER* pExeLastSection = pExeInfo->m_pSectionHeader0 + pExeInfo->m_pFileHeader->NumberOfSections - 1;
	DWORD dwNewSectionRVA = pExeLastSection->VirtualAddress;
	//stub
	IMAGE_DATA_DIRECTORY RelocTableDir = pStubInfo->m_pOptionalHeader->DataDirectory[5];
	DWORD dwRelocSectionSize = RelocTableDir.Size;
	DWORD dwRelocVA = RelocTableDir.VirtualAddress + pStubInfo->m_dwBufferBase;
	IMAGE_BASE_RELOCATION* pBaseReloc = (IMAGE_BASE_RELOCATION*)dwRelocVA;
	//���������ض�λ��, ���ڴ���ε�RVA ���޸�Ϊ��Ӧexe��RVA
	DWORD dwTextRVAmin = pStubInfo->GetSectionByName(".text")->VirtualAddress;
	DWORD dwTextRVAmax = dwTextRVAmin + pStubInfo->GetSectionByName(".text")->Misc.VirtualSize;
	char* dwCopyAddrStart = (char*)pBaseReloc;
	char* dwCopyAddrEnd = 0;
	while(pBaseReloc->SizeOfBlock != 0) {
		//�ж��Ƿ�����text�ε�
		DWORD dwRelocRVA = pBaseReloc->VirtualAddress;
		if (dwRelocRVA > dwTextRVAmin && dwRelocRVA < dwTextRVAmax) {
			DWORD dwOldProtect;
			VirtualProtect((char*)pBaseReloc, 8, PAGE_EXECUTE_READWRITE, &dwOldProtect);
			pBaseReloc->VirtualAddress -= dwTextRVAmin;
			//DWORD dwExeEndRVA = pExeLastSection->VirtualAddress + pExeLastSection->Misc.VirtualSize;
			pBaseReloc->VirtualAddress += pExeLastSection->VirtualAddress;
			VirtualProtect((char*)pBaseReloc, 8, dwOldProtect, &dwOldProtect);
		}
		else {//���ڴ������
			dwCopyAddrEnd = (char*)pBaseReloc; // ��һ���ֽ�
			break;
		}
		pBaseReloc = (IMAGE_BASE_RELOCATION*)((DWORD)pBaseReloc + pBaseReloc->SizeOfBlock);
	}

	// exe����һ���µ�����stubRel 
	// ���޸�m_FileSize ���� 
	pExeInfo->m_FileSize += pExeLastSection->SizeOfRawData; 
	DWORD dwRelocFSize = pStubInfo->GetSectionByName(".reloc")->SizeOfRawData;
	pExeInfo->AddNewSection("stubRel", dwRelocFSize);
	//��.reloc����Ϣ������ȥ
	pExeLastSection++;
	char* destAddr = (char*)(pExeLastSection->PointerToRawData + pExeInfo->m_dwBufferBase);
	char* srcAddr = (char*)(pStubInfo->GetSectionByName(".reloc")->VirtualAddress + pStubInfo->m_dwBufferBase);
	DWORD copyLength = (DWORD)dwCopyAddrEnd - (DWORD)dwCopyAddrStart;
	memcpy_s(destAddr, copyLength, srcAddr, copyLength);
	//�޸��ض�λ��Ŀ¼��RVA��Size
	pExeInfo->m_pOptionalHeader->DataDirectory[5].VirtualAddress = pExeLastSection->VirtualAddress;
	pExeInfo->m_pOptionalHeader->DataDirectory[5].Size = copyLength;
}

BOOL FixStubTextReloc(CPEinfo* pStubInfo, CPEinfo* pExeInfo)
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



