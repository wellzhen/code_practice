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
protected:
	// socket�й�
	afx_msg LRESULT OnMysocket(WPARAM wParam, LPARAM lParam);
	void InsertOrDeleteUser(CHATUPDATEUSER &objUpdate);
	void ChatForOne2One(CHATONE2ONE &objOne2One);

public:
	virtual BOOL OnInitDialog();
	//���������Ϣ
	afx_msg void OnClickedButtonSendWord();
	//˫�������û��б���û�, 1V1����
	afx_msg void OnDblclkListUserOnline(NMHDR *pNMHDR, LRESULT *pResult);
	//�Ҽ��˵�����
	//�Ҽ��˵���Ϣ: ��Ӻ���
	//�Ҽ��˵���Ϣ: �����û�
	//�Ҽ��˵���Ϣ: ��ѯ�����¼
	//��ʱ����Ϣ: ���ڵȴ���ȡ��Ϣ��¼���


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

	virtual void OnOK();
};
