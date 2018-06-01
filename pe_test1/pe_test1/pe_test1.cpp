// pe_test1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>

//�������
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
DWORD RVA2FOA(DWORD RVA);
IMAGE_SECTION_HEADER* GetSectionHeaderByRva(DWORD RVA);
DWORD GetSectionFoaByRva(DWORD RVA);
bool ShowExportTableInfo();
bool ShowImportTableInfo();
bool ShowResourceTableInfo();
bool ShowRelocationInfo();

int _tmain(int argc, _TCHAR* argv[])
{
	WCHAR* pFileName = L"C:\\Users\\moonq\\Desktop\\dll\\Network.dll";
	//WCHAR* pFileName = L"C:\\Users\\moonq\\Desktop\\dll\\TM2.exe";
	if (!LoadFile(pFileName)) {
		return 0;
	}
	if (!IsPeFile()) {
		return 0;
	}
	//ShowExportTableInfo();
	//ShowImportTableInfo();
	//ShowResourceTableInfo();
	ShowRelocationInfo();
	return 0;
}

BOOL LoadFile(WCHAR* pFileName)
{
	HANDLE hFile = CreateFile(pFileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		printf("���ļ�ʧ��\n");
		return FALSE;
	}
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	if (dwFileSize == INVALID_FILE_SIZE) {
		printf("�޷���ȡ�ļ���С\n");
		CloseHandle(hFile);
		return FALSE;
	}
	g_pFileBuffer = new char[dwFileSize];
	ZeroMemory(g_pFileBuffer, dwFileSize);
	BOOL  bRead = ReadFile(hFile, g_pFileBuffer, dwFileSize, NULL, NULL);
	if (bRead == FALSE) {
		printf("�޷���ȡ�ļ�����\n");
		CloseHandle(hFile);
		return FALSE;
	}
	g_pDosHeader = (IMAGE_DOS_HEADER*)g_pFileBuffer;
	g_pNtHeaders = (IMAGE_NT_HEADERS*)(g_pDosHeader->e_lfanew + g_pFileBuffer); // error + fileBase
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
		printf("û��MZǩ��\n");
		return FALSE;
	}
	if (g_pNtHeaders->Signature != IMAGE_NT_SIGNATURE) {
		printf("û��NTͷ��PEǩ��\n");
		return FALSE;
	}
	return TRUE;
}

DWORD RVA2FOA(DWORD RVA)
{
	WORD dwCount = g_pFileHeader->NumberOfSections;
	IMAGE_SECTION_HEADER* pSectionHeader = g_pSectionHeader;
	BOOL bFind = false;
	for (WORD i = 0; i < dwCount; i++) {
		//if (RVA >= pSectionHeader->PointerToRawData && RVA < (pSectionHeader->PointerToRawData + pSectionHeader->SizeOfRawData)) {
		if(RVA >=pSectionHeader->VirtualAddress && RVA < (pSectionHeader->VirtualAddress + pSectionHeader->Misc.VirtualSize)) {
			bFind = true;
			break;
		}
		pSectionHeader++;
	}
	if (!bFind) {
		printf("RVA2FOAת��ʧ��\n");
		return 0;
	}
	return RVA - pSectionHeader->VirtualAddress + pSectionHeader->PointerToRawData;
	
}

DWORD GetSectionFoaByRva(DWORD RVA)
{
	WORD dwCount = g_pFileHeader->NumberOfSections;
	IMAGE_SECTION_HEADER* pSectionHeader = g_pSectionHeader;
	BOOL bFind = false;
	for (WORD i = 0; i < dwCount; i++) {
		//if (RVA >= pSectionHeader->PointerToRawData && RVA < (pSectionHeader->PointerToRawData + pSectionHeader->SizeOfRawData)) {
		if(RVA >=pSectionHeader->VirtualAddress && RVA < (pSectionHeader->VirtualAddress + pSectionHeader->Misc.VirtualSize)) {
			bFind = true;
			break;
		}
		pSectionHeader++;
	}
	if (!bFind) {
		printf("RVA2FOAת��ʧ��\n");
		return 0;
	}
	return pSectionHeader->PointerToRawData;
}

