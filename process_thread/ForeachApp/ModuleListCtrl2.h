#pragma once


// CModuleListCtrl2

class CModuleListCtrl2 : public CListCtrl
{
	DECLARE_DYNAMIC(CModuleListCtrl2)

public:
	CModuleListCtrl2();
	virtual ~CModuleListCtrl2();
	void InsertColumnCustom(DWORD dwCount, ...);
	void InsertItemCustom(DWORD dwCount, ...);
protected:
	DECLARE_MESSAGE_MAP()
};


