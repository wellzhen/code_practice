// data_struct.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>

/*
时间复杂度 n^2
*/
void sort(int * pArr, int nCount)
{
	for (int i = 0; i < nCount - 1; i++) {
		for (int j = 0; j < nCount - i - 1; j++) {
			if (pArr[j] > pArr[j + 1]) {
				int nTemp = pArr[j];
				pArr[j] = pArr[j + 1];
				pArr[j + 1] = nTemp;
			}
		}
	}
}

int main_1()
{
	int nArr[] = { 7,6,9,5,3,1,2,0 };
	sort(nArr, _countof(nArr));

	for (int i = 0; i < _countof(nArr); i++) {
		printf("%d  ", nArr[i]);
	}
	printf("\n");
	return 0;
}


template <class T>
class CVector {
public:
	CVector()
	{
		m_nCurrentCount = 0;
		m_nMaxCount = 1;
		pHead = new T[m_nMaxCount];
	}

	void push_back(T nData)
	{
		extend();
		pHead[m_nCurrentCount] = nData;
		m_nCurrentCount++;
	}

	void pop_back()
	{
		if (m_nCurrentCount == 0) {
			return;
		}
		m_nCurrentCount--;
	}

	int  max_size()
	{
		return m_nMaxCount;
	}

	int size()
	{
		return m_nCurrentCount;
	}
	bool empty()
	{
		return m_nCurrentCount == 0;
	}

	int capacity()
	{
		return m_nMaxCount;
	}


	void  insert(int index, T nData)
	{
		if (index < 0 || index > m_nCurrentCount) {
			return;
		}
		extend();
		if (index == m_nCurrentCount) {
			pHead[index] = nData;
			m_nCurrentCount++;
			return;
		}

		for (int i = m_nCurrentCount; i >= index + 1; i--) {
			pHead[i] = pHead[i - 1];
		}
		pHead[index] = nData;
		m_nCurrentCount++;
		return;
	}

	void erase(int index)
	{
		if (index < 0 || index >= m_nCurrentCount) {
			return;
		}
		if (index == m_nCurrentCount - 1) {
			m_nCurrentCount--;
			return;
		}
		//前移
		for (int i = index; i <= m_nCurrentCount - 2; i++) {
			pHead[i] = pHead[i + 1];
		}
		m_nCurrentCount--;
		return;

	}

	void clear()
	{
		m_nCurrentCount = 0;
	}

	void extend()
	{
		if (m_nCurrentCount == m_nMaxCount) {
			m_nMaxCount++; // -_-
			T * pNewHead = new T[m_nMaxCount];
			memcpy_s(pNewHead, sizeof(T) * m_nMaxCount, pHead, sizeof(T) * m_nCurrentCount);
		}
	}
	void print()
	{
		for (int i = 0; i < m_nCurrentCount; i++) {
			printf("%1.1f ", pHead[i]);
		}

		printf("\n当前: %d 容量：%d", m_nCurrentCount, m_nMaxCount);
		printf("\n");
	}

	~CVector()
	{
		delete pHead;
		pHead = NULL;
	}
private:
	T *pHead;
	int m_nCurrentCount;
	int m_nMaxCount;
};

int main_2()
{
	CVector<double> myArr;
	myArr.push_back(0);
	myArr.push_back(3.3);
	myArr.push_back(4.4);
	myArr.print();

	myArr.insert(1, 2.2);
	myArr.insert(1, 1.1);
	myArr.print();

	myArr.insert(1, 8.8);
	myArr.print();

	myArr.erase(1);
	myArr.print();

	myArr.pop_back();
	myArr.print();

	myArr.clear();
	myArr.print();

	return 0;
}


class  CList
{
public:
	typedef struct _NODE {
		int nData;
		_NODE * pNext;
	}NODE, PNODE;

	CList()
	{
		m_nCurrentCount = 0;
		m_pHead = NULL;
	}
	void push_back(int nData)
	{
		NODE* pNew = (NODE*)malloc(sizeof(NODE));
		pNew->nData = nData;
		pNew->pNext = NULL;

		if (m_nCurrentCount == 0) {
			m_pHead = pNew;
			m_nCurrentCount++;
			return;
		}
		NODE* m_pCurrent = m_pHead;
		for (int i = 0; i < m_nCurrentCount - 1; i++) {
			m_pCurrent = m_pCurrent->pNext;
		}

		m_pCurrent->pNext = pNew;
		m_nCurrentCount++;
	}

