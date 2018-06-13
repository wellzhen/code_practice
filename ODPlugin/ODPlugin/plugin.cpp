#include "stdafx.h"
#include "plugin.h"

// [ OD�����ѡ�������� ]
// �ڴ˺�����,��д���������, ����İ汾��
extc int ODBG2_Pluginquery( int ollydbgversion , 
							ulong *features ,
							wchar_t pluginname[ SHORTNAME ] ,
							wchar_t pluginversion[ SHORTNAME ] ) 
{

	// �ж�OD�İ汾�Ƿ�Ϊ201�汾
	if( ollydbgversion < 201 ) {
		// ����0, ��������ᱻ����
		OutputDebugString(L"С��201");
		//return 0;
	}

	// ��д�����
	wcscpy_s( pluginname , SHORTNAME ,  MYPLUGIN_NAME );

	// ��д�汾��
	wcscpy_s( pluginversion , SHORTNAME , MYPLUGIN_VERSION );

	// ���ز�������OD�汾��.
	return PLUGIN_VERSION;
}


// [OD��ѡ�����������]
// �ڴ˺�����, ����һ���˵�, ������,�������ܹ���ʾ��OD��Ӧ���ڵĲ˵���.
extc t_menu *ODBG2_Pluginmenu( wchar_t *type )
{
	// 1. �ȹ���һ���˵��ṹ��,����˵��ṹ����������������������ڼ�.
	//    �ṹ�������һ��ȫ0Ԫ��Ϊ��β.
	static t_menu menu[ 4 ] = { 0 };
	
	// 2. �˵���
	menu[ 2 ].name = L"MyOdPlugin_����ര�ڲ˵���";
	// 2.1 �˵�ID
	menu[ 2 ].index = 1;

	// 3. �˵��Ļص�����
	menu[ 2 ].menufunc = cb_menu_disasm;


	menu[ 0 ].name = L"MyOdPlugin_���˵�";
	menu[ 0 ].menufunc = cb_menu_disasm;
	menu[ 0 ].index = 0;

	// �ж��Ƿ��Ƿ���ര�ڵ����Ĳ˵�
	if( wcscmp( type , PWM_DISASM ) == 0 ) {
		return menu + 2;
	}
	// �ж��Ƿ������˵������Ĳ˵�
	else if( wcscmp( type , PWM_MAIN ) == 0 ) {
		return menu ;
	}
	return nullptr;
}

// cb => call back (�ص�����)
// �˵�������Ļص�����
int cb_menu_disasm( struct t_table * table , wchar_t * name , ulong Index , int mode ) {

	// �����˵�����֤ģʽ, ���ʱ��,����ָ���˵�����ʽ
	if( mode == MENU_VERIFY ) {
		return MENU_NORMAL | MENU_CHECKED;
	}
	// �˵������.
	if( mode == MENU_EXECUTE ) {

		// �ж����ĸ��˵������
		switch( Index ) {
			case 0:
				MessageBoxA( 0 , "�������˵�" , 0 , 0 );
				break;

			case 1:
				MessageBoxA( 0 , "���Ƿ���ര�ڵĲ˵�" , 0 , 0 );
				break;
		}
	}

	return 0;
}


// [OD�����ѡ��������]
// �������Խ��̲����쳣�¼�ʱ,OD�ͻ�����������.
pentry( int )         ODBG2_Pluginexception( t_run *prun , 
											 const t_disasm *da ,
											 t_thread *pthr , 
											 t_reg *preg , 
											 wchar_t *message )
{
	//Error( L"������%08X��������%08X�쳣" , 
	//	   prun->de.u.Exception.ExceptionRecord.ExceptionAddress ,
	//	   prun->de.u.Exception.ExceptionRecord.ExceptionCode );
	
	return 0;
}