IMAGE_SECTION_HEADER* GetSectionHeaderByRva(DWORD RVA)
{
	WORD dwCount = g_pFileHeader->NumberOfSections;
	IMAGE_SECTION_HEADER* pSectionHeader = g_pSectionHeader;
	BOOL bFind = false;
	for (WORD i = 0; i < dwCount; i++) {
		//if (RVA >= pSectionHeader->PointerToRawData && RVA < (pSectionHeader->PointerToRawData + pSectionHeader->SizeOfRawData)) {
		if(RVA >=pSectionHeader->VirtualAddress && RVA < (pSectionHeader->VirtualAddress + pSectionHeader->Misc.VirtualSize)) {
			bFind = true;
			break;
		}
		pSectionHeader++;
	}
	if (!bFind) {
		printf("RVA2FOAת��ʧ��\n");
		return 0;
	}
	return pSectionHeader;

}

bool ShowExportTableInfo()
{
	if (g_pDataDir[0].Size == 0) {
		printf("û�е�����\n");
		return FALSE;
	}
	//��չͷ�еĵ�����VirtualAddress
	DWORD VirtualAddress = g_pDataDir[0].VirtualAddress;
	DWORD ExportDirOffset = RVA2FOA(VirtualAddress);
	IMAGE_EXPORT_DIRECTORY* pExportDir = (IMAGE_EXPORT_DIRECTORY*)(ExportDirOffset + (DWORD)g_pFileBuffer);  // error: ���ϻ�ַ
	DWORD dwFunctions = pExportDir->NumberOfFunctions;
	DWORD dwNames = pExportDir->NumberOfNames;

	
	// ����������ַ��
	printf("-------------������--------------\n");
	printf("dll name: %s\n", (char*)(RVA2FOA(pExportDir->Name) + (DWORD)g_pFileBuffer));
	for (DWORD i = 0; i < dwFunctions; i++) {
		DWORD dwFunRva = *(DWORD*)(RVA2FOA(pExportDir->AddressOfFunctions + 4*i) + (DWORD)g_pFileBuffer); // ��ǰ������RVAֵ: ���ֵ
		DWORD dwFunAddrOfFile = RVA2FOA(dwFunRva) + (DWORD)g_pFileBuffer; // ������ƫ�� 
		if (*(DWORD*)dwFunAddrOfFile == 0) {
			printf("��Ч��ַ\n");
			continue;
		}
		printf("ordinals: %X	;", i + pExportDir->Base);
		DWORD dwNameRva = *(DWORD*)(RVA2FOA(pExportDir->AddressOfNames + i * 4) + (DWORD)g_pFileBuffer); // ��������RVA : ���ֵ
		printf("RVA: %X	;",  dwFunRva);
		printf("offset: %X	;", RVA2FOA(dwFunRva));
		//>>>> ���Ҷ�Ӧ�ĺ�����
		//������ű�
		for (DWORD j = 0; j < dwNames; j++) {
			DWORD dwOrdFoa = RVA2FOA(pExportDir->AddressOfNameOrdinals + j * 2);  // error: ��ű���word����, һ�μ������ֽ�
			DWORD dwOrdAddrOfFile = dwOrdFoa + (DWORD)g_pFileBuffer;
			WORD ordValue = *(WORD*)dwOrdAddrOfFile;
			if (*(WORD*)dwOrdAddrOfFile == i) {  // WORD����ָ��...
				// ֱ�ӻ�ȡ��Ӧ�±�ĺ�����
				DWORD dwNameRva =*(DWORD*) (RVA2FOA(pExportDir->AddressOfNames + 4 * j) + (DWORD)g_pFileBuffer);
				DWORD dwNameFoa = RVA2FOA(dwNameRva);
				DWORD dwNameAddrOfFile = dwNameFoa + (DWORD)g_pFileBuffer;
				printf("funName: %s", (char*)dwNameAddrOfFile);
				break;
			}
		}

		printf("\n");

	}
	
	return TRUE;
}

