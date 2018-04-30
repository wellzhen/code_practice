#pragma once


// CDiaA222 对话框

class CDiaA222 : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaA222)

public:
	CDiaA222(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDiaA222();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
