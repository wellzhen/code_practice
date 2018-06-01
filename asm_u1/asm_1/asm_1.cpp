// asm_1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string.h>




void Test()
{
	int data[6] = { 1,2,3,4,5,6 };
	_asm
	{
		push eax;
		push ebx;
		push edx;

		lea edx,  data; //存入首地址 error !
		//交换第一个
		mov eax, [edx];
		mov ebx, [edx + 5];
		xchg eax, [edx + 5];
		xchg ebx, [edx];
		//交换第二个
		mov eax, [edx + 1];
		mov ebx, [edx + 4];
		xchg eax, [edx + 4];
		xchg ebx, [edx + 1];
		//交换第三个
		mov eax, [edx + 2];
		mov ebx, [edx + 3];
		xchg eax, [edx + 3];
		xchg ebx, [edx + 2];

		pop edx;
		pop ebx;
		pop eax;
	}
	for (int i = 0; i < 6; i++) {
		printf("%d\n", data[i]);
	}
	
	int a = 0;
}

int addSon(int x, int y) 
{
	return x + y;
}
void myAdd(int a, int b, int c, int d, int e)
{
	 int n1 = 4;
	 int  n2 = 5;
	 int n3 = 6;
	 int n4 = 7;
	 int n5 = 8;
	 int n6 = 9;

	 int tmp1;
	 int tmp2;
	 tmp1 = addSon(a, b);
	 tmp2 = addSon(n1, n2);
		
}

void myloop(int x)
{
	int sum = 0;
	do {
		sum += x;
		x--;
	} while (x > 0);

}

void testArr()
{
	int data[] = { 1, 2, 3, 4, 5, 6 };
	int tmp;
	tmp = data[0];
	data[0] = data[5];
	data[5] = tmp;

}

int g_num = 1;
void myCmp(int x, int y)
{
	if (x > y) {
		g_num = x;
	}
	else {
		g_num = y;
	}
}
void echo()
{
	printf("hello world");
	getchar();
}

void hello()
{
	int arr[5] = { 1, 2, 3, 4, 5 };
	//arr[6] = (int)echo;
	int r;
	r = arr[0];
	r = arr[1];
	r = arr[2];
	r = arr[3];
	r = arr[4];
}



void getLen()
{
	char * str = "hello world";
	int len = strlen(str);


}
int main()
{
	//Test();
	int a = 11;
	int b = 12;
	int c = 13;
	int d = 14;
	int e = 15;
	int f = 16;
	int g = 17;
	//myAdd(a, b, c, d, e);
	//getLen();
	hello();
	myloop(3);
	char a1 = 'a';
	int x = 6;
	int y = 7;
	//myCmp(x, y);
	//printf("%d\n", a);
	//Test();
	int ffff = 666;
	ffff += 999;
	testArr();
}