bool ShowImportTableInfo()
{
	DWORD virtualAddress = g_pDataDir[1].VirtualAddress;
	DWORD dwImportDescriptorFoa = RVA2FOA(virtualAddress);
	DWORD dwImportDescriptorRva = dwImportDescriptorFoa + (DWORD)g_pFileBuffer;
	IMAGE_IMPORT_DESCRIPTOR* pImportTable = (IMAGE_IMPORT_DESCRIPTOR*)dwImportDescriptorRva;
	
	printf("---------�������Ϣ-----------\n");
	while (pImportTable->Name) {
		DWORD dwNameRva = pImportTable->Name;
		DWORD dwNameFoa = RVA2FOA(dwNameRva);
		DWORD dwNameAddrOfFile = dwNameFoa + (DWORD)g_pFileBuffer;
		printf("DllName: %s	;", (char*)dwNameAddrOfFile);
		printf("ORiginalFirst Thunk: %X\n", pImportTable->OriginalFirstThunk);

		//INT��
		DWORD dwOriginalThunkRva = pImportTable->OriginalFirstThunk;
		DWORD dwOriginalThunkFoa = RVA2FOA(dwOriginalThunkRva);
		DWORD dwOriginalThunkAddr = dwOriginalThunkFoa + (DWORD)g_pFileBuffer;
		IMAGE_THUNK_DATA32* pINT = (IMAGE_THUNK_DATA32*)dwOriginalThunkAddr;

		int i = 0;
		while (pINT->u1.Ordinal) {
			printf("     ThunkRVA: %X  ", dwOriginalThunkRva + i*sizeof(IMAGE_THUNK_DATA32));
			printf("ThunkOffset: %X  ", dwOriginalThunkFoa + i * sizeof(IMAGE_THUNK_DATA32));
			printf("ThunkValue: %X  ", pINT->u1.Ordinal);
			i++;
			if (pINT->u1.Ordinal >> 31 == 1) { // ���λ��1 , ��ŵ����
				printf("�������: %04X  ������: null, \n", pINT->u1.Ordinal & 0xFFFF);
			}
			else {
				//���������Ƶ����
				DWORD AddressOfData = pINT->u1.AddressOfData;
				DWORD dwNameFoa = RVA2FOA(AddressOfData);
				DWORD dwNameStructAddrOfFile = dwNameFoa + (DWORD)g_pFileBuffer;
				IMAGE_IMPORT_BY_NAME* pImportName = (IMAGE_IMPORT_BY_NAME*)dwNameStructAddrOfFile;
				printf("Hint: %04X  ������: %s\n", pImportName->Hint, (char*)pImportName->Name);
			}
			pINT++;
		}


		pImportTable++;
		printf("\n");
	}

	return 0;

}


