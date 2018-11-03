//这个文件的目的：测试一个二叉树中，如果要删除的结点是根结点，那么改变根结点指向时要不要free原来根节点
//结论：可以free原本根节点T，就算T是间接指向分配出来的内存空间，不影响，只要根节点T重新指向新的根节点即可

#include <stdio.h>
#include <stdlib.h>

typedef int KeyType;
typedef struct BSTNode{  //二叉查找树结点
	KeyType key;      //关键字(键值)
	struct BSTNode *lchild;
	struct BSTNode *rchild;
	struct BSTNode *parent;
}BSTNode, *BSTree;

void fun(BSTree x)
{
	free(x);
	x = NULL;
}

int main()
{
	BSTree T = NULL;

	BSTree s = (BSTree)malloc(sizeof(BSTNode));
	s->key = 1;
	s->lchild = s->rchild = s->parent = NULL;
	T = s;

//以下是本文件测试部分
	BSTree s2 = (BSTree)malloc(sizeof(BSTNode));
	s2->key = 32;
	s2->lchild = s2->rchild = NULL;
	s2->parent = s;
	s->lchild = s2;

	printf("s->key:%d, T->key:%d, s2->key:%dT->lchild->key:%d, T->lchild->parent->key:%d\n",s->key, T->key, s2->key, T->lchild->key, T->lchild->parent->key);

	BSTree tmp = T->lchild;
	free(T);
	T = tmp;
	T->parent = NULL;
	printf("\nAfter free T, T->key:%d, s->key:%d\n", T->key, s->key);
	if(s2->parent == NULL)
		printf("\ns2->parent == NULL\n");

//以下测试调用函数free指针是否可行
/*	printf("s->key:%d, T->key:%d\n", s->key, T->key);
//情况1
	fun(T);
	if(T == NULL)
		printf("yes\n");
	else
	{
		printf("情况1：After fun, T->key:%d\n", T->key);
	}
//情况2
/*	fun(s);
	if(s == NULL)
		printf("yes!!\n");
	else
	{
		printf("情况2：After fun, s->key:%d\n", s->key);
	}*/
	


}
