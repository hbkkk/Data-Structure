//-------------------------------------------广度优先搜索-------------------------------------------
// 存储结构: 邻接表
// 同时还用到 队列，用队列来存储已被访问的顶点，是为了达到 【 “先被访问的顶点的邻接点”先于“后被访问的顶点的邻接点”被访问 】 的效果。
//
// 应用: 可用于迷宫问题
//

#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

//*************以下是邻接表的一些数据结构声明*************
const int MAX_VEX_NUM = 20;   //***************************注*********************************
bool visited[MAX_VEX_NUM];    //因为有visited这个访问标志数组在，所以不用担心在无向图的邻接表中每条边被记录2次的问题，因为只要访问过一个顶点，
			      //那么这个顶点的visited就会被置为true
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


//*************以下是邻接表的一些数据结构声明*************
typedef int QElemType;

typedef struct QNode{
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct{
	QNode *front;  //对头指针
	QNode *rear;   //对尾指针
}LinkQueue;


//*************邻接表基本操作、BFS函数原型*************
void CreateAdjList(ALGraph &G, int kind);
void print(const ALGraph &G);
int clear(ALGraph &G);
void BFSTraverse(ALGraph &G);
int FirstAdjVex(ALGraph &G, int v);  //图G存在，返回与顶点v第一个邻接的顶点
int NextAdjVex(ALGraph &G, int v, int w);   //图G存在，v是G中的某个顶点，w是v的邻接顶点，返回v的(相对于w的)下一个邻接顶点所在数组下标，若w是v的最后一个邻接点，返回-1

//*************队列函数原型*************
int InitQueue(LinkQueue &Q);
int DestroyQueue(LinkQueue &Q);
bool IsEmpty(const LinkQueue &Q);
int EnQueue(LinkQueue &Q, const QElemType &e);
int DeQueue(LinkQueue &Q, const QElemType &e);

int InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = new QNode;
	if(NULL == Q.front) {cout << "new QNode error\n"; exit(1);}
	Q.front->next = NULL;
	return 0;
}

int DestroyQueue(LinkQueue &Q)
{
	if(Q.front->next)
	{
		Q.rear = Q.front->next;
		delete Q.front;
		Q.front = Q.rear;
	}
	return 0;
}

bool IsEmpty(const LinkQueue &Q)
{
	return Q.front == Q.rear;
}

int EnQueue(LinkQueue &Q, const QElemType &e)
{
	QueuePtr node = new QNode;
	if(NULL == node) {cout << "In EnQueue, new QNode error\n"; exit(1);}
	
	node->data = e;
	node->next = NULL;

	Q.rear->next = node; //让队列最后那个结点指向新增的结点
	Q.rear = node;       //让对尾指针指向新增的那个结点

	return 0;
}

int DeQueue(LinkQueue &Q, QElemType &e)
{
	if(IsEmpty(Q)) {cout << "Empty Queue\n"; return -1;}

	QueuePtr q = Q.front->next;
	e = q->data;
	if(NULL == q->next)  //如果队列中就一个结点，那要是直接删除它会导致尾指针丢失
	{
		Q.rear = Q.front;
		Q.front->next = NULL;
	}
	else
	{
		Q.front->next = q->next;
	}
	delete q;

	return 0;
}

static ArcNode *next;  //用于创建每个结点单链表中的表结点