	void push_front(int nData)
	{
		if (m_nCurrentCount == 0) {
			push_back(nData);
			return;
		}
		NODE* pNew = (NODE*)malloc(sizeof(NODE));
		pNew->nData = nData;
		pNew->pNext = m_pHead;

		m_pHead = pNew;

		m_nCurrentCount++;
		return;
	}



	void pop_back()
	{
		if (m_nCurrentCount == 0) {
			return;
		}

		if (m_nCurrentCount == 1) {
			delete m_pHead;
			m_pHead = NULL;
			m_nCurrentCount--;
			return;
		}
		NODE* pBefore = m_pHead;
		for (int i = 0; i < m_nCurrentCount - 2; i++) {
			pBefore = pBefore->pNext;
		}

		delete pBefore->pNext;
		pBefore->pNext = NULL;

		m_nCurrentCount--;
	}

	void pop_front()
	{
		if (m_nCurrentCount == 0) {
			return;
		}
		if (m_nCurrentCount == 1) {
			delete m_pHead;
			m_pHead = NULL;
			m_nCurrentCount--;
			return;
		}
		//2个及以上
		NODE* pAfter = m_pHead->pNext;
		delete m_pHead;
		m_pHead = pAfter;
		m_nCurrentCount--;
		return;
	}

	void insert(int index, int nData)
	{
		if (index < 0 || index > m_nCurrentCount) {
			return;
		}

		if (index == m_nCurrentCount) {//最后一个元素
			push_back(nData);
			//m_nCurrentCount++;  //push_back含++
			return;
		}
		if (index == 0) { //插入到首位
			push_front(nData);
			//push_front含++
			return;
		}

		NODE* pNew = (NODE*)malloc(sizeof(NODE));
		pNew->nData = nData;
		pNew->pNext = NULL;

		//index > 0
		NODE* pAfter = NULL;
		NODE* pBefore = m_pHead;
		for (int i = 0; i < index - 1; i++) {
			pBefore = pBefore->pNext;
		}
		pAfter = pBefore->pNext;
		//插入
		pBefore->pNext = pNew;
		pNew->pNext = pAfter;

		m_nCurrentCount++;
		return;


	}

	void erase(int index)
	{
		if (index < 0 || index > m_nCurrentCount - 1) {
			return;
		}

		if (m_nCurrentCount == 1) { // index 也肯定是0
			delete m_pHead;
			m_pHead = NULL;
			m_nCurrentCount--;
			return;
		}

		if (index == 0) {
			NODE* pAfter = m_pHead->pNext;
			delete m_pHead;
			m_pHead = pAfter;
			m_nCurrentCount--;
			return;
		}

		NODE* pBefore = m_pHead;
		for (int i = 0; i < index - 1; i++) {
			pBefore = pBefore->pNext;
		}
		NODE* pAfter = pBefore->pNext->pNext;
		delete pBefore->pNext;
		pBefore->pNext = pAfter;
		m_nCurrentCount--;
		return;




	}

	void print()
	{
		NODE* pCurrent = m_pHead;
		for (int i = 0; i < m_nCurrentCount; i++) {
			if (i != 0) {
				printf(" -> ");
			}
			printf("%d", pCurrent->nData);
			pCurrent = pCurrent->pNext;
		}
		printf("\n");
	}




	~CList()
	{
		//
	}
private:
	NODE* m_pHead;
	int m_nCurrentCount;
};


int main()
{
	CList list;
	list.push_back(1);
	list.print();
	list.push_back(2);
	list.print();
	list.push_back(3);
	list.print();

	//第四行
	list.insert(0, 110);
	list.print();
	list.insert(1, 111);
	list.print();
	list.insert(5, 99999);
	list.print();

	printf("push_front:\n");
	list.push_front(444);
	list.print();
	printf("pop_back\n");
	list.pop_back();
	list.print();
	list.pop_back();
	list.print();
	printf("pop_front:\n");
	list.pop_front();
	list.print();
	list.pop_front();
	list.print();
	printf("erase:\n");
	list.erase(1);
	list.print();

	return 0;
}
