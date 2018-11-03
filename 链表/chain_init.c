#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LNode{
	int num;
	struct LNode* next;
}LNode, *LinkList;

static LinkList stpHead;
//stpHead->next = NULL;
static LinkList stpNow;
/*
//头插法！！！每次插入的节点都在上一个节点之前
int main()
{
	stpHead = (LinkList)malloc(sizeof(LNode));
	stpHead->next = NULL;
	printf("how many nodes?:");
	int n;
	scanf("%d", &n);
	for(int i = n; i > 0; --i)
	{
		stpNow = (LinkList)malloc(sizeof(LNode));
		scanf("%d", &stpNow->num);
		stpNow->next = stpHead->next;
		stpHead->next = stpNow;
	}

	LinkList list = stpHead;
	while(NULL != list)
	{
		printf("%d ", list->num);
		list = list->next;
	}
	printf("\n");
}*/


//尾插法------------每次插入的节点都在上一个节点之后
int main()
{
	int data,n;
	int i = 0;
	scanf("%d", &n);	
	LinkList stpBegin = (LinkList)malloc(sizeof(LNode));
	stpBegin->next = NULL;
	LinkList stptmp = stpBegin;   //*********************用于尾插法**********************

	while(i++ < n)
	{
		scanf("%d", &data);
		LinkList temp = (LinkList)malloc(sizeof(LNode));

		temp->num = data;
		temp->next = stptmp->next;
		stptmp->next = temp;
		stptmp = temp;               //多了这句话！就变成尾插法了，没这句话就还是头插法！！！！！！！！！！
	}

	LinkList p = stpBegin->next;
	while(p)
	{
		printf("%d ", p->num);
		p = p->next;
	}
	printf("\n");

	return 0;
}








