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
	for(int i = n; i > 0; --i)   //初始化链表
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
	printf("\nenter which node want to delete:");
	int n1;
	scanf("%d", &n1);
	int j = 1;
	LinkList p = stpHead;    //！！！！找对应的前一个节点
	while(p && j < n1)
	{
//		printf("***(%d\n", p->num);
		p = p->next;
		++j;
	}
	printf("p:%d\n", p->num);
	
	LinkList q = p->next;
	p->next = q->next;
	free(q);

	LinkList q1 = stpHead->next;
	printf("after delete: ");
	while(q1)
	{
		printf("%d ", q1->num);
		q1 = q1->next;
	}
	printf("\n");

	return 0;
}















