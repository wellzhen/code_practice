#include "stdafx.h"
#include <windows.h>
#include <winternl.h>
#pragma comment(lib, "ntdll.lib")

//对象类型信息结构体
typedef struct _OBJECT_TYPE_INFORMATION {
	UNICODE_STRING TypeName;
	ULONG TotalNumberOfHanders;
	ULONG TotalNumberOfObjects;
} OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;

//对象类型信息数组
typedef struct _OBJECT_ALL_INFORMATION {
	ULONG NumberOfObjectsTypes;
	OBJECT_TYPE_INFORMATION ObjectTypeInfo[1];
}OBJECT_ALL_INFORMATION, *POBJECT_ALL_INFORMATION;

bool NQ_NtQueryObject()
{
	//获取欲查询信息大小
	ULONG uSize = 0;
	NtQueryObject(NULL,
		(OBJECT_INFORMATION_CLASS)0x03,
		&uSize,
		sizeof(uSize),
		&uSize
		);
	//获取对象信息
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
	//循环遍历并处理对象信息
	POBJECT_TYPE_INFORMATION pObjType = pObjectAllInfo->ObjectTypeInfo;

	for (int i = 0; i < pObjectAllInfo->NumberOfObjectsTypes; )


}

