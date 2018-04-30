#pragma once


// CDiaA333 对话框

class CDiaA333 : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaA333)

public:
	CDiaA333(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDiaA333();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
