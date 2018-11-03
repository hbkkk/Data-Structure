#include <iostream>
#include <stdio.h>
using namespace std;

int a = 10;
int b = 199;

void f(int* p)
{
	p = &b;
	printf("In f(), *p:%d, p:%d, &p:%d\n\n", *p, p, &p);
}

void g(int** p)
{
	*p = &b;
	printf("In g(), **p:%d, *p:%d, p:%d, &p:%d\n\n", **p, *p, p, &p);
}

void h(int* &p)
{
	p = &b;
}

int main()
{
	printf("&a:%d, &b:%d\n\n", &a, &b);

	int* q = &a;
	printf("*q:%d, q:%d, &q:%d\n", *q, q, &q);
	cout << endl << "*q:" << *q << " ,q:" << q << " ,&q:" << &q << endl << endl;
	f(q);
	printf("after f(q), *q:%d, q:%d, &q:%d\n\n", *q, q, &q);

//	g(&q);
//	printf("after g(q), *q:%d, q:%d, &q:%d\n\n", *q, q, &q);

	h(q);
	printf("after h(q), *q:%d, q:%d, &q:%d\n\n", *q, q, &q);
	
	return 0;
}
