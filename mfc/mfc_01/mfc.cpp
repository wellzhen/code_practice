#include <afxwin.h>
CWinApp theApp;

class CMyApp : public CWinApp
{
	BOOL InitInstance()
	{
		CFrameWnd * Frame = new CFrameWnd();
		m_pMainWnd = Frame;
		Frame->Create(NULL, L"��򵥵Ĵ���");
		Frame->ShowWindow(SW_SHOW);
		
		return true;
	}
};