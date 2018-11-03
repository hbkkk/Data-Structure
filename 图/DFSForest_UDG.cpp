//------------------------------------无向图的深度优先生成森林------------------------------------
//树的存储结构:孩子兄弟链表表示法，即:左子树是第一个孩子，右子树是下一个兄弟结点
//最后的生成森林其实只生成了一棵树，即在函数DFSForest的第二个循环中创建的那些棵树的根节点其实是兄弟节点的概念
//
//最后生成的森林中的结点顺序与实际输入图中边的顺序有关


#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

//图的数据类型(邻接表)
const int MAX_VEX_NUM = 20;

bool visited[MAX_VEX_NUM];

typedef string vextype;

typedef enum {DG, DN, UDG, UDN} GraphKind;

typedef struct ArcNode{
	int adjvex;
	struct ArcNode *nextarc;
	int info;
}ArcNode;

typedef struct{
	vextype data;
	ArcNode *firstarc;
}VNode, AdjList[MAX_VEX_NUM];

typedef struct ALGraph{
	AdjList adjlist;
	int vexnum;
	int arcnum;
	int kind;
}ALGraph;

//树的数据类型
typedef int TElemType;

typedef struct BiTNode{
	vextype data;
	struct BiTNode *lchild;  //指向该结点的第一个孩子结点
	struct BiTNode *rchild;  //指向该结点的下一个兄弟结点
}BiTNode, *BiTree;



//函数原型
void CreateAdjList(ALGraph &G, int kind);
void print(const ALGraph &G);
int clear(ALGraph &G);

void DFSForest(ALGraph &G, BiTree &T);
void DFSTree(ALGraph &G, int v, BiTree &T);

vextype GetVex(const ALGraph &G, const int v);
int FirstAdjVex(ALGraph &G, int v);  //图G存在，返回与顶点v第一个邻接的顶点
int NextAdjVex(ALGraph &G, int v, int w);   //图G存在，v是G中的某个顶点，w是v的邻接顶点，返回v的(相对于w的)下一个邻接顶点所在数组下标，若w是v的最后一个邻接点，返回-1
void PreOrderTraverse(BiTree T, int level); //先序遍历树

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

vextype GetVex(const ALGraph &G, const int v)
{	
	if(v < 0 || v >= G.vexnum)
		return "wrong";
	else
		return G.adjlist[v].data;
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

void PreOrderTraverse(BiTree T, int level)
{
	if(NULL == T)
		return;
	cout << "level(" << level << "):" << T->data << "  ";
	PreOrderTraverse(T->lchild, level+1);
	PreOrderTraverse(T->rchild, level+1);
}

void DFSForest(ALGraph &G, BiTree &T)
{
	int i;
	BiTree p,q;

	T = p = q = NULL;

	for(i = 0; i < G.vexnum; ++i)
	{
		visited[i] = false;		
	}
	
	for(i = 0; i < G.vexnum; ++i)  //作用:生成若干颗分别以i1、i2、..为根节点的生成树。
	{			       //************这里其实只生成了一棵树，即在这个循环里创建的作为一颗颗树的根节点的新结点们其实是兄弟节点的概念************
		if(!visited[i])
		{
			p = new BiTNode;
			if(!p) {cout << "In DFSForest, new BitNode error\n"; exit(1);}
			p->data = GetVex(G, i);
//			p->data = i;
			p->rchild = NULL;
			p->lchild = NULL;
		
			if(NULL == T) //代表是第一颗生成树的根(T的根)
			{
				T = p;  //其实在最后生成的一颗"大树"中，树根是这些棵树中第一棵树的树根
			}
			else   //代表是其他生成树的根(前一棵的根的"兄弟")
			{
				q->rchild = p;
			}
			q = p; //q指向当前生成树的根
			DFSTree(G, i, p);  //建立以p为根的生成树
		}
	}
}

void DFSTree(ALGraph &G, int v, BiTree &T)
{
	BiTree p,q;
	bool first;
	int w;
 
	p = q = NULL;   //××××××
	visited[v] = true;  //这句后面没对顶点v创建树结点是因为在进这个函数前，上面那个函数已经对顶点v创建过树结点了
	first = true;

	for(w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
	{
		if(!visited[w])
		{
			p = new BiTNode;
			
			p->data = GetVex(G, w);
//			p->data = w;
			p->rchild = NULL;
			p->lchild = NULL;

			if(first)  //w是v的第一个未被访问的邻接顶点
			{
				T->lchild = p;  //根的左孩子结点
				first = false;
			}
			else	   //w是v的其他未被访问的邻接顶点
				q->rchild = p;  //是上一邻接顶点的右兄弟结点
			q = p;

			DFSTree(G, w, q);
		}
	}
}


int main()
{
	int i=0,j=0;
	ALGraph G;
	BiTree T;
	
	cout << "无向图:\n";
	CreateAdjList(G, UDG);
	print(G);
	DFSForest(G, T);
	cout << "深度优先生成森林:\n";
	PreOrderTraverse(T, 1);
	cout << endl;
	clear(G);
}

/*exercise
void DFSForest(ALGraph &G, BiTree &T)
{
	int i;
	BiTree p,q;

	T = p = q = NULL;

	for(i = 0; i < G.vexnum; ++i)
	{
		visited[i] = false;
	}

	for(i = 0; i < G.vexnum; ++i)
	{
		if(!visited[i])
		{
			p = new BiTNode;
			p->data = GetVex(G, i);
			p->rchild = NULL;
			p->lchild = NULL;

			if(NULL == T)
				T = p;
			else
			{
				q->rchild = p;
			}
			q = p;

			DFSTree(G, i, p);
		}
	}
}

void DFSTree(ALGraph &G, int v, BiTree &T)
{
	int i, w;
	BiTree p,q;
	bool first = true;

	p = q = NULL;

	visited[v] = true;
	for(w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
	{
		if(!visited[w])
		{
			p = new BiTNode;
			p->data = GetVex(G, w);
			p->rchild = NULL;
			p->lchild = NULL;

			if(first)
			{
				T->lchild = p;
				first = false;
			}
			else
			{
				q->rchild = p;
			}
			q = p;
			
			DFSTree(G, w, q);
		}
	}
}*/







