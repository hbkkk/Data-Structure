#include <iostream>
using namespace std;

struct listnode{
	struct listnode* prior;
	struct listnode* next;
	int data;
};

listnode* init()
{
	listnode* head = new listnode;
	head->prior = NULL;
	head->next = NULL;
	head->data = 0;
	listnode* p = head;
	
	int num;
	cin >> num;
	while(num != 0)
	{
		listnode* temp = new listnode;
		temp->data = num;
		temp->next = NULL;
		temp->prior = p;
		p->next = temp;
		p = p->next;
		cin >> num;
	}
	return head;
}

void print(listnode* head)
{
	listnode* p = head->next;
	while(p)
	{
		cout << p->data << " ";
		p = p->next;	
	}	
	cout << endl;
}

int getlength(listnode* head)
{
	if(!head) {cout << "NULL head\n"; return -1;}
	listnode* p = head;
	int i = 0;
	while(p)
	{
		p = p->next;
		++i;
	}
	return i;
}

void delete_chain(listnode* head, int pos)
{
	if(!head) {cout << "In delete_chain, wrong head!\n";}
	if(pos < getlength(head) && pos > 0)
	{
		listnode* p = head;
		int j = 1;
		while(p && j < pos)
		{
			p = p->next;
			++j;
		}
		if(!p || j > pos) {cout << "wrong11\n";}

		listnode* q = p->next;

		if(NULL == q->next && pos == 1)
		{
			p->next = NULL;
			delete head->next;
		}
		else if(NULL == q->next && pos >1)
		{
			p->next = NULL;
			delete p->next;
		}
		else
		{
			p->next = q->next;
			q->next->prior = q;
			delete p->next;
		}
	}
	else
		cout << "In delete_chain, wrong pos!\n";
}

void insert(listnode* head, int pos, int num)
{
	if(pos > 0 || pos <= getlength(head))
	{
		listnode* p = head;
		int j = 1;

		while(p && j < pos)
		{
			p = p->next;
			++j;
		}
		listnode* p1 = p->next;
	
		listnode* q = new listnode;
		q->data = num;

		if(NULL == p1 && pos == 1)  //空链表的情况
		{
			q->next = NULL;
			q->prior = p;
			p->next = q;
		}
		else if(NULL == p->next && pos > 1)  //插入的节点是最后一个的情况
		{
			q->next = NULL;
			q->prior = p;
			p->next = q;
		}
		else
		{
			q->next = p1;
			q->prior = p;
			p1->prior = q;
			p->next = q;
		}
		
	}
	else
		cout << "wrong position!\n";
}

int main()
{
	int pos;
	int num;
//	listnode* head = init();
	listnode* head = NULL;
	head = init();
	int n = getlength(head);
	cout << "length:" << n << endl;
	print(head);
	cout << "which node want to delete(if don't delete,enter 0):";
	cin >> pos;
	if(pos != 0)
	{		
		delete_chain(head, pos);
	}
	print(head);
/*	listnode* p = head->next->next->next;
	cout << "p = head->next->next->next, P data: " << p->data << endl;	
	
	listnode* q = p->prior;
	cout << "q = p->prior, q data:" << q->data << endl;  */
	
	cout << "where do you want to insert a node:";
	cin >> pos;
	if(pos > 0 && pos <= getlength(head))
	{
		cout << "enter the num:";
		cin >> num;
		insert(head, pos, num);
		print(head);
	}
	else
		cout << "wrong position! Please enter pos between 1~" 
		<< getlength(head) << endl;


//	destroy(head);
}
