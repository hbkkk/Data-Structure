#include <iostream>
#include <stdio.h>
using namespace std;

struct listnode{
	int data;
	struct listnode* next;
};

void init1(listnode* head)
{

	listnode* p = new listnode;
	p->data = 111;
	p->next = NULL;

	if(NULL == head) 
	{
		head = p;  //********注： 一级指针为形参是，函数里不能改变传进来的指针值！！！！！！！！
	}
	else                         //------------------------注！！！！---------------------------
	{			     //如果传进来的参数不是空指针，那么继续下面两行的操作，就在传进来的节点后新增一个节点
		p->next = head->next;
		head->next = p;
	}
}

void init2(listnode** head)
{
	listnode* p = new listnode;
	p->data = 111;
	p->next = NULL;
	if(NULL == *head) 
	{	
		*head = p;
	}
	else
	{
		p->next = (*head)->next;
		(*head)->next = p;
	}
}

void init3(listnode** head)
{
	listnode* p = new listnode;
	p->data = 111;
	p->next = NULL;
	if(NULL == *head) 
	{	
		*head = p;
	}
	else
	{
		*head = p;
	}
}

int main()
{
	listnode* head = NULL;
	init1(head);
	if(NULL != head)
	{
		cout << "after init1, head->data:" << head->data << endl;
	}
	else
		cout << "head is NULL\n\n";

	init2(&head);
	cout << "after init2, head->data:" << head->data << endl;


	listnode* head1 = new listnode;
	init1(head1);
	if(NULL != head1)
	{
		cout << "after init1, head1->data:" << head1->next->data << endl;    
	}
	else
		cout << "head1 is NULL\n\n";

	init2(&head1);
	cout << "after init2, head1->data:" << head1->next->data << endl;

	init3(&head1);
	cout << "after init3, head1->data:" << head1->data << endl;

}













