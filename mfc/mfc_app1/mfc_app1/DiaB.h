#pragma once


// CDiaB �Ի���

class CDiaB : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaB)

public:
	CDiaB(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDiaB();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
