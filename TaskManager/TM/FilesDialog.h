#pragma once
#include "afxeditbrowsectrl.h"
#include "FilesTree.h"


// CFilesDialog �Ի���

class CFilesDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CFilesDialog)

public:
	CFilesDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFilesDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FILE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
