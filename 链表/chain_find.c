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
	printf("\nenter which node want to find:");
	int n1;
	scanf("%d", &n1);
	int j = 1;
	LinkList p = stpHead->next;    //！！！！找对应节点
	while(p && j < n1)
	{
		p = p->next;
		++j;
	}
	if(p)
		printf("find:%d\n", p->num);
	
	return 0;
}
