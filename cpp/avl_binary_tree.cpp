#include "stdafx.h"


class Avl
{
public:
	typedef struct _NODE {
		int nData;
		_NODE* pLchild;
		_NODE* pRchild;
	} NODE;
	bool insert(int nData);
	
	void preOrder(); 
	void midOrder();
	void postOrder(); 

private:
	bool insertNode(NODE* & pNode, int nData);
	int getHeight(NODE* & pNode);
	void preOrderTraverse(NODE*& pNode);
	void midOrderTraverse(NODE*& pNode);
	void postOrderTraverse(NODE*& pNode);
private:
	NODE* m_pRoot;
	int m_nCount;
};

bool Avl::insert(int nData)
{
	bool res = insertNode(m_pRoot, nData);
	return res;
}

bool Avl::insertNode(NODE* & pNode, int nData)
{
	if (pNode == NULL) {
		pNode = new NODE{};
		pNode->nData = nData;
		m_nCount++;
		return true;
	}

	if (getHeight(pNode->pLchild) >= getHeight(pNode->pRchild)) {//insert into left
		insertNode(pNode->pLchild, nData);
	}
	else {
		insertNode(pNode->pRchild, nData);
	}
	return false;
}

int Avl::getHeight(NODE* & pNode)
{
	if (pNode == NULL) {
		return 0;
	}
	int nLeftHeight = getHeight(pNode->pLchild);
	int nRightHeight = getHeight(pNode->pRchild);

	return (nLeftHeight > nRightHeight ? nLeftHeight : nRightHeight) + 1;
}

void Avl::preOrder()
{
	preOrderTraverse(m_pRoot);
}
void Avl::midOrder()
{
	midOrderTraverse(m_pRoot);
}
void Avl::postOrder()
{
	postOrderTraverse(m_pRoot);
}

void Avl::preOrderTraverse(NODE*& pNode)
{
	if (pNode == NULL) {
		return;
	}
	printf("%d ", pNode->nData);//print rootNode
	preOrderTraverse(pNode->pLchild);
	preOrderTraverse(pNode->pRchild);
}

void Avl::midOrderTraverse(NODE*& pNode)
{
	if (pNode == NULL) {
		return;
	}
	preOrderTraverse(pNode->pLchild);
	printf("%d ", pNode->nData);//print rootNode
	preOrderTraverse(pNode->pRchild);
}