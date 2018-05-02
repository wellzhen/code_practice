#pragma once


// CProcListCtrl2

class CProcListCtrl2 : public CListCtrl
{
	DECLARE_DYNAMIC(CProcListCtrl2)

public:
	CProcListCtrl2();
	virtual ~CProcListCtrl2();
	void InsertColumnCustom(DWORD dwCount, ...);
	void InsertItemCustom(DWORD dwCount, ...);
protected:
	DECLARE_MESSAGE_MAP()
};


