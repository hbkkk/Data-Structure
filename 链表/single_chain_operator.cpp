#include <iostream>
using namespace std;

struct listnode{
	int data;
	struct listnode* next;
};

listnode* init()
{
	cout << "Init chain from end, enter num(except -1):\n";
	listnode* head = new listnode;
	head->next = NULL;
	listnode* p = head;
	int num;
	cin >> num;
	while(num != -1)
	{
		listnode* temp = new listnode;
		temp->data = num;
		temp->next = p->next;
		p->next = temp;
		cin >> num;
	}
	
	cout << "create chain done\n";
	return head;	
}

listnode* init_reverse()
{
	cout << "Init chain from head, enter num(except -1):\n";
	listnode* head = new listnode;
	head->next = NULL;
	listnode* p = head;
	int num;
	cin >> num;
	while(num != -1)
	{
		listnode* temp = new listnode;
		temp->data = num;
		temp->next = p->next;
		p->next = temp;
		p = p->next;
		cin >> num;
	}
	cout << "create chain done\n";
	return head;
}

void print(listnode* head)
{
	listnode* p = head->next;
	while(p)
	{
		cout << p->data << "  ";
		p = p->next;
	}
	cout << endl;
}

int find(listnode* p1, const int& e)  //找与e同值的节点
{
	listnode* temp = p1->next;
	while(temp)
	{
		if(temp->data == e)
		{
			cout << "find:" << e << endl;
			return 0;
		}
		else
		{
			temp = temp->next;
		}
	}
	cout << "no " << e << endl;

	return -1;
}


int delete_node(listnode* p1, const int& n)
{
	listnode* temp = p1->next;
	int j = 1;
	while(temp && j < n-1)
	{
		temp = temp->next;
		++j;
	}
	if(!temp) return -1;
	listnode* q = temp->next;
	temp->next = q->next;
	delete q;

	return 0;	
}

int insert(listnode* p1, const int& n, const int& num)
{
	listnode* temp = p1;  //不能是p1->next，这样的话如果要在第一个位置插节点就会失败，永远插在第二个节点上。
	int j = 1;
	while(temp && j < n)
	{
		temp = temp->next;
		++j;
	}
	if(!temp) return -1;
	listnode* q = new listnode;
	q->data = num;
	q->next = temp->next;
	temp->next = q;

	return 0;
}


listnode* mergexunhuan(listnode* head1, listnode* head2)
{
	listnode* head = new listnode;
	head->next = NULL;
	listnode* temp = head;
	
	listnode* p1 = head1->next;
	listnode* p2 = head2->next;
	while(p1 && p2)
	{
		if(p1->data < p2->data)
		{
			temp->next = p1;
			p1 = p1->next;
			temp = temp->next;
		}
		else if(p1->data > p2->data)
		{
			temp->next = p2;
			p2 = p2->next;
			temp = temp->next;
		}
		else
		{
			temp->next = p2;
			p1 = p1->next;	
			p2 = p2->next;
			temp = temp->next;
		}
	}
	temp->next = p1 ? p1 : p2;

	return head;
}


listnode* mergedigui(listnode* head1, listnode* head2)
{
	if(head1 == NULL)
		return head2;
	if(head2 == NULL)
		return head1;
	listnode* head = NULL;
	
	if(head1->data > head2->data)
	{
		head = head2;
		head->next = mergedigui(head1, head2->next);
	}
	else
	{
		head = head1;
		head->next = mergedigui(head1->next, head2);
	}
	return head;
}


int main()
{
//	listnode* head1 = init();
	listnode* head1 = init_reverse();
	listnode* head2 = init_reverse();

	cout << "head1: "; print(head1);
	cout << "head2: "; print(head2);

	const int a = 888;

	int iRet = find(head2, a);
//	cout << "iRet: " << iRet << endl;

//	delete_node(head1, 3);
//	print(head1);

//	insert(head2, 4, 987654);
//	print(head2);

//	listnode* head = mergexunhuan(head1, head2);
	listnode* head = mergedigui(head1, head2);
	print(head->next);

	delete head,head1,head2;
	return 0;
}







