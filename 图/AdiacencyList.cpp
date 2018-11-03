// --------------邻接表-------------
//    优点：
//    对于，稀疏图，邻接表比邻接矩阵更节约空间。
//    缺点：
//    不容易判断两个顶点是有关系（边），顶点的出度容易，但是求入度需要遍历整个邻接表。

//表结点结构:   adjvex nextarc info

//头结点结构:      data firstarc  在邻接表中，头结点是一个******顺序存储结构******，是一个数组，这样方便查询每个顶点

//*******************************主要还是链表的基本操作要会使用************************************

#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

const int MAX_VEX_NUM = 20;

typedef enum {DG, DN, UDG, UDN} GraphKind;

typedef string vextype; //顶点类型

typedef struct ArcNode{  //表结点
	int adjvex;   //表示的该边的另外一个顶点在顶点数组中的下标
	struct ArcNode *nextarc;   //指向的是下一条依附在该顶点的边的信息
	int info;
}ArcNode;

typedef struct VNode{  //头结点
	vextype data;
	ArcNode *firstarc;
}VNode, AdjList[MAX_VEX_NUM];  //这里的AdjList代表的就是最大的头结点数组

typedef struct ALGraph{   //图
	AdjList adjlist;  //图中每个结点的单链表,   注：这个adjlist是顺序存储的一个数组
	int vexnum;   //图中顶点的个数
	int arcnum;   //图中边或者弧的个数
	int kind;
}ALGraph;

static ArcNode *stpNow;  //用于创建每个结点单链表中的表结点


void CreateAdjList(ALGraph &G, int kind)
{
	int i,j,k;
	int weight;
	G.kind = kind;
	cout << "输入顶点个数:";
	cin >> G.vexnum;
	cout << "输入弧或边个数:";
	cin >> G.arcnum;

	cout << "输入每个顶点信息(V1,V2,V3...):";
	for(i = 0; i < G.vexnum; ++i)  //初始化图，并给图中每个顶点赋予信息
	{
		cin >> G.adjlist[i].data;
		G.adjlist[i].firstarc = NULL;
	}
	cout << "输入弧或边的两头顶点序号(若是有向的，则输入循序为:尾 头，例如1 2代表顶点1指向顶点2):";
	for(k = 0; k < G.arcnum; ++k)
	{
		cin >> i;
		cin >> j;

		stpNow = (ArcNode *)malloc(sizeof(ArcNode));
		stpNow->adjvex = j-1;
		stpNow->nextarc = G.adjlist[i-1].firstarc;   //头插法(逆序)，即把每次新增的那个表结点用对应头结点的firstarc指针去指向
		if(G.kind == DN || G.kind == UDN)
		{
			cout << "输入顶点" << i << "和顶点" << j << "之间的权值:";
			cin >> stpNow->info;
			weight = stpNow->info;
		}
		G.adjlist[i-1].firstarc = stpNow;       //头插法(逆序)

		if(G.kind == UDG || G.kind == UDN)  //如果是无向图或者无向网，还需添加一个，即含有n条弧的有向图、网在这个存储结构中需要n个表结点；
		{								   //而含有n条弧的无向图、网在这个存储结构中需要2n个表结点，所以需要以下这段代码
			stpNow = (ArcNode *)malloc(sizeof(ArcNode));
			stpNow->adjvex = i-1;
			stpNow->nextarc = G.adjlist[j-1].firstarc;
			if(G.kind == UDN)
			{
//				cout << "输入顶点" << j << "和顶点" << i << "之间的权值:";
//				cin >> stpNow->info;
				stpNow->info = weight;
			}
			G.adjlist[j-1].firstarc = stpNow;
		}
	}
}

void print(const ALGraph &G)
{
	int i;
	ArcNode *node;  //创建一个新的指针，指向每个头结点，然后一次打印每个链表的内容

	cout << "图的邻接表:\n";
	for(i = 0; i < G.vexnum; ++i)
	{
		node = G.adjlist[i].firstarc;
		cout << i << "-" << G.adjlist[i].data << ": ";
		if(G.kind == DN || G.kind == UDN)
		{
			while(NULL != node)
			{
				cout << node->adjvex << "(weight:" << node->info << ")  ";
				node = node->nextarc;
			}
		}
		else
		{
			while(NULL != node)
			{
				cout << node->adjvex << " ";
				node = node->nextarc;
			}
		}
		cout << endl;
	}
}

int clear(ALGraph &G)
{
	if(NULL == G.adjlist[0].firstarc) return 0;
	ArcNode *p = NULL;    //清空链表的方法！！！！
	ArcNode *q = NULL;
	

	for(int i = 0; i < G.vexnum; ++i)
	{
		p = G.adjlist[i].firstarc;
		while(p)  //链表清除，不是销毁
		{
			q = p->nextarc;
			free(p);
			p = q;
		}
		G.adjlist[i].firstarc = NULL;
	}

	return 0;
}

int main()
{
	ALGraph G;
	
	cout << "无向网:\n";
	CreateAdjList(G, UDN);
	print(G);
	clear(G);

	cout << "有向图:\n";
	CreateAdjList(G, DG);
	print(G);
	clear(G);

	cout << "无向图:\n";
	CreateAdjList(G, UDG);
	print(G);
	clear(G);

	cout << "有向网:\n";
	CreateAdjList(G, DN);
	print(G);
	clear(G);

	return 0;
}













