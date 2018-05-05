#pragma once
#include "afxeditbrowsectrl.h"
#include "FilesTree.h"


// CFilesDialog 对话框

class CFilesDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CFilesDialog)

public:
	CFilesDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFilesDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FILE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void TraverseFiles(CString fullPath, HTREEITEM  hTreeNode);
	void TraverseDeleteFiles(CString fullPath, CString postFix);
	afx_msg void OnEnChangeFileBrowser();
public:
	CMFCEditBrowseCtrl m_FileBrowser;
	CFilesTree m_FilesTree;
	CString m_EditFilePostfix;
	afx_msg void OnBnClickedButtonClearFile();
};
