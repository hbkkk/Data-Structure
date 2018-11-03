#include <iostream>
#include <stdlib.h>
using namespace std;

const int STACK_INIT_SIZE = 20;
const int STACKINCREMENT = 5;

typedef int ElemType;

typedef struct{
	ElemType* base;
	ElemType* top;
	int stacksize;
}SqStack;

int InitStack(SqStack &S)
{
	S.base = (ElemType*)malloc(sizeof(SqStack));
	if(!S.base) {cout << "malloc failed\n"; return -1;}
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return 0;
}


int GetTop(SqStack S, int& e)
{
	if(S.base == S.top) {cout << "Empty stack\n"; return -1;}
	
	e = *(S.top-1);
	return 0;
}

int Push(SqStack &S, ElemType& e)
{
	if((S.top - S.base) >= S.stacksize)
	{
		S.base = (ElemType*)realloc(S.base, (S.stacksize + STACKINCREMENT)*sizeof(SqStack));
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return 0;
}

int Pop(SqStack& S, ElemType& e)
{
	if(S.base == S.top) {cout << "Empty stack\n"; return -1;}
	e = *--S.top;
	return 0;
}

int Pop(SqStack& S)
{
	if(S.base == S.top) {cout << "Empty stack\n"; return -1;}
	--S.top;
	return 0;
}

int StackEmpty(const SqStack& S)
{
	return S.top == S.base;
}

void conversion(SqStack& S)
{
	InitStack(S);
	int n;
	cout << "enter a hex num: ";
	cin >> n;
	while(n)
	{
		int i = n % 8;
		Push(S, i);
		n = n / 8;
	}
	if(StackEmpty(S)) {cout << "empty!\n";}
	cout << "length:" << (S.top - S.base) << endl;
	while(S.base != S.top)
	{
		int a = 0;
		GetTop(S, a);
		Pop(S);
		cout << a;
	}
	cout << endl;
}

int main()
{
	SqStack S;
	conversion(S);

	return 0;
}











