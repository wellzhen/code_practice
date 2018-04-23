#include "stdafx.h"
#include <Windows.h>
#include <vector>
using std::vector;

typedef struct _COORD {
	int nX; 
	int nY;
	int  nDir;
} COORD, *PCOORD;

typedef struct _STARNODE {
	void setG(int g) {
		G = g;
	}
	void  setH_G(COORD endPos) {
		H = abs(self.nX - endPos.nX) + abs(self.nY - endPos.nY);
		F = G + H;
	}
	int G;
	int H;
	int F;
	COORD  self;
} STARNODE, *PSTARNODE;

class CAstar
{
public:
	void init()
	{

	}
private:
	void __setStartPos(int x, int y)
	{
		m_startPos.nX = x;
		m_startPos.nY = y;
	}
	void __setEndPos(int x, int y)
	{
		m_endPos.nX = x;
		m_endPos.nY = y;
	}
	void __setMap()
	{

	}
	void __setBlockMap()
	{

	}

private:
	vector<STARNODE> m_vecOpen;
	vector<STARNODE> m_vecClose;
	COORD m_startPos;
	COORD m_endPos;
	int g_nMap[40][80];
	int g_nBlockMap[40][80];
};