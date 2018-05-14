#pragma once
#include "afxcmn.h"
#include <map>
#include "ClientSocket.h"
using std::map;

// CMainChatDlg �Ի���

class CMainChatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainChatDlg)

public:
	CMainChatDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CMainChatDlg(CClientSocket* pClient, CWnd* pParent = NULL);
	virtual ~CMainChatDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINCHATDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//��½���컹����������
	BOOL m_bLogin = FALSE;
	//����send/recv�������, socket����ָ��
	CClientSocket * m_pClient;
	
	// Ⱥ����Ϣ��ʾ��
	CString m_strChatShow;
	// �����͵���Ϣ
	CString m_strChatSend;
	// list�ؼ�, ���ߵ��û��б�
	CListCtrl m_listUserName;

	//1V1������map ��
	map<CString, CDialogEx*> m_map;

	//����������û��б�ʱ������ֵ
	DWORD m_dwNameIndex = 0;
	//�����¼����ָ��
	//CDlgRecord* m_pDlgRecord = nullptr;



};
