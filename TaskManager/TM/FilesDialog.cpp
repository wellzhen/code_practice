// FilesDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TM.h"
#include "FilesDialog.h"
#include "afxdialogex.h"
#include <Strsafe.h>


// CFilesDialog �Ի���

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


// CFilesDialog ��Ϣ�������


void CFilesDialog::OnEnChangeFileBrowser()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString selectedPath;
	GetDlgItemText(IDC_FILE_BROWSER, selectedPath);
	//MessageBox(selectedPath);
	if (selectedPath.IsEmpty()) {
		MessageBox(L"��ѡ��Ŀ¼");
		return;
	}
	//ɾ���������ڵ�
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
	//��ȡ��һ���ļ�/Ŀ¼, ����ò��Ҿ��
	HANDLE hFileList = FindFirstFile(strFilePath, &findFileData);
	if (INVALID_HANDLE_VALUE == hFileList) {
		return;
	}

	do {
		strFileName = findFileData.cFileName;
		if (strFileName[0] == '.' || strFileName[0] == '..') {
			continue;
		}
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {// Ŀ¼
			//ǰ����ʾ
			CString info;
			info.Format(L"%s", findFileData.cFileName);
			HTREEITEM hChildNode = m_FilesTree.InsertItem(info, hRootNode);
			//��ȡ����·��
			CString strFullPath;
			strFilePath.TrimRight(L"\\*");
			strFullPath.Format(L"%s\\%s", strFilePath, strFileName);
			TraverseFiles(strFullPath, hChildNode);
		}
		else { //�ļ�
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	CString selectedPath;
	GetDlgItemText(IDC_FILE_BROWSER, selectedPath);
	if (m_EditFilePostfix.IsEmpty()) {
		MessageBox(L"����дҪɾ�����ļ���׺");
		return;
	}
	else if (selectedPath.IsEmpty()) {
		MessageBox(L"��ѡ��Ŀ¼");
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
	//��ȡ��һ���ļ�/Ŀ¼, ����ò��Ҿ��
	HANDLE hFileList = FindFirstFile(strFilePath, &findFileData);
	if (INVALID_HANDLE_VALUE == hFileList) {
		return;
	}

	do {
		strFileName = findFileData.cFileName;
		if (strFileName[0] == '.' || strFileName[0] == '..') {
			continue;
		}
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {// Ŀ¼

			//��ȡ����·��
			CString strFullPath;
			strFilePath.TrimRight(L"\\*");
			strFullPath.Format(L"%s\\%s", strFilePath, strFileName);
			TraverseDeleteFiles(strFullPath, strDeletePostFix);
		}
		else { //�ļ�
			//�ж��Ƿ����ɾ��
			//��ȡ�ļ�.��λ��
			int DotPos = strFileName.ReverseFind('.');
			if (DotPos == -1) {
				continue;
			}
			int length = strFileName.GetLength();
			int postFixLenght = length - DotPos;
			if (postFixLenght <= 1) {
				MessageBox(L"�ļ���׺���쳣");
				continue;
			}
			CString strPostfix = strFileName.Right(postFixLenght);
			strPostfix.Append(L"\\");
			if (strDeletePostFix.Find(strPostfix) != -1) {
				//ɾ���ļ�
				CString deleteInfo;
				//deleteInfo.Format(L"ɾ���ļ�:%s", strFileName);
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
