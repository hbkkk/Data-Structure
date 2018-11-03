#include <iostream>
#include <stdlib.h>
using namespace std;

int a = 10;
int b = 99;

typedef struct{
	int *p;
	int length;
}SPTR;

void f(SPTR T)    //一级指针作为形参，不能改变指针变量的值！！！
{
	int *q = &b;
	T.p = q;
}

void g(SPTR &T)   //一级指针的引用作为形参，可以改变指针变量的值(即指针变量存放的地址值)！！！！！！！！！！！！
{
	int *q = &b;
	T.p = q;
}

void f1(SPTR T)
{
	int *q = (int*)malloc(sizeof(int));
	q = &b;
	T.p = q;
}

int main()
{

	cout << "a: " << a << " ,&a: " << &a << endl;
	cout << "b: " << b << " ,&b: " << &b << endl;

	SPTR stp;
	stp.p = &a;
	cout << "              	*stp.p: " << *stp.p << " ,stp.p: " << stp.p << " ,&stp.p: " << &stp.p << endl;

	f(stp);
	cout << "after f(stp), *stp.p: " << *stp.p << " ,stp.p: " << stp.p << " ,&stp.p: " << &stp.p << endl;

	f1(stp);
	cout << "after f1(stp), *stp.p: " << *stp.p << " ,stp.p: " << stp.p << " ,&stp.p: " << &stp.p << endl;

	g(stp);
	cout << "after g(stp), *stp.p: " << *stp.p << " ,stp.p: " << stp.p << " ,&stp.p: " << &stp.p << endl;

}
