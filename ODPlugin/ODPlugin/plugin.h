#pragma once
#include <windows.h>

// 导入OD头文件
#include "OllyDBG_Plugin/od_plugin.h"
#pragma comment(lib,"OllyDBG_Plugin/ollydbg.lib")

extern HMODULE g_hModule; // 本dll模块加载基址.


// 插件的名字(随意定)
#define MYPLUGIN_NAME L"PLUGIN_15PB"

// 插件的版本(随意定)
#define MYPLUGIN_VERSION L"0.01"

// 菜单的回调函数
int  cb_menu_disasm( struct t_table * table , wchar_t * name , ulong Index , int mode );

/**
 * OD插件编写步骤
 * 1. 准备OD插件的头文件和库文件.
 * 2. 在工程中添加头文件,添加库文件
 * 3. 导出OD的必要导出函数:ODBG2_Pluginquery
 *
 * OD插件添加弹出菜单步骤:
 * 1. 导出OD的添加菜单的函数:ODBG2_Pluginmenu
 * 2. 在导出函数中,编写代码.返回一个想要添加的菜单结构体.
 *
 * OD插件注册调试器断点事件步骤:
 * 1. 导出ODBG2_Pluginexception函数
 * 2. 判断异常发生的地方是否是断点.
 */


