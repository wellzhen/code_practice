#pragma once


// CDiaB11 �Ի���

class CDiaB11 : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaB11)

public:
	CDiaB11(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDiaB11();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIAB11 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
