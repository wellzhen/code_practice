// process.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	STARTUPINFO si = {};
	PROCESS_INFORMATION pi = {};
	CreateProcess(
		TEXT("C:\\Program Files (x86)\\FastStoneCapturecn\\FSCapture.exe"),//exe�ļ�·��
		NULL, //�����в���
		NULL, //���̰�ȫ����
		NULL, //�̵߳İ�ȫ����
		FALSE,//�Ƿ�Ҫ�̳и����̵ľ�������ڱ�������˵�������Ƿ�̳�VS2013�ľ��
		NULL, //������ʽ��־��1���Դ���һ����������Ľ���  2 ���Դ���һ�������ԵĽ���
		NULL, //�����ַ�����
		NULL, //��������Ŀ¼��ΪNULL�Ļ�������exe���ڵ�Ŀ¼
		&si,
		&pi);
    return 0;
}

