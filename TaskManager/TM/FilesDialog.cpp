// FilesDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "TM.h"
#include "FilesDialog.h"
#include "afxdialogex.h"
#include <Strsafe.h>


// CFilesDialog 对话框

IMPLEMENT_DYNAMIC(CFilesDialog, CDialogEx)

CFilesDialog::CFilesDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_FILE, pParent)
	, m_EditFilePostfix(_T(""))
{

}

CFilesDialog::~CFilesDialog()
{
}

void CFilesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILE_BROWSER, m_FileBrowser);
	DDX_Control(pDX, IDC_TREE_FILE, m_FilesTree);
	DDX_Text(pDX, IDC_EDIT_FILE_POSTFIX, m_EditFilePostfix);
}


BEGIN_MESSAGE_MAP(CFilesDialog, CDialogEx)
	ON_EN_CHANGE(IDC_FILE_BROWSER, &CFilesDialog::OnEnChangeFileBrowser)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_FILE, &CFilesDialog::OnBnClickedButtonClearFile)
END_MESSAGE_MAP()


// CFilesDialog 消息处理程序


void CFilesDialog::OnEnChangeFileBrowser()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	// TODO:  在此添加控件通知处理程序代码
	CString selectedPath;
	GetDlgItemText(IDC_FILE_BROWSER, selectedPath);
	//MessageBox(selectedPath);
	if (selectedPath.IsEmpty()) {
		MessageBox(L"请选择目录");
		return;
	}
	//删除所有树节点
	m_FilesTree.DeleteAllItems();
	
	HTREEITEM hRoot = TVI_ROOT;
	TraverseFiles(selectedPath, hRoot);


}

void CFilesDialog::TraverseFiles(CString fullPath, HTREEITEM  hRootNode)
{

	CString strFileName;
	CString strFilePath;
	
	strFilePath = fullPath;
	strFilePath.Append(L"\\*");

	WIN32_FIND_DATA findFileData;
	//获取第一个文件/目录, 并获得查找句柄
	HANDLE hFileList = FindFirstFile(strFilePath, &findFileData);
	if (INVALID_HANDLE_VALUE == hFileList) {
		return;
	}

	do {
		strFileName = findFileData.cFileName;
		if (strFileName[0] == '.' || strFileName[0] == '..') {
			continue;
		}
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {// 目录
			//前端显示
			CString info;
			info.Format(L"%s", findFileData.cFileName);
			HTREEITEM hChildNode = m_FilesTree.InsertItem(info, hRootNode);
			//获取完整路径
			CString strFullPath;
			strFilePath.TrimRight(L"\\*");
			strFullPath.Format(L"%s\\%s", strFilePath, strFileName);
			TraverseFiles(strFullPath, hChildNode);
		}
		else { //文件
			CString info;
			SYSTEMTIME sysCreationTime, sysAccessTime, sysWriteTime;
			FileTimeToSystemTime(&findFileData.ftCreationTime, &sysCreationTime);
			FileTimeToSystemTime(&findFileData.ftLastAccessTime, &sysAccessTime);
			FileTimeToSystemTime(&findFileData.ftLastWriteTime, &sysWriteTime);
			info.Format(L"%s  %d byte  Creation(%d/%d/%d %d:%d:%d) Access(%d/%d/%d %d:%d:%d) Write(%d/%d/%d %d:%d:%d) ", findFileData.cFileName, findFileData.nFileSizeLow,
				sysCreationTime.wYear, sysCreationTime.wMonth, sysCreationTime.wDay, sysCreationTime.wHour, sysCreationTime.wMinute, sysCreationTime.wSecond,
				sysAccessTime.wYear, sysAccessTime.wMonth, sysAccessTime.wDay, sysAccessTime.wHour, sysAccessTime.wMinute, sysAccessTime.wSecond,
				sysWriteTime.wYear, sysWriteTime.wMonth, sysWriteTime.wDay, sysWriteTime.wHour, sysWriteTime.wMinute, sysWriteTime.wSecond
			);
			m_FilesTree.InsertItem(info, hRootNode);
			continue;
		}


	} while (FindNextFile(hFileList, &findFileData));
	//CloseHandle(hFileList);

	return;
}


void CFilesDialog::OnBnClickedButtonClearFile()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CString selectedPath;
	GetDlgItemText(IDC_FILE_BROWSER, selectedPath);
	if (m_EditFilePostfix.IsEmpty()) {
		MessageBox(L"请填写要删除的文件后缀");
		return;
	}
	else if (selectedPath.IsEmpty()) {
		MessageBox(L"请选择目录");
		return;
	}


	//MessageBox(m_EditFilePostfix);
	TraverseDeleteFiles(selectedPath, m_EditFilePostfix);
}

void CFilesDialog::TraverseDeleteFiles(CString fullPath, CString strDeletePostFix)
{

	CString strFileName;
	CString strFilePath;

	strFilePath = fullPath;
	strFilePath.Append(L"\\*");

	WIN32_FIND_DATA findFileData;
	//获取第一个文件/目录, 并获得查找句柄
	HANDLE hFileList = FindFirstFile(strFilePath, &findFileData);
	if (INVALID_HANDLE_VALUE == hFileList) {
		return;
	}

	do {
		strFileName = findFileData.cFileName;
		if (strFileName[0] == '.' || strFileName[0] == '..') {
			continue;
		}
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {// 目录

			//获取完整路径
			CString strFullPath;
			strFilePath.TrimRight(L"\\*");
			strFullPath.Format(L"%s\\%s", strFilePath, strFileName);
			TraverseDeleteFiles(strFullPath, strDeletePostFix);
		}
		else { //文件
			//判断是否可以删除
			//获取文件.的位置
			int DotPos = strFileName.ReverseFind('.');
			if (DotPos == -1) {
				continue;
			}
			int length = strFileName.GetLength();
			int postFixLenght = length - DotPos;
			if (postFixLenght <= 1) {
				MessageBox(L"文件后缀有异常");
				continue;
			}
			CString strPostfix = strFileName.Right(postFixLenght);
			strPostfix.Append(L"\\");
			if (strDeletePostFix.Find(strPostfix) != -1) {
				//删除文件
				CString deleteInfo;
				//deleteInfo.Format(L"删除文件:%s", strFileName);
				CString strFullPath;
				strFilePath.TrimRight(L"\\*");
				strFullPath.Format(L"%s\\%s", strFilePath, strFileName);
				//DeleteFile(strFullPath);
				MessageBox(deleteInfo);
			}
			continue;
		}


	} while (FindNextFile(hFileList, &findFileData));
	//CloseHandle(hFileList);

	return;
}
