#pragma once


// CDiaA111 �Ի���

class CDiaA111 : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaA111)

public:
	CDiaA111(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDiaA111();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
