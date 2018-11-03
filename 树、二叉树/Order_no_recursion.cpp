/****************************非递归遍历二叉树****************************/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stack>

using namespace std;

typedef char ElemType;

typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild;
	struct BiTNode *rchild;
}BiTNode, *BiTree;

void operater1(ElemType ch);

void PreOrder(BiTree T)  //非递归前序遍历二叉树
{
	stack<BiTree> stack;
	BiTree p = T;

	while(NULL!=p || !stack.empty())
	{
		if(NULL != p)
		{
			stack.push(p);
			operater1(p->data);
			p = p->lchild;
		}
		else
		{
			p = stack.top();
			stack.pop();
			p = p->rchild;
		}
	}
}

void InOrder(BiTree T)  //非递归中序遍历二叉树
{
	stack<BiTree> stack;
	BiTree p = T;
	
	while(NULL!=p || !stack.empty())
	{
		if(NULL != p)
		{
			stack.push(p);
			p = p->lchild;    //先一直让左子树进栈，直到叶子结点为止
		}
		else
		{
			p = stack.top();  //先保存栈顶元素地址，等会儿会被出栈
			operater1(p->data);  //打印栈顶元素，一开始是左子树元素
			stack.pop();       //栈顶元素即遍历到后(打印后)出栈
			p = p->rchild;
		}
	}
}

void CreateTree(BiTree *T)
{
	ElemType ch;
	scanf("%c", &ch);
//	fflush(stdin);
	getchar();
	if(ch == '#')
	{
		*T = NULL;
	}
	else
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		if(NULL == *T)
		{
			printf("malloc error\n");
			exit(1);
		}
		(*T)->data = ch;
		CreateTree(&(*T)->lchild);
		cout << "first out\n";
		CreateTree(&(*T)->rchild);
		cout << "second out\n";
	}
}

void operater1(ElemType ch)
{
	printf("%c ", ch);
}

int main()
{
	BiTree T = NULL;
	CreateTree(&T);
	printf("\nafter PreOrder:\n");
	PreOrder(T);
	cout << endl;

	printf("\nafter InOrder:\n");
	InOrder(T);
	cout << endl;
	
	return 0;
}













