#pragma once


// CDiaA11 �Ի���

class CDiaA11 : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaA11)

public:
	CDiaA11(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDiaA11();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
