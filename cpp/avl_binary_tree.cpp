#include "stdafx.h"


class CAvl
{
public:
	typedef struct _NODE {
		int nData;
		_NODE* pLchild;
		_NODE* pRchild;
	} NODE;
	CAvl();
	bool insert(int nData);
	bool erase(int nData);
	void preOrder(); 
	void midOrder();
	void postOrder(); 

private:
	bool __insertNode(NODE* & pNode, int nData);
	bool __eraseNode(NODE* & pNode, int nData);
	bool __erase(int nData);
	NODE*  __getMaxOfLeft(NODE*& pNode); 
	NODE*  __getMinOfRight(NODE*& pNode);
	int  __getHeight(NODE* & pNode);
	void __preOrderTraverse(NODE*& pNode);
	void __midOrderTraverse(NODE*& pNode);
	void __postOrderTraverse(NODE*& pNode);
private:
	NODE* m_pRoot;
	int m_nCount;
};


CAvl::CAvl()
{
	//m_nCount = 0;
}

bool CAvl::insert(int nData)
{
	bool res = __insertNode(m_pRoot, nData);
	return res;
}

bool CAvl::__insertNode(NODE* & pNode, int nData)
{
	if (pNode == NULL) {
		pNode = new NODE{};
		pNode->nData = nData;
		m_nCount++;
		return true;
	}

	if (__getHeight(pNode->pLchild) >= __getHeight(pNode->pRchild)) {//insert into left
		__insertNode(pNode->pLchild, nData);
	}
	else {
		__insertNode(pNode->pRchild, nData);
	}
	return false;
}

bool CAvl::erase(int nData)
{
	return __eraseNode(m_pRoot, nData);
}

bool CAvl::__eraseNode(NODE* & pNode, int nData)
{
	if (pNode == NULL) {
		return false;
	}
	if (pNode->nData == nData) {
		if (pNode->pLchild  == NULL && pNode->pRchild == NULL) {
			m_nCount--;
			pNode = NULL;
			return true;
		}
		else if(__getHeight(pNode->pLchild) >= __getHeight(pNode->pRchild)){// has child
			NODE *pMax = __getMaxOfLeft(pNode->pLchild);
			int nMax = pMax->nData;
			pNode->nData = nMax;
			__eraseNode(pNode->pLchild, nMax);
		}
		else if (__getHeight(pNode->pLchild) < __getHeight(pNode->pRchild)) {// has child
			NODE *pMax = __getMinOfRight(pNode->pRchild);
			int nMax = pMax->nData;
			pNode->nData = nMax;
			__eraseNode(pNode->pRchild, nMax);
		}
	}
	else {
		if (__getHeight(pNode->pLchild) >= __getHeight(pNode->pRchild)) {// has child
			__eraseNode(pNode->pLchild, nData);
		}
		else if (__getHeight(pNode->pLchild) < __getHeight(pNode->pRchild)) {// has child
			__eraseNode(pNode->pRchild, nData);
		}
	}
	return false;
}


int CAvl::__getHeight(NODE* & pNode)
{
	if (pNode == NULL) {
		return 0;
	}
	int nLeftHeight = __getHeight(pNode->pLchild);
	int nRightHeight = __getHeight(pNode->pRchild);

	return (nLeftHeight > nRightHeight ? nLeftHeight : nRightHeight) + 1;
}

CAvl::NODE* CAvl::__getMaxOfLeft(NODE*& pNode)
{
	if (pNode == NULL) {
		return NULL;
	}
	if (pNode->pRchild == NULL) {
		return pNode;
	}
	return __getMaxOfLeft(pNode->pRchild);

}

CAvl::NODE* CAvl::__getMinOfRight(NODE*& pNode)
{
	if (pNode == NULL) {
		return NULL;
	}
	if (pNode->pLchild == NULL) {
		return pNode;
	}
	return __getMinOfRight(pNode->pLchild);

}

void CAvl::preOrder()
{
	__preOrderTraverse(m_pRoot);
}
void CAvl::midOrder()
{
	__midOrderTraverse(m_pRoot);
}
void CAvl::postOrder()
{
	__postOrderTraverse(m_pRoot);
}

void CAvl::__preOrderTraverse(NODE*& pNode)
{
	if (pNode == NULL) {
		return;
	}
	printf("%d ", pNode->nData);//print rootNode
	__preOrderTraverse(pNode->pLchild);
	__preOrderTraverse(pNode->pRchild);
}

void CAvl::__midOrderTraverse(NODE*& pNode)
{
	if (pNode == NULL) {
		return;
	}
	__preOrderTraverse(pNode->pLchild);
	printf("%d ", pNode->nData);//print rootNode
	__preOrderTraverse(pNode->pRchild);
}

void CAvl::__postOrderTraverse(NODE*& pNode)
{
	if (pNode == NULL) {
		return;
	}
	__preOrderTraverse(pNode->pLchild);
	__preOrderTraverse(pNode->pRchild);
	printf("%d ", pNode->nData);//print rootNode
}

int main()
{
	CAvl bt;
	bt.insert(1);
	bt.insert(2);
	bt.insert(3);
	bt.preOrder();

	bt.erase(3);
	bt.preOrder();
	return 0;
}