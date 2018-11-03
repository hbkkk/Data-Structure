/****************************层次遍历****************************/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <queue>

using namespace std;

typedef char ElemType;

typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild;
	struct BiTNode *rchild;
}BiTNode, *BiTree;

void operater1(ElemType ch);

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

void levelorder(BiTree T)
{
	queue<BiTree> queue;
	BiTree p = T;
	queue.push(p);
	
	while(!queue.empty())
	{
		p = queue.front();
		operater1(p->data);
		queue.pop();
		if(NULL != p->lchild)
		{
			queue.push(p->lchild);
		}
		if(NULL != p->rchild)
		{
			queue.push(p->rchild);
		}
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
	printf("\nafter levelorder:\n");
	levelorder(T);
	cout << endl;
	
	return 0;
}