void CreateAdjList(ALGraph &G, int kind)
{
	int i,j,k;
	int weight;
	G.kind = kind;
	cout << "输入顶点个数:";
	cin >> G.vexnum;
	cout << "输入弧或边个数:";
	cin >> G.arcnum;

	cout << "输入每个顶点信息(V1,V2,V3...):\n";
	for(i = 0; i < G.vexnum; ++i)  //初始化图，并给图中每个顶点赋予信息
	{
		cin >> G.adjlist[i].data;
		G.adjlist[i].firstarc = NULL;
	}
	cout << "输入弧或边的两头顶点序号(若是有向的，则输入循序为:尾 头，例如1 2代表顶点1指向顶点2):\n";
	for(k = 0; k < G.arcnum; ++k)
	{
		cin >> i;
		cin >> j;
		
		next = new ArcNode;
		next->adjvex = j-1;
		next->nextarc = G.adjlist[i-1].firstarc;
		G.adjlist[i-1].firstarc = next;

		if(G.kind == DN || G.kind == UDN)
		{
			cout << "输入顶点" << i << "和顶点" << j << "之间的权值:";
			cin >> next->info;
			weight = next->info;
		}
		
		if(G.kind == UDG || G.kind == UDN)
		{
			next = new ArcNode;
			next->adjvex = i-1;
			next->nextarc = G.adjlist[j-1].firstarc;
			G.adjlist[j-1].firstarc = next;
			if(G.kind == UDN)
			{
				next->info = weight;
			}
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

	ArcNode *p, *q;
	for(int i = 0; i < G.vexnum; ++i)
	{
		p = G.adjlist[i].firstarc;
		while(p)
		{
			q = p->nextarc;
			delete p;
			p = q;
		}
		G.adjlist[i].firstarc = NULL;
	}

	return 0;
}


int FirstAdjVex(ALGraph &G, int v)  //图G存在，返回与顶点v(即第v+1个顶点)第一个邻接的顶点
{
	if(v < 0 || v >= G.vexnum)
		return -1;
	
	if(G.adjlist[v].firstarc != NULL)
		return G.adjlist[v].firstarc->adjvex;  //直接就写这么一句会出错！有可能firstarc是NULL，要加判断！！！！
	else
		return -1;
}


int NextAdjVex(ALGraph &G, int v, int w)   //图G存在，v是G中的某个顶点，w是v的邻接顶点，返回v的(相对于w的)下一个邻接顶点，若w是v的最后一个邻接点，返回-1
{
	if(v < 0 || v >= G.vexnum)
		return -1;

	ArcNode *p = G.adjlist[v].firstarc;
	if(NULL == p)
		return -1;
	while(1)
	{
		if(p->adjvex == w && p->nextarc != NULL)
		{
			return p->nextarc->adjvex;
		}
		else if(p->adjvex != w && p->nextarc != NULL)
		{
			p = p->nextarc;
		}
		else if(p->adjvex == w && p->nextarc == NULL)
		{
			return -1;
		}
		else if(NULL == p || (p->adjvex != w && p->nextarc == NULL)) //其实这种情况正常清除下不可能出现，这种情况是w顶点与v顶点没有关联的情况
			return -1;
	}
}


void BFSTraverse(ALGraph &G)
{
	int i,u,w;

	LinkQueue Q;    //这里之所以用队列来存储已被访问的顶点，是为了达到 【“先被访问的顶点的邻接点”先于“后被访问的顶点的邻接点”被访问】 的效果。
	InitQueue(Q);

	for(i = 0; i < G.vexnum; ++i)
	{
		visited[i] = false;
	}

	for(i = 0; i < G.vexnum; ++i)
	{
		if(!visited[i])
		{
			visited[i] = true;
			cout << "搜索到顶点: " << i << endl;  //这句相当于搜索到顶点后采取的动作
			EnQueue(Q, i);  //将顶点i入队
			while(!IsEmpty(Q))
			{
				DeQueue(Q, u);  //删除队列中第一个顶点，然后依次搜索该顶点的未访问过的邻接点，并把他们放到队列中，为了之后搜索他们的邻接点
				for(w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))  //这个for循环作用: 依次访问每个顶点的邻接点，并将其放入队列中
				{							     //循环条件:该顶点u有下一个邻接顶点
					if(!visited[w])  //w为u的尚未访问的邻接顶点
					{
						visited[w] = true;
						cout << "搜索到顶点: " << w << endl;  //这句相当于搜索到顶点后采取的动作
						EnQueue(Q, w); //w搜索过后，把它放入队列，为了之后继续搜索它的邻接顶点
					}
				}//for
				
			}//while
		}//if
	}//for
}


int main()
{
	ALGraph G;

	cout << "有向图:\n";
	CreateAdjList(G, DG);
	print(G);
	cout << "广度优先搜索:\n";
	BFSTraverse(G);
	clear(G);

	cout << "无向图:\n";
	CreateAdjList(G, UDG);
	print(G);
	cout << "广度优先搜索:\n";
	BFSTraverse(G);
	clear(G);

	return 0;
}













