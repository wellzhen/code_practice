#pragma once
#include <windows.h>

// ����ODͷ�ļ�
#include "OllyDBG_Plugin/od_plugin.h"
#pragma comment(lib,"OllyDBG_Plugin/ollydbg.lib")

extern HMODULE g_hModule; // ��dllģ����ػ�ַ.


// ���������(���ⶨ)
#define MYPLUGIN_NAME L"PLUGIN_15PB"

// ����İ汾(���ⶨ)
#define MYPLUGIN_VERSION L"0.01"

// �˵��Ļص�����
int  cb_menu_disasm( struct t_table * table , wchar_t * name , ulong Index , int mode );

/**
 * OD�����д����
 * 1. ׼��OD�����ͷ�ļ��Ϳ��ļ�.
 * 2. �ڹ��������ͷ�ļ�,��ӿ��ļ�
 * 3. ����OD�ı�Ҫ��������:ODBG2_Pluginquery
 *
 * OD�����ӵ����˵�����:
 * 1. ����OD����Ӳ˵��ĺ���:ODBG2_Pluginmenu
 * 2. �ڵ���������,��д����.����һ����Ҫ��ӵĲ˵��ṹ��.
 *
 * OD���ע��������ϵ��¼�����:
 * 1. ����ODBG2_Pluginexception����
 * 2. �ж��쳣�����ĵط��Ƿ��Ƕϵ�.
 */


