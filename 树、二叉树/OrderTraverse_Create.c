/****************************前序创建二叉树、递归遍历二叉树****************************/

#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

void operater1(ElemType data, int level);

void CreateTree(BiTree *T) //先序创建树
{
	ElemType ch;
//	scanf("%c\n", &n);  //醉了！！！这里干嘛要加个\n。。。又不是输出printf！！！！！fuck！！！！！！！！！！！！
	scanf("%c", &ch);  //***********注！！！！：找到问题了！！！！
	        //输入A和第一个回车后，A和这个回车符都留在缓冲区中第一个scanf读取了A，
		//但是输入缓冲区里面还留有一个\n，第二个scanf读取这个 。解决办法如下↓↓↓↓↓↓
	getchar();  //或者用fflush(stdin); 

	if(ch == '#')
	{
		*T = NULL;
	}
	else
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		(*T)->data = ch;
		CreateTree(&(*T)->lchild);
//		printf("first out\n");
		CreateTree(&(*T)->rchild);
//		printf("second out\n");
	}
	printf("end\n");
}

//***************前序遍历***************
// 1) 访问根结点
// 2) 先序遍历左子树
// 3) 先序遍历右子树
void PreOrderTraverse(BiTree T, int level)
{
	if(NULL == T)
		return;
	operater1(T->data, level);
	PreOrderTraverse(T->lchild, level+1);
	PreOrderTraverse(T->rchild, level+1);
}

//***************中序遍历***************
// 1) 中序遍历左子树
// 2) 访问根结点
// 3) 中序遍历左子树
void InOrderTraverse(BiTree T, int level)
{
	if(NULL == T)
		return;
	InOrderTraverse(T->lchild, level+1);
	operater1(T->data, level);
	InOrderTraverse(T->rchild, level+1);
}

//***************后序遍历***************
// 1) 后序遍历左子树
// 2) 后序遍历左子树
// 3) 访问根结点
void PosOrderTraverse(BiTree T, int level)
{
	if(NULL == T)
		return;
	PosOrderTraverse(T->lchild, level+1);
	PosOrderTraverse(T->rchild, level+1);
	operater1(T->data, level);
}

void operater1(ElemType data, int level)
{
	printf("Node: %c, level: %d\n", data, level);
}

int main()
{
	int level = 1;
	BiTree bintree = NULL;
	CreateTree(&bintree);
	printf("前序遍历：\n");
	PreOrderTraverse(bintree, level);

	printf("\n中序遍历：\n");
	InOrderTraverse(bintree, level);

	printf("\n后序遍历：\n");
	PosOrderTraverse(bintree, level);

	return 0;
}
















