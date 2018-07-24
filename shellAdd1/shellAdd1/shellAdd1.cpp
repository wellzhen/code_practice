// shellAdd1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "PEinfo.h"
#include "../stub/stubconf.h"

BOOL FixStubReloc(CPEinfo* pStubInfo, CPEinfo* pExeInfo);

int _tmain(int argc, _TCHAR argv[])
{
	char szFile[255]{ 0 };
	printf("PE路径:  ");
	scanf_s("%s", szFile, 255);
	//加载exe文件
	CPEinfo*  pExeInfo = new CPEinfo(szFile, TRUE);
	//加载stub.dll
	CPEinfo*  pStubInfo = new CPEinfo("W:\\code_practice\\shellAdd1\\bin\\stub.dll", FALSE);

	//获取stub代码段的信息
	IMAGE_SECTION_HEADER* pStubTextSectionHeader = pStubInfo->GetSectionByName(".text");
	if (pStubTextSectionHeader == NULL) {
		printf("无法获取.text区段表信息\n");
		return 0;
	}
	//添加一个新的区段到exe
	char chNewSectionName[8] = "moon";
	BOOL AddRes = pExeInfo->AddNewSection(chNewSectionName, pStubTextSectionHeader->SizeOfRawData);
	if (AddRes == FALSE) {
		printf("buffer空间不足\n");
		system("pause");
	}

	//修复Stub的.text段的重定位(重定位基址和区段RVA)
	FixStubReloc(pStubInfo, pExeInfo);

	//重定位导出函数start的RVA: star函数要作为exe的新OEP
	DWORD dwStubStartRVA = (DWORD)GetProcAddress((HMODULE)pStubInfo->m_dwBufferBase, "start") - pStubInfo->m_dwBufferBase; //GetProcAddress()求出的是VA,不是RVA
	dwStubStartRVA -= pStubTextSectionHeader->VirtualAddress; //修改到区段的RVA
	IMAGE_SECTION_HEADER* pExeLastSection = pExeInfo->m_pSectionHeader0 + pExeInfo->m_pFileHeader->NumberOfSections - 1;
	dwStubStartRVA += pExeLastSection->VirtualAddress;

	//OEP处理: 保存exe的OEP, 修改exe的OEP
	//   保存exe参数到 StubConf: oep和DataDir
	StubConf* stubConf = (StubConf*)GetProcAddress((HMODULE)pStubInfo->m_dwBufferBase, "g_conf");
	stubConf->dwOEP = pExeInfo->m_pOptionalHeader->AddressOfEntryPoint;  // 保存exe的原始OEP
	//	 修改exe的OEP, 指向start函数
	pExeInfo->m_pOptionalHeader->AddressOfEntryPoint = dwStubStartRVA;


	//保存exe的数据目录表到stubConf
	memcpy_s(stubConf->dataDir,sizeof(IMAGE_DATA_DIRECTORY)*16, pExeInfo->m_pOptionalHeader->DataDirectory, sizeof(IMAGE_DATA_DIRECTORY) * 16);
	
	//将stub.dll的代码段拷入exe : note: 要加基址
	memcpy_s((char*)(pExeLastSection->PointerToRawData + pExeInfo->m_dwBufferBase), pStubTextSectionHeader->SizeOfRawData,
			(char*)(pStubTextSectionHeader->VirtualAddress + pStubInfo->m_dwBufferBase), pStubTextSectionHeader->SizeOfRawData);

	//新的文件大小: 用于保存文件
	DWORD dwNewFileSize = pExeLastSection->PointerToRawData + pStubTextSectionHeader->SizeOfRawData;
	// 将exe的数据目录清空
	ZeroMemory(pExeInfo->m_pOptionalHeader->DataDirectory, sizeof(IMAGE_DATA_DIRECTORY) * 16);

	//写入文件
	memcpy_s(pExeInfo->m_szNewFilePath + strlen(pExeInfo->m_szNewFilePath) - 4, 255, "_.exe", 5);
	HANDLE hNewFile = CreateFileA(pExeInfo->m_szNewFilePath, GENERIC_ALL, NULL, NULL, CREATE_ALWAYS, NULL, NULL);
	WriteFile(hNewFile, (char*)pExeInfo->m_dwBufferBase, dwNewFileSize, NULL, NULL);
	CloseHandle(hNewFile);
    return 0;
}

BOOL FixStubReloc(CPEinfo* pStubInfo, CPEinfo* pExeInfo)
{
	//Stub重定位表
	IMAGE_DATA_DIRECTORY RelocTableDir = pStubInfo->m_pOptionalHeader->DataDirectory[5];
	DWORD dwRelocTableRVA = RelocTableDir.VirtualAddress;
	DWORD dwRelocTableVA = dwRelocTableRVA + pStubInfo->m_dwBufferBase;
	IMAGE_BASE_RELOCATION*  baseReloc = (IMAGE_BASE_RELOCATION*)dwRelocTableVA;
	typedef struct __TypeOffset {
		WORD offset : 12; //偏移量
		WORD type : 4;  //重定位属性
	} TypeOffset;
	while (baseReloc->SizeOfBlock != 0) {
		DWORD count = (baseReloc->SizeOfBlock - 8) / 2; //需要重定位的个数
		for (DWORD i = 0; i < count; i++) {
			TypeOffset* pTypeOffset = (TypeOffset*)((DWORD)baseReloc + 8 + i * 2); //地址通过i增加
			IMAGE_SECTION_HEADER* pStubTextSectionHeader = pStubInfo->GetSectionByName(".text"); //获取stub代码段的信息
			IMAGE_SECTION_HEADER* pExeTextSectionHeader = pExeInfo->GetSectionByName("moon"); //获取exe代码段的信息
			if (pTypeOffset->type == 3 
				&& baseReloc->VirtualAddress >= pStubTextSectionHeader->VirtualAddress
				&& baseReloc->VirtualAddress <= pStubTextSectionHeader->VirtualAddress + pStubTextSectionHeader->Misc.VirtualSize ) 
			{
				// to do : 修改内存读写属性

				DWORD dwNeedRelocRVA = baseReloc->VirtualAddress + pTypeOffset->offset;
				DWORD dwNeedRelocVA = dwNeedRelocRVA + pStubInfo->m_dwBufferBase;
				//修改该位置的值
				//	替换加载基址
				*(DWORD*)dwNeedRelocVA -= pStubInfo->m_dwBufferBase;
				*(DWORD*)dwNeedRelocVA += pExeInfo->m_pOptionalHeader->ImageBase;
				//	替换段首RVA
				*(DWORD*)dwNeedRelocVA -= pStubTextSectionHeader->VirtualAddress;
				*(DWORD*)dwNeedRelocVA +=  pExeTextSectionHeader->VirtualAddress;
			}
		}
		//baseReloc++; //错误, 不能++ 应该加SizeOfBlock
		baseReloc = (IMAGE_BASE_RELOCATION*)((DWORD)baseReloc + baseReloc->SizeOfBlock);
	}

	return TRUE;
}