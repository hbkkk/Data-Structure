/****************************前序创建二叉树、递归遍历二叉树****************************/
//这个不全，可以看OrderTraverse_Create.c文件中的代码
//该文件主要目的：测试c++中的一级指针引用等价于c中的二级指针的效果


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

typedef char ElemType;

typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

void operater1(ElemType ch, int level);

void CreateTree(BiTree &T)   //用一级指针引用，代替了二级指针
{
	ElemType ch;
	printf("enter the node's data: ");
	cin >> ch;

	if(ch == '#')
	{
		T = NULL;  //将叶子结点的左、右子树指针设为NULL !!!
	}
	else
	{
		T = (BiTree)malloc(sizeof(BiTNode));
		if(NULL == T)
		{	
			cout << "malloc error\n";
			exit(1);
		}

		T->data = ch;
		CreateTree(T->lchild);
//		cout << "first out\n";
		CreateTree(T->rchild);
//		cout << "second out\n";
	}
	printf("end\n");
}


void PreOrderTraverse(BiTree T, int level)
{
	if(NULL == T)
		return;
	operater1(T->data, level);
	PreOrderTraverse(T->lchild, level+1);
	PreOrderTraverse(T->rchild, level+1);
}

void operater1(ElemType ch, int level)
{
	printf("Node: %c, level: %d\n", ch, level);
}

int main()
{
	int level = 1;
	BiTree bintree = NULL;
	CreateTree(bintree);
	cout << "\nPreOrderTraverse:\n";
	PreOrderTraverse(bintree, level);

	return 0;
}
















