// debug.cpp : �������̨Ӧ�ó������ڵ㡣
//try finally

#include "stdafx.h"


int main()
{
	char* pFileData = nullptr;
	FILE* pFile = nullptr;
	__try {
		printf("try��\n");
		fopen_s(&pFile, "debug.cpp", "rb");
		if (pFile == NULL) {
			return 0;
		//	__leave;
		}
		pFileData = new char[200];
		if (pFileData == NULL) {
			//return 0;
			__leave;
		}
		if (fread(pFileData, 1, 200, pFile) != 200) {
			//return 0;
			__leave;
		}

	}
	__finally {
		//��finally����ͳһ�ͷ���Դ
		printf("finally\n");
		if (pFileData != nullptr) {
			delete[] pFileData;
			pFileData = nullptr;
		}
		if (pFile != nullptr)
		{
			fclose(pFile);
			pFile = nullptr;
		}
	}


	return 0;
}