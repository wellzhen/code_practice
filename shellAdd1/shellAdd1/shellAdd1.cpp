// shellAdd1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "PEinfo.h"
#include "../stub/stubconf.h"

//修复stub的重定位表的virtualAddress;
void FixStubRelocRVA(CPEinfo* pStubInfo, CPEinfo* pExeInfo);
BOOL FixStubTextReloc(CPEinfo* pStubInfo, CPEinfo* pExeInfo);

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
	FixStubTextReloc(pStubInfo, pExeInfo);

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

	//加密密码
	printf("请输入密码 > ");
	scanf_s("%s", stubConf->szKey, 16);

	//保存exe的数据目录表到stubConf
	memcpy_s(stubConf->dataDir,sizeof(IMAGE_DATA_DIRECTORY)*16, pExeInfo->m_pOptionalHeader->DataDirectory, sizeof(IMAGE_DATA_DIRECTORY) * 16);
	
	//将stub.dll的代码段拷入exe : note: 要加基址
	memcpy_s((char*)(pExeLastSection->PointerToRawData + pExeInfo->m_dwBufferBase), pStubTextSectionHeader->SizeOfRawData,
			(char*)(pStubTextSectionHeader->VirtualAddress + pStubInfo->m_dwBufferBase), pStubTextSectionHeader->SizeOfRawData);

	
	// 将exe的数据目录清空
	//	1. 保存TLS
	DWORD dwTlsRVA = pExeInfo->m_pOptionalHeader->DataDirectory[9].VirtualAddress;
	DWORD dwTlsSize = pExeInfo->m_pOptionalHeader->DataDirectory[9].Size;
	if (dwTlsRVA != 0) {
		//	2. 清空
		ZeroMemory(pExeInfo->m_pOptionalHeader->DataDirectory, sizeof(IMAGE_DATA_DIRECTORY) * 16);
		//	3. 恢复TLS数据目录
		pExeInfo->m_pOptionalHeader->DataDirectory[9].VirtualAddress = dwTlsRVA;
		pExeInfo->m_pOptionalHeader->DataDirectory[9].Size = dwTlsSize;
		//	4. 转换成FOA
		DWORD dwTlsFOA = pExeInfo->RVA2FOA(dwTlsRVA);
		if (dwTlsFOA == 0) {
			MessageBoxA(NULL, "无法转换成FOA", "note", MB_OK);
			return 0;
		}
		//  4. 清除TLS的回调函数表: 
		IMAGE_TLS_DIRECTORY* pTlsDir = (IMAGE_TLS_DIRECTORY*)(dwTlsFOA+ pExeInfo->m_dwBufferBase);
		DWORD dwAddrOfCallBackRVA = (pTlsDir->AddressOfCallBacks - pExeInfo->m_pOptionalHeader->ImageBase);
		DWORD dwAddrOfCallBackFOA = pExeInfo->RVA2FOA(dwAddrOfCallBackRVA);
		DWORD* pCallBack = (DWORD*)(dwAddrOfCallBackFOA+pExeInfo->m_dwBufferBase);
		DWORD index = 0;
		while (*pCallBack != 0) {
			//保存
			stubConf->dwTlsCallBackValue[index] = *pCallBack;
			//清除
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



	//加密
	pExeInfo->Encrypt(stubConf);

	//修复并拷贝stub的重定位表, 并新建了新的区段
	FixStubRelocRVA(pStubInfo, pExeInfo);
	pExeLastSection++;
	//新的文件大小: 用于保存文件
	//写入文件
	DWORD dwNewFileSize = pExeLastSection->PointerToRawData + pStubTextSectionHeader->SizeOfRawData;
	memcpy_s(pExeInfo->m_szNewFilePath + strlen(pExeInfo->m_szNewFilePath) - 4, 255, "_.exe", 5);
	HANDLE hNewFile = CreateFileA(pExeInfo->m_szNewFilePath, GENERIC_ALL, NULL, NULL, CREATE_ALWAYS, NULL, NULL);
	WriteFile(hNewFile, (char*)pExeInfo->m_dwBufferBase, dwNewFileSize, NULL, NULL);
	CloseHandle(hNewFile);
    return 0;
}

//支持随机基址: 修改.reloc区段的VirtualAddress信息
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
	//遍历所有重定位块, 属于代码段的RVA 则修改为对应exe的RVA
	DWORD dwTextRVAmin = pStubInfo->GetSectionByName(".text")->VirtualAddress;
	DWORD dwTextRVAmax = dwTextRVAmin + pStubInfo->GetSectionByName(".text")->Misc.VirtualSize;
	char* dwCopyAddrStart = (char*)pBaseReloc;
	char* dwCopyAddrEnd = 0;
	while(pBaseReloc->SizeOfBlock != 0) {
		//判断是否属于text段的
		DWORD dwRelocRVA = pBaseReloc->VirtualAddress;
		if (dwRelocRVA > dwTextRVAmin && dwRelocRVA < dwTextRVAmax) {
			DWORD dwOldProtect;
			VirtualProtect((char*)pBaseReloc, 8, PAGE_EXECUTE_READWRITE, &dwOldProtect);
			pBaseReloc->VirtualAddress -= dwTextRVAmin;
			//DWORD dwExeEndRVA = pExeLastSection->VirtualAddress + pExeLastSection->Misc.VirtualSize;
			pBaseReloc->VirtualAddress += pExeLastSection->VirtualAddress;
			VirtualProtect((char*)pBaseReloc, 8, dwOldProtect, &dwOldProtect);
		}
		else {//不在代码段了
			dwCopyAddrEnd = (char*)pBaseReloc; // 多一个字节
			break;
		}
		pBaseReloc = (IMAGE_BASE_RELOCATION*)((DWORD)pBaseReloc + pBaseReloc->SizeOfBlock);
	}

	// exe创建一个新的区段stubRel 
	// 先修改m_FileSize 属性 
	pExeInfo->m_FileSize += pExeLastSection->SizeOfRawData; 
	DWORD dwRelocFSize = pStubInfo->GetSectionByName(".reloc")->SizeOfRawData;
	pExeInfo->AddNewSection("stubRel", dwRelocFSize);
	//把.reloc的信息拷贝进去
	pExeLastSection++;
	char* destAddr = (char*)(pExeLastSection->PointerToRawData + pExeInfo->m_dwBufferBase);
	char* srcAddr = (char*)(pStubInfo->GetSectionByName(".reloc")->VirtualAddress + pStubInfo->m_dwBufferBase);
	DWORD copyLength = (DWORD)dwCopyAddrEnd - (DWORD)dwCopyAddrStart;
	memcpy_s(destAddr, copyLength, srcAddr, copyLength);
	//修改重定位表目录的RVA和Size
	pExeInfo->m_pOptionalHeader->DataDirectory[5].VirtualAddress = pExeLastSection->VirtualAddress;
	pExeInfo->m_pOptionalHeader->DataDirectory[5].Size = copyLength;
}

BOOL FixStubTextReloc(CPEinfo* pStubInfo, CPEinfo* pExeInfo)
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



