#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;

const int STACK_INIT_SIZE = 20;  //先为栈分配一个初始容量，若不够了再加
const int STACKINCREMENT = 5;

typedef char ElemType;

typedef struct{  //栈的结构体，先进后出
	ElemType* base; //栈底指针，在顺序栈中始终指向栈底的位置
	ElemType* top;  //栈顶指针，初值指向栈底，即top=base可作为栈空的标志，每当插入新的栈顶元素，top增1，删除栈顶元素，top减1
	int stacksize;  //栈的当前可用的最大容量
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
	}
}

