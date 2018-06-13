#include "stdafx.h"
#include <windows.h>
#include <winternl.h>
#pragma comment(lib, "ntdll.lib")

//����������Ϣ�ṹ��
typedef struct _OBJECT_TYPE_INFORMATION {
	UNICODE_STRING TypeName;
	ULONG TotalNumberOfHanders;
	ULONG TotalNumberOfObjects;
} OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;

//����������Ϣ����
typedef struct _OBJECT_ALL_INFORMATION {
	ULONG NumberOfObjectsTypes;
	OBJECT_TYPE_INFORMATION ObjectTypeInfo[1];
}OBJECT_ALL_INFORMATION, *POBJECT_ALL_INFORMATION;

bool NQ_NtQueryObject()
{
	//��ȡ����ѯ��Ϣ��С
	ULONG uSize = 0;
	NtQueryObject(NULL,
		(OBJECT_INFORMATION_CLASS)0x03,
		&uSize,
		sizeof(uSize),
		&uSize
		);
	//��ȡ������Ϣ
	//POBJECT_ALL_INFORMATION pObjectAllInfo =(POBJECT_ALL_INFORMATION)new BYTE[uSize];
	POBJECT_ALL_INFORMATION pObjectAllInfo =
		(POBJECT_ALL_INFORMATION)new BYTE[uSize];
	NtQueryObject(
		NULL, 
		(OBJECT_INFORMATION_CLASS)0x03,
		pObjectAllInfo,
		uSize,
		&uSize
	);
	//ѭ�����������������Ϣ
	POBJECT_TYPE_INFORMATION pObjType = pObjectAllInfo->ObjectTypeInfo;

	for (int i = 0; i < pObjectAllInfo->NumberOfObjectsTypes; )


}

