/****************************************************静态树表查找算法****************************************************/
//
//
//
//
//

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

using std::vector;
using std::endl;
using std::cout;
using std::cin;

#define DEBUG

#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)>(b))
#define MAX_SIZE 50

typedef char KeyType; 

typedef struct ElemType  //数据元素类型
{
	KeyType key;  //关键字类型
	int weight;   //权重
}ElemType;

typedef struct{  //静态查找表
	ElemType *elem;  //数据元素存储空间基址,0号单元留空
	int length;      //表长度
}SSTable;

typedef struct BiTNode  //二叉树中叶子结点
{
	ElemType data;
	BiTNode *lchild;
	BiTNode *rchild;
}BiTNode, *BiTree;


//******************************************构造次优查找树******************************************
BiTree SecondOptimal(ElemType R[], vector<int> sw, const int &low, const int &high)//由有序表R[low,...,high]及累计权值表sw(其中sw[0]==0)递归构造次优查找树T
{
	int i = low;
	int min = abs(sw[high] - sw[low]);
	int dw = sw[high] + sw[low-1]; //定值

	for(int j = low+1; j <= high; ++j) //找最小值△P
	{
		if(abs(dw-sw[j]-sw[j-1]) < min)   //△Pi = |(SWh+SWl-1)-SWi-SWi-1|
		{
			i = j;
			min = abs(dw-sw[j]-sw[j-1]);
		}
	}

	cout << "[i]=" << i << " ,low=" << low << " ,high=" << high << endl;

	BiTree T = new BiTNode;  //生成结点
	T->data = R[i];
	T->lchild = NULL;
	T->rchild = NULL;
	if(i == low)
	{
		T->lchild = NULL;
	}
	else
	{
		T->lchild = SecondOptimal(R, sw, low, i-1);
	}

	if(i == high)
	{
		T->rchild = NULL;
	}
	else
	{
		T->rchild = SecondOptimal(R, sw, i+1, high);
	}
	return T;
}

void FindSW(const SSTable &ST, vector<int> &sw)  //按照由有序表ST中各数据元素的weight域求累计权值表sw       SWi = Wj(从j=l累加到j=i)
{
	sw[0] = 0;

	for(int i = 1; i <= ST.length; ++i)
	{
//		sw.push_back(sw[i]+ST.elem[i+1].weight);
		sw[i] = sw[i-1] + ST.elem[i].weight;
	}

	cout << "SW:  ";
	for(int i = 1; i <= ST.length; ++i)
	{
		cout << "[" << i << "]=" << sw[i] << " ";
	}
	cout << endl;
}

BiTree CreateSOSTree(SSTable &ST)  //由有序表ST构造一棵次优查找树. ST的数据元素含有权域weight
{
	if(ST.length == 0)
		return NULL;
	else
	{
		vector<int> sw(ST.length+1, 0);
		FindSW(ST, sw);  //按照由有序表ST中各数据元素的weight域求累计权值表sw
		return SecondOptimal(ST.elem, sw, 1, ST.length); //由有序表ST.elem[low,...,high]及累计权值表sw(其中sw[0]==0)递归构造次优查找树并返回
	}
}

void print(const SSTable &ST)
{
	cout << "data:\n";
	for(int i = 1; i <= ST.length; ++i)
	{
		cout << "[" << i << "]=" << ST.elem[i].key << "," << ST.elem[i].weight << " ";
	}
	cout << endl;
}

int PreOrderTraverse(BiTree T);
int InOrderTraverse(BiTree T);
int PostOrderTraverse(BiTree T);


int PreOrderTraverse(BiTree T)
{
	
	if(T)
	{
		cout << T->data.key << "," << T->data.weight << " ";
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
	return 0;
}

int InOrderTraverse(BiTree T)
{

	if(T)
	{
		InOrderTraverse(T->lchild);
		cout << T->data.key << "," << T->data.weight << " ";
		InOrderTraverse(T->rchild);
	}
	return 0;
}

int PostOrderTraverse(BiTree T)
{

	if(T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		cout << T->data.key << "," << T->data.weight << " ";		
	}
	return 0;
}

int main()
{
	SSTable ST;
	int i = 1;
#ifdef DEBUG
	ElemType arr[MAX_SIZE] = {{'0', 0}, {'A', 1}, {'B', 1}, {'C', 2}, {'D',5}, {'E', 3}, {'F', 4}, {'G', 4}, {'H', 3}, {'I', 5}};
	i = 10;
#else
	ElemType arr[MAX_SIZE];
	KeyType tmp;
	int w;
	cout << "输入关键字和权值:\n";
	while(1)
	{
		cin >> tmp;
		cin >> w;
		if(tmp == '0' && w == 0)
			break;
		else
		{
			arr[i].key = tmp;
			arr[i].weight = w;
			++i;
		}
	}
#endif

	ST.elem = arr;
	ST.length = i-1;

#ifdef DEBUG
	print(ST);
#endif

	BiTree T = CreateSOSTree(ST);

	cout << "前序遍历:";
	PreOrderTraverse(T);
	cout << endl;

	cout << "中序遍历:";
	InOrderTraverse(T);
	cout << endl;

	cout << "后序遍历:";
	PostOrderTraverse(T);
	cout << endl;
}






















