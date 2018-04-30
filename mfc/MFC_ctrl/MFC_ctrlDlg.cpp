
// MFC_ctrlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_ctrl.h"
#include "MFC_ctrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_ctrlDlg 对话框



CMFC_ctrlDlg::CMFC_ctrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_CTRL_DIALOG, pParent)
	, m_check_piano(FALSE)
	, m_edit03(_T(""))
	, m_edit02(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_ctrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Check(pDX, IDC_CHECK1, m_nCheck_male);
	DDX_Check(pDX, IDC_CHECK1, m_check_piano);
	DDX_Control(pDX, IDC_CHECK5, m_basketball);
	DDX_Control(pDX, IDC_EDIT1, m_edit01);
	DDX_Text(pDX, IDC_EDIT3, m_edit03);
	DDX_Text(pDX, IDC_EDIT2, m_edit02);
	DDX_Control(pDX, IDC_PROGRESS1, m_proress);
	DDX_Control(pDX, IDC_SLIDER1, m_sliderbar);
}

BEGIN_MESSAGE_MAP(CMFC_ctrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_RBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC_ctrlDlg::OnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CMFC_ctrlDlg::OnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK5, &CMFC_ctrlDlg::OnClickedCheck5_baskball)
	ON_EN_CHANGE(IDC_EDIT1, &CMFC_ctrlDlg::OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CMFC_ctrlDlg::OnChangeEdit2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CMFC_ctrlDlg::OnCustomdrawProgress1)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_PROGRESS1, &CMFC_ctrlDlg::OnOutofmemoryProgress1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_PROGRESS1, &CMFC_ctrlDlg::OnReleasedcaptureProgress1)
	ON_NOTIFY(NM_THEMECHANGED, IDC_PROGRESS1, &CMFC_ctrlDlg::OnThemechangedProgress1)
END_MESSAGE_MAP()


// CMFC_ctrlDlg 消息处理程序

BOOL CMFC_ctrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//yz
	CBitmap bmp;
	bmp.LoadBitmapW(IDB_BITMAP2);
	m_brBk.CreatePatternBrush(&bmp);
	bmp.DeleteObject();


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFC_ctrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC_ctrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFC_ctrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CMFC_ctrlDlg::OnRButtonDblClk(  UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnRButtonDblClk(nFlags, point);
	MessageBox(L"onRButtonDblClk");
}


void CMFC_ctrlDlg::OnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//m_proress.SetRange(0, 100);
	m_proress.SetPos(80);
	//MessageBox(L"OnClickedButton1");
	m_sliderbar.SetPos(80);

}

//piano
void CMFC_ctrlDlg::OnClickedCheck1()
{
	UpdateData(true);
	CString piano;
	piano.Format(L"%d", m_check_piano);
	MessageBox(piano);
}


void CMFC_ctrlDlg::OnClickedCheck5_baskball()
{
	int status = m_basketball.GetCheck();
	WCHAR buf[100];
	_itow_s(status, buf, 100, 10);
	MessageBox(buf);
}


void CMFC_ctrlDlg::OnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//m_edit01.LimitText(4);
	//SendMessage(WM_COMMAND, NULL, NULL);
	//m_edit01.SetPasswordChar(L'-');

}


void CMFC_ctrlDlg::OnChangeEdit2()
{
	UpdateData(true);
	m_edit03.Append(m_edit02);
	m_edit02.Empty();
	UpdateData(false);

}


void CMFC_ctrlDlg::OnCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_proress.SetRange(0, 100);
	m_proress.SetPos(50);
	MessageBox(L"滚动条1");


	*pResult = 0;
	
}


void CMFC_ctrlDlg::OnOutofmemoryProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_proress.SetRange(0, 100);
	m_proress.SetPos(50);
	MessageBox(L"滚动条2");
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	
}


void CMFC_ctrlDlg::OnReleasedcaptureProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CMFC_ctrlDlg::OnThemechangedProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 该功能要求使用 Windows XP 或更高版本。
	// 符号 _WIN32_WINNT 必须 >= 0x0501。
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
