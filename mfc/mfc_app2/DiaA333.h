#pragma once


// CDiaA333 �Ի���

class CDiaA333 : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaA333)

public:
	CDiaA333(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDiaA333();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
