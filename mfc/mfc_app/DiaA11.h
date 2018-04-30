#pragma once


// CDiaA11 对话框

class CDiaA11 : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaA11)

public:
	CDiaA11(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDiaA11();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
