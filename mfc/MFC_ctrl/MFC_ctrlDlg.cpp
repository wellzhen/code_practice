
// MFC_ctrlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_ctrl.h"
#include "MFC_ctrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFC_ctrlDlg �Ի���



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


// CMFC_ctrlDlg ��Ϣ�������

BOOL CMFC_ctrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//yz
	CBitmap bmp;
	bmp.LoadBitmapW(IDB_BITMAP2);
	m_brBk.CreatePatternBrush(&bmp);
	bmp.DeleteObject();


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFC_ctrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFC_ctrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CMFC_ctrlDlg::OnRButtonDblClk(  UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnRButtonDblClk(nFlags, point);
	MessageBox(L"onRButtonDblClk");
}


void CMFC_ctrlDlg::OnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_proress.SetRange(0, 100);
	m_proress.SetPos(50);
	MessageBox(L"������1");


	*pResult = 0;
	
}


void CMFC_ctrlDlg::OnOutofmemoryProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_proress.SetRange(0, 100);
	m_proress.SetPos(50);
	MessageBox(L"������2");
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	
}


void CMFC_ctrlDlg::OnReleasedcaptureProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CMFC_ctrlDlg::OnThemechangedProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// �ù���Ҫ��ʹ�� Windows XP ����߰汾��
	// ���� _WIN32_WINNT ���� >= 0x0501��
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
