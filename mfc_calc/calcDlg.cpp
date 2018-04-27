
// calcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfc_calc.h"
#include "calcDlg.h"
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


// calcDlg �Ի���



calcDlg::calcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_CALC_DIALOG, pParent)
	, m_string(_T(""))
	, m_strResult(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void calcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_string);
	DDX_Text(pDX, IDC_EDIT2, m_strResult);
}

BEGIN_MESSAGE_MAP(calcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON6, &calcDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON22, &calcDlg::OnClickedButton22_2)
	ON_BN_CLICKED(IDC_BUTTON26, &calcDlg::OnClickedButton26_0)
	ON_BN_CLICKED(IDC_BUTTON21, &calcDlg::OnClickedButton21_1)
	ON_BN_CLICKED(IDC_BUTTON22, &calcDlg::OnClickedButton22_2)
	ON_BN_CLICKED(IDC_BUTTON23, &calcDlg::OnClickedButton23_3)
	ON_BN_CLICKED(IDC_BUTTON16, &calcDlg::OnClickedButton16_4)
	ON_BN_CLICKED(IDC_BUTTON17, &calcDlg::OnClickedButton17_5)
	ON_BN_CLICKED(IDC_BUTTON18, &calcDlg::OnClickedButton18_6)
	ON_BN_CLICKED(IDC_BUTTON11, &calcDlg::OnClickedButton11_7)
	ON_BN_CLICKED(IDC_BUTTON12, &calcDlg::OnClickedButton12_8)
	ON_BN_CLICKED(IDC_BUTTON13, &calcDlg::OnClickedButton13_9)
	ON_BN_CLICKED(IDC_BUTTON27, &calcDlg::OnClickedButton27_dot)
	ON_BN_CLICKED(IDC_BUTTON28, &calcDlg::OnClickedButton28_add)
	ON_BN_CLICKED(IDC_BUTTON24, &calcDlg::OnClickedButton24_sub)
	ON_BN_CLICKED(IDC_BUTTON19, &calcDlg::OnClickedButton19_multi)
	ON_BN_CLICKED(IDC_BUTTON14, &calcDlg::OnClickedButton14_div)
	ON_BN_CLICKED(IDC_BUTTON15, &calcDlg::OnClickedButton15_model)
	ON_BN_CLICKED(IDC_BUTTON25, &calcDlg::OnClickedButton25_result)
	ON_BN_CLICKED(IDC_BUTTON1, &calcDlg::OnClickedButton1_clear)
END_MESSAGE_MAP()


// calcDlg ��Ϣ�������

BOOL calcDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void calcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void calcDlg::OnPaint()
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
HCURSOR calcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void calcDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void calcDlg::OnClickedButton26_0()
{
	m_string.Append(L"0");
	UpdateData(false);
}


void calcDlg::OnClickedButton21_1()
{
	m_string.Append(L"1");
	UpdateData(false);
}


void calcDlg::OnClickedButton22_2()
{
	m_string.Append(L"2");
	UpdateData(false);
}


void calcDlg::OnClickedButton23_3()
{
	m_string.Append(L"3");
	UpdateData(false);
}


void calcDlg::OnClickedButton16_4()
{
	m_string.Append(L"4");
	UpdateData(false);
}


void calcDlg::OnClickedButton17_5()
{
	m_string.Append(L"5");
	UpdateData(false);
}


void calcDlg::OnClickedButton18_6()
{
	m_string.Append(L"6");
	UpdateData(false);
}


void calcDlg::OnClickedButton11_7()
{
	m_string.Append(L"7");
	UpdateData(false);
}


void calcDlg::OnClickedButton12_8()
{
	m_string.Append(L"8");
	UpdateData(false);
}


void calcDlg::OnClickedButton13_9()
{
	m_string.Append(L"9");
	UpdateData(false);
}


void calcDlg::OnClickedButton27_dot()
{
	m_string.Append(L".");
	UpdateData(false);
}


void calcDlg::OnClickedButton28_add()
{
	m_string.Append(L"+");
	UpdateData(false);
}


void calcDlg::OnClickedButton24_sub()
{
	m_string.Append(L"-");
	UpdateData(false);
}


void calcDlg::OnClickedButton19_multi()
{
	m_string.Append(L"*");
	UpdateData(false);
}


void calcDlg::OnClickedButton14_div()
{
	m_string.Append(L"/");
	UpdateData(false);
}


void calcDlg::OnClickedButton15_model()
{
	m_string.Append(L"%");
	UpdateData(false);
}


void calcDlg::OnClickedButton25_result()
{
	int strLen = m_string.GetLength();
	WCHAR buf[32];
	_itow_s(strLen, buf,32,  10);

	//int n = 123;
	//CString test;
	//test.Format(L"%d", n);
	//WCHAR ch = test[0];

	//CString test = L"123";
	//int a = _wtoi(test);
	//int b = a + 1;

	//MessageBox(m_string);
	//WCHAR wch = m_string[0];
	//CString tmp;
	//tmp.AppendChar(wch);
	//MessageBox(tmp);

	CString strLeft;
	CString  strRight;
	WCHAR  oper;
	BOOL flag = true; //�Ƿ��һ������������
	int nRest;
	CString strRest;
	for (int i = 0; i < strLen; i++) {
		if ((m_string[i] == L'+' || m_string[i] == L'-' || m_string[i] == L'*' || m_string[i] == '/') && flag) {
			//��һ������������, ��ʼȡ��ֵ
			flag = false;
			//���������
			oper = m_string[i];
		}
		else if (m_string[i] == L'+' || m_string[i] == L'-' || m_string[i] == L'*' || m_string[i] == '/') {
			//���������� ��ʼ�����ϸ����������ߵĽ��, ��������ֵ
			switch (oper) {
			case L'+':
				nRest = _wtoi(strRight) + _wtoi(strLeft);
				break;
			case L'-':
				nRest = _wtoi(strRight) - _wtoi(strLeft);
				break;
			case L'*':
				nRest = _wtoi(strRight) * _wtoi(strLeft);
				break;
			case L'/':
				nRest = _wtoi(strRight) / _wtoi(strLeft);
				break;
			default:
				MessageBox(L"����������");
				return;

			}
			strLeft.Empty();
			strLeft.Format(L"%d", nRest);
			strRight.Empty();
			//���������
			oper = m_string[i];
		}
		else if(flag){
			//ȡ������ֵ
			strLeft.AppendChar(m_string[i]);
		}
		else if(!flag){ //ȡ��ֵ
			strRight.AppendChar(m_string[i]);
		}

		if (i == strLen - 1) { //������
			int nLeft = _wtoi(strLeft);
			int nRight = _wtoi(strRight);
			switch (oper) {
			case L'+':
				nRest = nLeft + nRight;
				break;
			case L'-':
				nRest = nLeft - nRight;
				break;
			case L'*':
				nRest = nLeft * nRight;
				break;
			case L'/':
				nRest = nLeft / nRight;
				break;
			default:
				MessageBox(L"����������");
				return;
			}
			strLeft.Empty();
			strRight.Empty();

			strRest.Empty();
			strRest.Format(L"%d", nRest);
			m_strResult = strRest;
			UpdateData(false);
		}
		
	}

	

	



}


void calcDlg::OnClickedButton1_clear()
{
	m_string.Empty();
	m_strResult.Empty();
	UpdateData(false);
}
