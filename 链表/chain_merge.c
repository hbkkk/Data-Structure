#include <stdio.h>
#include <stdlib.h>

typedef struct LNode{
	int data;
	struct LNode* next;
}LNode,*LinkList;

static LinkList stptmp;
static LinkList stpnow;

int main()
{
	LinkList a = (LinkList)malloc(sizeof(LNode));
	a->next = NULL;
	for(int i = 2; i < 7; i++)
	{
		LinkList a1 = (LinkList)malloc(sizeof(LNode));
		a1->next = a->next;
		a1->data = i*3;
		a->next = a1;
	}

	LinkList b = (LinkList)malloc(sizeof(LNode));
	b->next = NULL;
	for(int i = 1; i < 8; i++)
	{
		LinkList b1 = (LinkList)malloc(sizeof(LNode));
		b1->next = b->next;
		b1->data = i*2;
		b->next = b1;
	}

	//打印两个待排序的链表
	stpnow = a->next;
	while(stpnow)
	{
		printf("%d ", stpnow->data);
		stpnow = stpnow->next;
	}
	printf("\n");

	stpnow = b->next;
	while(stpnow)
	{
		printf("%d ", stpnow->data);
		stpnow = stpnow->next;
	}
	printf("\n");

	LinkList c = (LinkList)malloc(sizeof(LNode));
	c->next = NULL;
	LinkList head = c;

	LinkList pa = a->next;
	LinkList pb = b->next;

	//---------------------------------循环实现合并---------------------------------
	while(pa && pb)
	{
		printf("pa data:%d, pb data:%d\n", pa->data, pb->data);
		if(pa->data > pb->data)
		{   
		//***************这里很绕 好好理解！！！！**********************

			head->next = pa;          //!!!!!!!!!!不能直接用c，应该再用一个指针指向链表头，然后在这个指针上操作，否则循环过后链表头c就不再指向链表头了！！！！！！！
			head = head->next; //这句话！！！！！！是让此时这个指针指向链表下一个节点，即：当head的next指向了pa，就是说下一个节点是pa，
					   //然后再让head也指向pa，这样为了下次修改head的next是直接修改让其指向pa这个节点之后那个！！！     类似打印每个节点数据后，要stpnow=stpnow->next
			pa = pa->next;
		}
		else if(pa->data < pb->data)
		{
			head->next = pb;
			head = head->next;
			pb = pb->next;
		}
		else
		{
			head->next = pa;
			head = head->next;
			pa = pa->next;
			pb = pb->next;
		}
	}

	head->next = pa ? pa : pb;

	stpnow = c->next;
	while(stpnow)
	{
		printf("%d ", stpnow->data);
		stpnow = stpnow->next;
	}
	printf("\n");

	return 0;
}




















