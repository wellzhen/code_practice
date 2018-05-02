#pragma once


// CMyListCtrl

class CMyListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CMyListCtrl)

public:
	CMyListCtrl();
	virtual ~CMyListCtrl();
	void InsertColumnCustom(DWORD dwCount ...);
protected:
	DECLARE_MESSAGE_MAP()
};