bool ShowResourceTableInfo()
{
	//
	WCHAR*  pResourceType[] = { L"0", L"���ָ��",L"bitmap",L"icon", L"menu", L"dialog", L"string table", L"fontDir", L"font", L"shortCut", L"noFormatResource", L"MessageList", L"mouserCursorGroup",L"D",  L"iconGroup",L"F", L"versionInfo"   };
	DWORD VirtualAddress = g_pDataDir[2].VirtualAddress;
	DWORD dwResourceDirFoa = RVA2FOA(VirtualAddress);
	DWORD dwResourceDirAddressOfFile = dwResourceDirFoa + (DWORD)g_pFileBuffer;
	IMAGE_RESOURCE_DIRECTORY*  pResourceDir = (IMAGE_RESOURCE_DIRECTORY*)dwResourceDirAddressOfFile;
	// ��һ�� : ��Դ�������
	DWORD dwNumberOfNamedEntries = pResourceDir->NumberOfNamedEntries;
	DWORD dwNumberOfIdEntries = pResourceDir->NumberOfIdEntries;
	DWORD dwEntryCount = dwNumberOfNamedEntries + dwNumberOfIdEntries;
	printf("------��Դ-------\n");
	printf("������Ŀ����: %d\n", dwNumberOfNamedEntries);
	printf("id  ��Ŀ����: %d\n", dwNumberOfIdEntries);

	IMAGE_RESOURCE_DIRECTORY_ENTRY* pResourceDirEntry = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)(dwResourceDirAddressOfFile + sizeof(IMAGE_RESOURCE_DIRECTORY));
	for (DWORD i = 0; i < dwEntryCount; i++) {
		//�ж����ַ�����Դ����id��Դ
		if (pResourceDirEntry->NameIsString) {
			//����������
			DWORD dwNameOffset = pResourceDirEntry->NameOffset;
			DWORD sectionFoa = GetSectionFoaByRva(VirtualAddress);
			DWORD dwNameAddrOfFile = dwNameOffset + sectionFoa + (DWORD)g_pFileBuffer;  // error ��Ҫ�ӻ�ַfileBuffer
			IMAGE_RESOURCE_DIR_STRING_U* pDirStringU = (IMAGE_RESOURCE_DIR_STRING_U*)dwNameAddrOfFile;
			DWORD dwStrLen = pDirStringU->Length;
			WCHAR* pStrBuffer = new WCHAR[dwStrLen+ 2];
			ZeroMemory(pStrBuffer, dwStrLen*2 + 2);
			memcpy_s(pStrBuffer, dwStrLen*2, pDirStringU->NameString, dwStrLen*2);
			printf("	NameString: %ls", pStrBuffer);
		}
		else {
			//id������
			DWORD id = pResourceDirEntry->Name;
			if (id <=16) {
				printf("	Name(ID): %ls", pResourceType[id]);
			}
			else {
				printf("	Name(ID): %d", id);
			}
			
		}
		printf("\n");
		//�ڶ���
		if (pResourceDirEntry->DataIsDirectory) {
			
			DWORD  dwOffsetToDirectory = pResourceDirEntry->OffsetToDirectory;
			DWORD  sectionFoa = GetSectionFoaByRva(VirtualAddress);
			DWORD  dwDirectoryAddrOfFile = dwOffsetToDirectory + sectionFoa + (DWORD)g_pFileBuffer;
			IMAGE_RESOURCE_DIRECTORY* pResourceDirectory2 = (IMAGE_RESOURCE_DIRECTORY*)dwDirectoryAddrOfFile;
			//�ڶ������
			DWORD dwNumberOfNamedEntries = pResourceDirectory2->NumberOfNamedEntries;
			DWORD dwNumberOfIdEntries = pResourceDirectory2->NumberOfIdEntries;
			DWORD dwEntryCount = dwNumberOfNamedEntries + dwNumberOfIdEntries;
			IMAGE_RESOURCE_DIRECTORY_ENTRY* pDirEntry2 = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)(pResourceDirectory2 + 1);
			////
			for (DWORD i = 0; i < dwEntryCount; i++) {
				//entry
				if (pDirEntry2->NameIsString) {
					//����������
					DWORD dwNameOffset = pDirEntry2->NameOffset;
					DWORD sectionFoa = GetSectionFoaByRva(VirtualAddress);
					DWORD dwNameAddrOfFile = dwNameOffset + sectionFoa + (DWORD)g_pFileBuffer;  // error ��Ҫ�ӻ�ַfileBuffer
					IMAGE_RESOURCE_DIR_STRING_U* pDirStringU = (IMAGE_RESOURCE_DIR_STRING_U*)dwNameAddrOfFile;
					DWORD dwStrLen = pDirStringU->Length;
					WCHAR* pStrBuffer = new WCHAR[dwStrLen + 2];
					ZeroMemory(pStrBuffer, dwStrLen * 2 + 2);
					memcpy_s(pStrBuffer, dwStrLen * 2, pDirStringU->NameString, dwStrLen * 2);
					printf("		NameString: %ls", pStrBuffer);
				}
				else {
					//id������
					DWORD id = pDirEntry2->Name;  
					//if (id <= 16) {   // >>>>>>�ڶ��㲻��ʹ����Դ����������
					//	printf("		Name(ID): %ls", pResourceType[id]);
					//}
					//else {
						printf("		Name(ID): %d", id);
					//}

				}
				
				printf("\n");

				//������
				if (pDirEntry2->DataIsDirectory) {
				//>>>>>>>>>>>>>>
					DWORD  dwOffsetToDirectory = pDirEntry2->OffsetToDirectory;
					DWORD  sectionFoa = GetSectionFoaByRva(VirtualAddress);
					DWORD  dwDirectoryAddrOfFile = dwOffsetToDirectory + sectionFoa + (DWORD)g_pFileBuffer;
					IMAGE_RESOURCE_DIRECTORY* pResourceDirectory3 = (IMAGE_RESOURCE_DIRECTORY*)dwDirectoryAddrOfFile;
					DWORD dwNumberOfNamedEntries = pResourceDirectory3->NumberOfNamedEntries;
					DWORD dwNumberOfIdEntries = pResourceDirectory3->NumberOfIdEntries;
					DWORD dwEntryCount = dwNumberOfNamedEntries + dwNumberOfIdEntries;
					IMAGE_RESOURCE_DIRECTORY_ENTRY* pDirEntry3 = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)(pResourceDirectory3 + 1);
					////
					for (DWORD i = 0; i < dwEntryCount; i++) {
						//entry
						if (pDirEntry3->NameIsString) {
							//����������
							DWORD dwNameOffset = pDirEntry3->NameOffset;
							DWORD sectionFoa = GetSectionFoaByRva(VirtualAddress);
							DWORD dwNameAddrOfFile = dwNameOffset + sectionFoa + (DWORD)g_pFileBuffer;  // error ��Ҫ�ӻ�ַfileBuffer
							IMAGE_RESOURCE_DIR_STRING_U* pDirStringU = (IMAGE_RESOURCE_DIR_STRING_U*)dwNameAddrOfFile;
							DWORD dwStrLen = pDirStringU->Length;
							WCHAR* pStrBuffer = new WCHAR[dwStrLen + 2];
							ZeroMemory(pStrBuffer, dwStrLen * 2 + 2);
							memcpy_s(pStrBuffer, dwStrLen * 2, pDirStringU->NameString, dwStrLen * 2);
							printf("			NameString3: %ls", pStrBuffer);
						}
						else {
							//id������
							DWORD id = pDirEntry3->Name;
							//printf("			Name3(Language): %d", id);
							//��ȡ��Դλ�ü���Դ����
							DWORD dwOffsetToData = pDirEntry3->OffsetToData; // �ڶ���������, ָ������Դ��λ��
							DWORD sectionFoa = GetSectionFoaByRva(VirtualAddress);
							DWORD dwDataEntryAddrOfFile = dwOffsetToData + sectionFoa + (DWORD)g_pFileBuffer;
							IMAGE_RESOURCE_DATA_ENTRY* pDataEntry = (IMAGE_RESOURCE_DATA_ENTRY*)dwDataEntryAddrOfFile;
							DWORD dwOffsetToDataRva = pDataEntry->OffsetToData;
							DWORD dwOffsetToDataFoa = RVA2FOA(dwOffsetToDataRva);
							DWORD dwSize = pDataEntry->Size;
							printf("			Rva: %X, Offset: %X, Size: %X\n", dwOffsetToDataRva, dwOffsetToDataFoa, dwSize);
						}
						pDirEntry3++;
						printf("\n");
					}


				//<<<<<<<<<<<<<<<<
				}
				else {
					//����һ��Ŀ¼
					DWORD dwOffsetToData = pDirEntry2->OffsetToData;
					DWORD dwSectionFoa = GetSectionFoaByRva(VirtualAddress);
					DWORD dwDataEntry = dwOffsetToData + dwSectionFoa + (DWORD)g_pFileBuffer;
					IMAGE_RESOURCE_DATA_ENTRY* pDataEntry = (IMAGE_RESOURCE_DATA_ENTRY*)dwDataEntry;
					printf("			ƫ��:%X  ��С:%X\n", pDataEntry->OffsetToData, pDataEntry->Size);
				}

				pDirEntry2++;

			}
			
			
			/////
		}
		else {
			printf("not a directory\n");
		}

		
		pResourceDirEntry++;
	}

	return 0;
	
}

