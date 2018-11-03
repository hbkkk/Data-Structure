//------------------------------------深度优先搜索(DFS)---------------------------------
// 存储结构: 邻接表
// 遍历规则：不断地沿着顶点的深度方向遍历。顶点的深度方向是指它的邻接点方向。
// 思想：往深里遍历，如果不能深入，则回朔
// 新增了一个visited数组作为访问标志，一旦一个顶点访问过了，其对应了visited数组值就会置true，之后就不会再搜索他了！

#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

const int MAX_VEX_NUM = 20;
		    	      //***************************注*********************************
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

//函数原型
void CreateAdjList(ALGraph &G, int kind);
void print(const ALGraph &G);
int clear(ALGraph &G);
void DFSTraverse(ALGraph &G);
void DFS(ALGraph &G, int v);
int FirstAdjVex(ALGraph &G, int v);  //图G存在，返回与顶点v第一个邻接的顶点
int NextAdjVex(ALGraph &G, int v, int w);   //图G存在，v是G中的某个顶点，w是v的邻接顶点，返回v的(相对于w的)下一个邻接顶点所在数组下标，若w是v的最后一个邻接点，返回-1


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

/******************************************DFS算法***************************************/
void DFSTraverse(ALGraph &G)
{
	int i;
	for(i = 0; i < G.vexnum; ++i)  //初始化访问标志数组
	{
		visited[i] = false;
	}
	for(i = 0; i < G.vexnum; ++i)
	{
		if(!visited[i])  //对尚未访问的顶点调用DFS
		{
			DFS(G, i);
		}
	}
}
void DFS(ALGraph &G, int v)
{
	int w;
	
	visited[v] = true;  //访问到以v为数组下标的顶点后，把它的访问标志置为true
	cout << "访问顶点:" << v << endl;  //这里相当于遍历函数visit()，只是简单的把遍历到的点打印出来罢了，如果需要这里也可以改成一个visit函数
	
	for(w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))  //找到当前搜索到的顶点，然后找这个顶点的下一个连通且未搜索过的顶点.
	{ // 如果一开始w=FirstAdjVex(G,v)就<0，那不会进入循环
		if(!visited[w])  //如果以w为数组下标的那个顶点未搜索过，就对它进行深度优先搜索
		{
			DFS(G, w); //***************这里的递归就是深度优先搜索的“核心”所在！因为传给DFS函数的第二个参数是w，
		}		   //所以递归进去DFS函数后，它访问的是顶点w的邻接点，而不是顶点v的邻接点，所以就一层层递归下去，直到与顶点v路径相同的所有顶点都被访问到为止
	}
}
/*********************************************************************************/



int main()
{
	int i=0,j=0;
	ALGraph G;
	
	cout << "无向网:\n";
	CreateAdjList(G, UDN);
	print(G);
	clear(G);

	cout << "有向图:\n";
	CreateAdjList(G, DG);
	print(G);
	cout << "深度优先搜索:\n";
	DFSTraverse(G);
/*	while(i != -1)
	{
		cin >> i;
		cout << "FirstAdjVex(G," << i << ")=" << FirstAdjVex(G, i) << endl;
	}
	i = 0;
	while(i != -1)
	{
		cin >> i;
		cin >> j;
		cout << "NextAdjVex(ALGraph &G, " << i << ", " << j << ")=" << NextAdjVex(G, i, j) << endl;
	}*/
	clear(G);

	cout << "无向图:\n";
	CreateAdjList(G, UDG);
	print(G);
	cout << "深度优先搜索:\n";
	DFSTraverse(G);
	clear(G);

	cout << "有向网:\n";
	CreateAdjList(G, DN);
	print(G);
	clear(G);

	return 0;
}











