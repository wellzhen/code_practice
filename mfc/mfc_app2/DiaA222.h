#pragma once


// CDiaA222 �Ի���

class CDiaA222 : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaA222)

public:
	CDiaA222(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDiaA222();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
