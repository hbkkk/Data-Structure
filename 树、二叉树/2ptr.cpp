#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
typedef struct{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode, *HuffmanTree;

typedef char ** HuffmanCode;  //编码表

void fun(HuffmanTree *ht)
{
	*ht = (HuffmanTree)malloc(5*sizeof(HTNode));
	for(int j = 0; j < 5; ++j)
	{
//		(*ht)[j].weight = j*3;

//		(*ht)[j]->weight = j*3; //不能这么写！！！invalid type argument of ‘->’ (have ‘struct <anonymous>’)(*ht)[j]->weight = j*3;

		(*ht + j)->weight = j*3;
		printf("uu: %d\n", (*ht+j)->weight);
	}
}

/*void Create2Ptr(HuffmanCode *hc)
{
	char *a[] = {"heel", "sasa", "wqed", "ufcs", "d12"};
	*hc = (char**)malloc(5*sizeof(char*));
		printf("22\n");
	for(int i = 0; i < 5; ++i)
	{
		(**hc)[i] = (char*)malloc(5*sizeof(char));
		printf("22\n");
		strcpy(**hc+i, a+i);
	}
}*/
typedef char ** HuffmanCode;  //编码表
void Create2Ptr(HuffmanCode *hc)  //三级指针
{
	char *a[] = {"heel", "sasa", "wqed", "ufcs", "d12"};
	*hc = (char**)malloc(5*sizeof(char*));

	for(int i = 0; i < 5; ++i)
	{
//		printf("123\n");
		(*hc)[i] = (char*)malloc(5*sizeof(char));
//		printf("22\n");
//		strcpy((*hc)[i], a+i);   //这样写不对！！！！
		strcpy((*hc)[i], a[i]);
	}
}
void Create2Ptr_yinyong(HuffmanCode &hc)  //二级指针引用
{
	char *a[] = {"heel", "sasa", "wqed", "ufcs", "d12"};
	hc = (char**)malloc(5*sizeof(char*));

	for(int i = 0; i < 5; ++i)
	{
//		printf("123\n");
		hc[i] = (char*)malloc(5*sizeof(char));
//		printf("22\n");
//		strcpy((*hc)[i], a+i);   //这样写不对！！！！
		strcpy(hc[i], a[i]);
	}
}

int main()
{
/*	HuffmanTree tree;
	fun(&tree);
	for(int i = 0; i<5; ++i)
	{
//		printf("%d ", (tree+i)->weight);
		printf("%d ", tree[i].weight);
//		printf("%d ", tree->weight);//这里输出的值都为0，但在fun函数里却不是0。。。  !!!!!!!!我真是个傻逼。。。这里应该是(tree+i)->weight
	}
	printf("\n");*/

	HuffmanCode HC = NULL;
//	Create2Ptr(&HC); //函数参数为三级指针！
	Create2Ptr_yinyong(HC);  //函数参数为二级指针的引用
	printf("after create2ptr\n");
	if(HC == NULL) printf("妈的！还他妈是没用\n");
	for(int i = 0; i < 5; ++i)
	{
		printf("%s ", HC[i]);
	}
	printf("\n");

	char b[100];
	scanf("%s", b);
	printf("b: %s\n", b);
}


/*void fun(int **i)
{
	*i = (int *)malloc(5*sizeof(int));
	for(int j = 0; j < 5; ++j)
	{
		(*i)[j] = j*3;    //这种写法可以
		*(*i + j) = j*3;  //这种写法也可以！
	
//		*i[j] = j*3; //这种写法不行！！！
	}
}
int main()
{
	int *a = NULL;

	fun(&a);
	
	for(int i = 0; i < 5; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}*/






