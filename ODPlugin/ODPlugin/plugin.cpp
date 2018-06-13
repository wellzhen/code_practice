#include "stdafx.h"
#include "plugin.h"

// [ OD插件必选导出函数 ]
// 在此函数中,填写插件的名字, 插件的版本号
extc int ODBG2_Pluginquery( int ollydbgversion , 
							ulong *features ,
							wchar_t pluginname[ SHORTNAME ] ,
							wchar_t pluginversion[ SHORTNAME ] ) 
{

	// 判断OD的版本是否为201版本
	if( ollydbgversion < 201 ) {
		// 返回0, 插件将不会被加载
		OutputDebugString(L"小于201");
		//return 0;
	}

	// 填写插件名
	wcscpy_s( pluginname , SHORTNAME ,  MYPLUGIN_NAME );

	// 填写版本号
	wcscpy_s( pluginversion , SHORTNAME , MYPLUGIN_VERSION );

	// 返回插件所需的OD版本号.
	return PLUGIN_VERSION;
}


// [OD可选插件导出函数]
// 在此函数中, 创建一个菜单, 并返回,这样就能够显示在OD对应窗口的菜单中.
extc t_menu *ODBG2_Pluginmenu( wchar_t *type )
{
	// 1. 先构造一个菜单结构体,这个菜单结构体必须存在整个程序的运行期间.
	//    结构体必须以一个全0元素为结尾.
	static t_menu menu[ 4 ] = { 0 };
	
	// 2. 菜单名
	menu[ 2 ].name = L"MyOdPlugin_反汇编窗口菜单名";
	// 2.1 菜单ID
	menu[ 2 ].index = 1;

	// 3. 菜单的回调函数
	menu[ 2 ].menufunc = cb_menu_disasm;


	menu[ 0 ].name = L"MyOdPlugin_主菜单";
	menu[ 0 ].menufunc = cb_menu_disasm;
	menu[ 0 ].index = 0;

	// 判断是否是反汇编窗口弹出的菜单
	if( wcscmp( type , PWM_DISASM ) == 0 ) {
		return menu + 2;
	}
	// 判断是否是主菜单弹出的菜单
	else if( wcscmp( type , PWM_MAIN ) == 0 ) {
		return menu ;
	}
	return nullptr;
}

// cb => call back (回调函数)
// 菜单被点击的回调函数
int cb_menu_disasm( struct t_table * table , wchar_t * name , ulong Index , int mode ) {

	// 弹出菜单的验证模式, 这个时候,可以指定菜单的样式
	if( mode == MENU_VERIFY ) {
		return MENU_NORMAL | MENU_CHECKED;
	}
	// 菜单被点击.
	if( mode == MENU_EXECUTE ) {

		// 判断是哪个菜单被点击
		switch( Index ) {
			case 0:
				MessageBoxA( 0 , "我是主菜单" , 0 , 0 );
				break;

			case 1:
				MessageBoxA( 0 , "我是反汇编窗口的菜单" , 0 , 0 );
				break;
		}
	}

	return 0;
}


// [OD插件可选导出函数]
// 当被调试进程产生异常事件时,OD就会调用这个函数.
pentry( int )         ODBG2_Pluginexception( t_run *prun , 
											 const t_disasm *da ,
											 t_thread *pthr , 
											 t_reg *preg , 
											 wchar_t *message )
{
	//Error( L"程序在%08X处产生了%08X异常" , 
	//	   prun->de.u.Exception.ExceptionRecord.ExceptionAddress ,
	//	   prun->de.u.Exception.ExceptionRecord.ExceptionCode );
	
	return 0;
}