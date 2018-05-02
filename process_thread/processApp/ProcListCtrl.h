#pragma once


// CProcListCtrl

class CProcListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CProcListCtrl)

public:
	CProcListCtrl();
	virtual ~CProcListCtrl();
	void InsertColumnCustom(DWORD dwCount, ...);
	void InsertItemCustom(DWORD dwCount, ...);
protected:
	DECLARE_MESSAGE_MAP()
};


