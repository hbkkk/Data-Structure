#include <iostream>
#include <stdlib.h>
using namespace std;

const int MAXSIZE = 4;

typedef int QElemType;

typedef struct{
	QElemType *base;
	int front;
	int rear;
}SqQueue;

int InitQueue(SqQueue& Q)
{
	Q.base = (QElemType*)malloc(MAXSIZE*sizeof(QElemType));
	if(!Q.base) {cout << "malloc failed\n"; return -1;}
	Q.front = Q.rear = 0;
	
	return 0;
}

int QueueLength(const SqQueue& Q)
{
	return (Q.rear-Q.front+MAXSIZE) % MAXSIZE;
}

bool IsFull(const SqQueue& Q)
{
	return (Q.rear + 1) % MAXSIZE == Q.front;
}

bool IsEmpty(const SqQueue& Q)
{
	return Q.front == Q.rear;
}

int EnQueue(SqQueue& Q, const QElemType& e)
{
	if(IsFull(Q)) {cout << "Queue is Full\n"; return -1;}
//	Q.base[Q.rear++] = e;  //不能这么写！因为Q.rear++可能会越界，数组内元素个数给定的
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXSIZE;
	return 0;
}

int DeQueue(SqQueue& Q, QElemType& e)
{
	if(IsEmpty(Q)) 
	{
		cout << "Queue is empty\n";
		return -1;
	}
	else
	{
		e = Q.base[Q.front];
//		++Q.front; //不能这么写！会越界!!!
		Q.front = (Q.front + 1) % MAXSIZE;
	}

	return 0;
}

void PrintQueue(const SqQueue& Q)
{
	if(!IsEmpty(Q))
	{
		int pos = Q.front;
		while(pos != Q.rear)
		{			
			cout << Q.base[pos] << " ";
			pos = (pos + 1) % MAXSIZE;
		}
	}
	cout << endl;
}

int DestroyQueue(SqQueue& Q)
{
	free(Q.base);
	Q.base = NULL;
	Q.front = Q.rear = 0;
	return 0;
}

int ClearQueue(SqQueue& Q)
{
	Q.front = Q.rear = 0;
	return 0;
}

int main()
{
	int num = 0;
	int data = 0;
	SqQueue queue;
	InitQueue(queue);
	cout << "how many: ";
	cin >> num;
	for(int i = 0; i < num; ++i)
	{
		cin >> data;
		EnQueue(queue, data);
	}
	cout << "Length: " << QueueLength(queue) << endl;
	PrintQueue(queue);

	data = -1;
	DeQueue(queue, data);
	cout << "deleted data: " << data << endl;
	cout << "After delete, length: " << QueueLength(queue) << endl;
	PrintQueue(queue);

	DestroyQueue(queue);

	return 0;
}











