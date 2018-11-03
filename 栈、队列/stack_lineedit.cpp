#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;

const int STACK_INIT_SIZE = 20;
const int STACKINCREMENT = 5;

typedef char ElemType;

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

int StackLength(const SqStack& S)
{
	return (S.top - S.base);
}

int StackEmpty(const SqStack& S)
{
	return S.top == S.base;
}

void StackClear(SqStack& S)
{
	if(S.base != S.top)
	{
		S.top = S.base;
		S.stacksize = 0;
	}
}

void StackDestroy(SqStack& S)
{
	if(S.base != S.top)
	{
		S.top = S.base;
		free(S.base);
		S.top = NULL;
		S.base = NULL;
	}
	else
	{
		free(S.base);
		S.base = NULL;
		S.top = NULL;
	}
}

void LineEdit(SqStack& S)
{
	ElemType *p,ch,c;
	InitStack(S);
	ch = getchar();
	cout << "ch:" << ch << endl;
	while(ch != EOF)
	{
		while(ch != EOF && ch != '\n')
		{
			switch(ch)
			{
				case '#': Pop(S); break;
				case '@': StackClear(S); break;
				default: Push(S, ch); break;
			}
			ch = getchar();
			cout << "1ch:" << ch << endl;
		}
		p = S.base;
		while(p != S.top)
		{
			cout << *p;
			++p;
		}
		cout << endl;
		StackClear(S);
		if(ch != EOF)		
			ch = getchar();
			cout << "2ch:" << ch << endl;
	}
}

int main()
{
	cout << "EOF:" << EOF << endl;
	SqStack S;
	LineEdit(S);

	return 0;
}









