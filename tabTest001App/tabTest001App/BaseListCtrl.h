#pragma once


// CBaseListCtrl

class CBaseListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CBaseListCtrl)

public:
	CBaseListCtrl();
	virtual ~CBaseListCtrl();
public:
	void InsertColumnCustom(DWORD dwCount, ...);
	void InsertItemCustom(DWORD dwCount, ...);

protected:
	DECLARE_MESSAGE_MAP()
};