typedef struct _TypeOffset {
	WORD Offset : 12;
	WORD Type : 4;
} TypeOffset;

bool ShowRelocationInfo()
{
	
	printf("---------��ַ�ض�λ---------\n");
	DWORD dwRelocationVirtualAddress = g_pDataDir[5].VirtualAddress;
	DWORD dwBaseRelocationFoa = RVA2FOA(dwRelocationVirtualAddress);
	DWORD dwBaseRelocationAddrOfFile = dwBaseRelocationFoa + (DWORD)g_pFileBuffer;
	IMAGE_BASE_RELOCATION* pBaseRelocation = (IMAGE_BASE_RELOCATION*)dwBaseRelocationAddrOfFile;
	DWORD index = 1;
	while (pBaseRelocation->SizeOfBlock) {// page
		printf("index: %d ", index);
		DWORD dwVirtualAddress = pBaseRelocation->VirtualAddress;
		DWORD dwSizeOfBlock = pBaseRelocation->SizeOfBlock;
		DWORD dwEntryCount = (dwSizeOfBlock - 8) / 2;
		//ȷ�����ĸ�����
		IMAGE_SECTION_HEADER* pSectionHeader = GetSectionHeaderByRva(dwVirtualAddress);
		printf("[%s] RVA: %08X,  iTems: %d\n", pSectionHeader->Name, dwVirtualAddress, dwEntryCount);
		TypeOffset* pTypeOffset = (TypeOffset*)(pBaseRelocation + 1);
		for (DWORD i = 0; i < dwEntryCount; i++) {
			DWORD dwType = pTypeOffset->Type;
			DWORD dwEntryRva = pTypeOffset->Offset + pBaseRelocation->VirtualAddress;
			DWORD dwEntryOffset = RVA2FOA(dwEntryRva); // ʵ��ΪFOA
			DWORD dwDataAddr = dwEntryOffset + (DWORD)g_pFileBuffer;
			DWORD  dwDataVA = *(DWORD*)dwDataAddr;
			printf("	����:%d Rva: %08X ƫ��: %08X  type: %d	FAR��ַ: %08X; ���ݽ���: --\n", i, dwEntryRva, dwEntryOffset, dwType, dwDataVA);
			pTypeOffset++;
		}
	
		pBaseRelocation = (IMAGE_BASE_RELOCATION*)((DWORD)pBaseRelocation + pBaseRelocation->SizeOfBlock);
		index++;
	}



	return true;
}
