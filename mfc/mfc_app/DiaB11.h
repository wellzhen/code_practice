#pragma once


// CDiaB11 对话框

class CDiaB11 : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaB11)

public:
	CDiaB11(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDiaB11();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIAB11 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
