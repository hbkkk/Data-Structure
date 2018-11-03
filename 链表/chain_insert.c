#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LNode{
	int num;
	struct LNode* next;
}LNode, *LinkList;

static LinkList stpHead;
static LinkList stpNow;

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

	LinkList list = stpHead->next;
	while(NULL != list)
	{
		printf("%d ", list->num);
		list = list->next;
	}

	printf("\nWhere and what node want to insert:");
	int n1,num1;
	int j = 1;
	scanf("%d %d", &n1, &num1);

	LinkList p = stpHead;    //找对应的前一个节点!!!
	while(p && j < n1)
	{
		p = p->next;
		++j;
	}
	printf("p's num:%d\n", p->num);
	LinkList p1 = (LinkList)malloc(sizeof(LNode));
	p1->num = num1;
	p1->next = p->next;
	p->next = p1;

	LinkList p2 = stpHead->next;
	while(p2)
	{
		printf("%d ", p2->num);
		p2 = p2->next;
	}
	printf("\n");
	
	return 0;
}













