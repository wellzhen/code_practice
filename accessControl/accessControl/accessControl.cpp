#include "stdafx.h"
#include <Windows.h>
#include <ShlObj.h>

int _tmain(int argc, _TCHAR* argv[])
{
	//获取本进程令牌
	HANDLE hToken = NULL;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
		printf("错误码:%x\n", GetLastError());
		return 0;
	}
	//用于接收令牌类型
	TOKEN_ELEVATION_TYPE tokenType = TokenElevationTypeDefault;
	DWORD dwRetSize = 0; // 用于接收函数输出信息的字节数
	//获取令牌信息
	GetTokenInformation(hToken, TokenElevationType, &tokenType, sizeof(tokenType), &dwRetSize);
	//判断调用是否成功
	if (ERROR_SUCCESS != GetLastError()) {
		printf("错误码: %x\n", GetLastError());
		return 0;
	}

	//根据令牌的类型来输出相应的信息
	switch (tokenType) {
	case TokenElevationTypeDefault:
		printf("默认用户: TokenElevationTypeDefault\n");
		return  IsUserAnAdmin();
		break;
	case TokenElevationTypeFull:
		printf("管理员账户, 所有权限\n");
		break;
	case TokenElevationTypeLimited:
		//判断受限制的用户是管理员
		//如果是管理员, 则这个令牌中会保存有管理员的SID

		//1. 获取系统内键管理员用户的SID
		byte adminSID[SECURITY_MAX_SID_SIZE];
		DWORD dwSize = SECURITY_MAX_SID_SIZE;
		CreateWellKnownSid(WinBuiltinAdministratorsSid,
			NULL,
			adminSID,
			&dwSize
		);
		//获取本令牌的连接令牌, 受限制的令牌都会有一个连接的令牌,
		//受限制的令牌都是都是由主令牌所创建的
		TOKEN_LINKED_TOKEN linkToken;
		GetTokenInformation(hToken,
			TokenLinkedToken,
			&linkToken,
			sizeof(linkToken),
			&dwSize
		);
		//在连接的令牌中查找是否具有管理员的SID
		BOOL  bIsMember = false;
		CheckTokenMembership(hToken, &adminSID, &bIsMember);
		if (bIsMember) {
			printf("权限被阉割的受限管理员账户\n");
		}
		break;
	}
	system("pause");
	return 0;
}