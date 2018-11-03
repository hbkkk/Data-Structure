//---------------------------邻接多重表------------------------------
//无向图的一种存储结构
//如果我们使用邻接表来存储图时，对于无向图又有一些不便的地方，例如我们需要对一条已经访问过的边进行删除或者标记等操作时，
//我们除了需要找到表示同一条边的两个结点。这会给我们的程序执行效率大打折扣，所以这个时候，邻接多重表就派上用场啦。

//边结点结构:       mark ivex ilink jvex jlink info

//顶点结点结构:             data firstedge


#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

typedef string vextype;

typedef enum {unvisited, visited} VisitIf;

typedef struct EdgeNode{  //边结点
	VisitIf mark;  //访问标志
	int ivex, jvex;  //一条边上的2个结点
	struct EdgeNode *ilink, *jlink;  //指向下一条依附于顶点i、j的边
	int info;  
}EdgeNode;

typedef struct VNode{ //顶点结点
	vextype data;   //顶点信息
	EdgeNode *firstedge;  //指向以该顶点为结点的第一条边的边结点
}VNode;

typedef struct{
	int vexnum;
	int edgenum;
	VNode *node;
}MGraph;

void CreateGraph(MGraph &G)
{
	int i,a,b;
//	EdgeNode *now = NULL;

	cout << "请输入图的顶点个数:";
	cin >> G.vexnum;
	cout << "请输入图的边的个数:";
	cin >> G.edgenum;

	G.node = new VNode[G.vexnum];
	if(NULL == G.node) {cout << "new G.node error\n"; exit(1);}

	cout << "请输入顶点信息(例如V1,V2,V3...):\n";
	for(i = 0; i < G.vexnum; ++i)
	{
		cin >> G.node[i].data;
		G.node[i].firstedge = NULL;
	}

	cout << "请输入每条边的两个结点:\n";
	cout << "G.edgenum:" << G.edgenum << endl;		
	for(i = 0; i < G.edgenum; ++i)
	{
		cin >> a;
		cin >> b;
	
		EdgeNode *next = new EdgeNode;
		if(NULL == next) {cout << "new edge node error\n"; exit(1);}
		
		next->ivex = a-1;
		next->jvex = b-1;
		next->ilink = NULL;
		next->jlink = NULL;
		next->mark = unvisited;
		next->info = 0;

//		cout << "here\n";

		//记录第一个顶点a的信息
		if(NULL == G.node[a-1].firstedge)
		{
			G.node[a-1].firstedge = next;
		}
		else
/*		{
			now = G.node[a-1].firstedge;
			if(now->ivex == (a-1))
			{
				while(now->ilink)
				{
					now = now->ilink;
				}
				now->ilink = next;
			}
			else if(now->jvex == (a-1))
			{
				while(now->jlink)
				{
					now = now->jlink;
				}
				now->jlink = next;
			}
		}*///else
		{
			EdgeNode *now = G.node[a-1].firstedge;
			while(1)
			{
				if(now->ivex == (a-1) && now->ilink == NULL)
				{
					now->ilink = next;
					break;
				}
				else if(now->ivex == (a-1) && now->ilink != NULL)
				{
					now = now->ilink;
				}
				else if(now->jvex == (a-1) && now->jlink == NULL)
				{
					now->jlink = next;
					break;
				}
				else if(now->jvex == (a-1) && now->jlink != NULL)
				{
					now = now->jlink;
				}
			}
		}

		//记录第二个顶点b的信息
		if(NULL == G.node[b-1].firstedge)
		{
			G.node[b-1].firstedge = next;
		}
		else
/*		{
			now = G.node[b-1].firstedge;
			if(now->ivex == (b-1))
			{
				while(now->ilink)
				{
					now = now->ilink;
				}
				now->ilink = next;
			}
			else if(now->jvex == (b-1))
			{
				while(now->jlink)
				{
					now = now->jlink;
				}
				now->jlink = next;
			}
		}*///else
		{
			EdgeNode *now = G.node[b-1].firstedge;
			while(1)
			{
				if(now->ivex == (b-1) && now->ilink == NULL)
				{
					now->ilink = next;
					break;
				}
				else if(now->ivex == (b-1) && now->ilink != NULL)
				{
					now = now->ilink;
				}
				else if(now->jvex == (b-1) && now->jlink == NULL)
				{
					now->jlink = next;
					break;
				}
				else if(now->jvex == (b-1) && now->jlink != NULL)
				{
					now = now->jlink;
				}
			}
		}
	}//for
	cout << "end of CreateGraph\n";
}


void print(const MGraph &G)
{
	int i;
	EdgeNode *p;

	for(i = 0; i < G.vexnum; ++i)
	{
		cout << "(" << i << ") " << G.node[i].data << ": ";
		p = G.node[i].firstedge;
//		if(NULL != p)
//			cout << "p:" << p << endl;
//cout << "here5\n";
		
		while(NULL != p)
		{
//			cout << "here 6\n";
			cout << "ivex=" << p->ivex << ",jvex=" << p->jvex << "  ";
//			cout << "here 7\n";
//			if(p->ivex == i && NULL != p->ilink)  不用加NULL != p->ilink这条判断条件，因为如果p->ivex等于i了并且p->ilink为NULL，
			if(p->ivex == i)		    //那么p=p->ilink后经过循环判断条件while(p)也会退出
			{
				p = p->ilink;
//				cout << "ivex=" << p->ivex << ",jvex=" << p->jvex << "  ";  //加了这句可能会内存出错！还是老问题，当p等于p->ilink时，此时p可能是NULL！！！
			}
			else if(p->jvex == i)
			{
				p = p->jlink;
//				cout << "ivex=" << p->ivex << ",jvex=" << p->jvex << "  ";
			}
//			else  //不用加这两句
//				p = NULL;
		}
		cout << endl;
	}
}

void clear(MGraph &G)
{
/*	for(int i = 0; i < G.vexnum; ++i)
	{
		
	}*/

	delete [] G.node;
}

int main()
{
	MGraph G;
	cout << "无向图:\n";
	CreateGraph(G);
	print(G);
	clear(G);
}








