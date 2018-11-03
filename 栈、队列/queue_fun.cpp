#include <iostream>
#include <stdlib.h>
using namespace std;

typedef int QElemType;

typedef struct QNode{
	QElemType data;
	struct QNode* next;
}QNode, *QueuePtr;

typedef struct{
	QueuePtr front; //对头指针
	QueuePtr rear;  //对尾指针
}LinkQueue;

int InitQueue(LinkQueue& Q)
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));

	if(!Q.front) {cout << "malloc failed\n"; return -1;}
	Q.front->next = NULL;

	return 0;
}

int DestroyQueue(LinkQueue& Q)
{
	if(!Q.front) return 0;
	
	QueuePtr q = Q.front;
	while(q)
	{
		QueuePtr q1 = q->next;
		free(q);
		q = q1;
	}

	return 0;
}

int DestroyQueue1(LinkQueue& Q)  //用这个好！因为最后会使得Q.front和Q.rear都变为NULL！！！！***********8888
{
	while(Q.front)
	{
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
}

int ClearQueue(LinkQueue& Q)
{
	if(!Q.front) {cout << "Q.front is NULL\n"; return 0;}

	QueuePtr q = Q.front->next;

	while(q)   //若能进循环，就说明队列中是至少有一个元素！
	{
		QueuePtr q1 = q->next;
		free(q);
		q = q1;
	}
	Q.front->next = NULL;
	return 0;
}

bool IsEmpty(const LinkQueue& Q)
{
	return Q.front == Q.rear;
}

int QueueLength(const LinkQueue& Q)
{
	int i = 0;
	if(!IsEmpty(Q))
	{
		QueuePtr q = Q.front->next;
		while(q)
		{
			++i;
			q = q->next;
		}
		return i;
	}
	else
	{
		cout << "Empty queue\n";
		return 0;
	}
}

int GetHead(const LinkQueue& Q, QElemType& e)
{
	if(IsEmpty(Q))
	{
		e = -1;
		return -1;
	}
	else
	{
		e = Q.front->next->data;
		return 0;
	}
}

void PrintQueue(const LinkQueue& Q)
{
	QueuePtr q = Q.front->next;
	cout << "Queue: ";
	while(q)
	{
		cout << q->data << " ";
		q = q->next;
	}
	cout << endl;
}

int EnQueue(LinkQueue& Q, const QElemType& e)  //插入元素e为Q的新的对尾元素
{
	QueuePtr node = (QueuePtr)malloc(sizeof(QNode));
	if(!node) {cout << "malloc failed\n"; return -1;}  //注意每次malloc后要检查是否分配成功
	node->data = e;
	node->next = NULL;
	Q.rear->next = node;  //这句话记得加上去！ 但是为什么呐？？？？   因为一开始rear和front一样都指向头节点，所以当新增一个节点1时，
	Q.rear = node;						 //Q.rear->next=node这句话就是让头结点指向新增节点1，若又新增一个
	return 0;					         //节点2，那么这句话就相当于让节点1指向节点2！因为有下一句Q.rear=node，
}								 //所以rear始终指向最新增加的那个节点！！！！

int DeQueue(LinkQueue& Q, QElemType& e)  //若队列不空，则删除Q的队头元素，用e返回其值
{
	if(IsEmpty(Q)) {cout << "Empty queue\n"; return -1;}
	QueuePtr q = Q.front->next;
	e = q->data;
	if(!q->next)   //这种情况是：删除的节点是队列中的最后一个元素，如果直接删除，那么队列尾指针也丢失了，因此需对队尾指针重新赋值(指向头指针！)
	{
		Q.front->next = NULL;
		Q.rear = Q.front;
	}
	else
	{
		Q.front->next = q->next;
	}
//	free(Q.front->next);   //这句话有问题！会导致删除对头元素后，使得对头元素后面那个元素的data值变为0.......
	free(q);
//	if(Q.front->next)
//		cout << "In Dequeue------, first data: " << Q.front->next->data << endl;
	return 0;
}

int main()
{
	LinkQueue queue;
	InitQueue(queue);
	int n;
	int data;
	cout << "how many: ";
	cin >> n;
	for(int i = 0; i < n; ++i)
	{
		cout << "enter data:";
		cin >> data;
		EnQueue(queue, data);
	}
	cout << "Queue's length: " << QueueLength(queue) << endl;
	PrintQueue(queue);
	DeQueue(queue, data);
	cout << "deleted data:" << data << endl;
	cout << "Queue's length: " << QueueLength(queue) << endl;
	PrintQueue(queue);

	data = 0;
	GetHead(queue, data);
	cout << "Head data: " << data << endl;

	cout << "do you want to destroy queue? 1 equal yes,0 equal no: ";
	int iRet = -1;
	cin >> iRet;
	if(iRet)
	{
		DestroyQueue1(queue);
		if(NULL == queue.front && NULL == queue.rear)
			cout << "queue's front and rear are NULL\n";
		else
			cout << "queue's front and rear are not NULL\n";
	}
	
	iRet = -1;
	cout << "do you want to clear queue? 1 equal yes,0 equal no: ";
	cin >> iRet;
	if(iRet)
	{
		ClearQueue(queue);
		if(queue.front && queue.rear && queue.front == queue.rear)
			cout << "queue's front and rear are not NULL, queue's front = rear\n";
	}

	return 0;
}












