//-----------------------------------------------最小生成树 之 普里姆算法(Prim)-----------------------------------------------
//n个顶点，时间复杂度: O(n^2)，与边数无关，适用于求边稠密的最小生成树
//
//用连通网表示n个城市以及n个城市间可能设置的通信线路，其中网的顶点表示城市，边表示两城市之间的线路，赋予边的权值表示相应的代价。
//最小代价生成树（即最小生成树），一棵生成树的代价就是树上各边的代价之和
//
//算法思路:首先就是从图中的一个起点a开始，把a加入U集合，然后，寻找从与a有关联的边中，权重最小的那条边并且该边的终点b在顶点集合：（V-U）中，我们也把b加入到集合U中，并且输出边（a，b）的信息，
//       这样我们的集合U就有：{a,b}，然后，我们寻找与a关联和b关联的边中，权重最小的那条边并且该边的终点在集合：（V-U）中，我们把c加入到集合U中，并且输出对应的那条边的信息，这样我们的
//	 集合U就有：{a,b,c}这三个元素了，一次类推，直到所有顶点都加入到了集合U。

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

//typedef enum {DG, DN, UDG, UDN} GraphKind;  //默认无向网
const int INT_MAX = 10000;

typedef struct CloseEdge{
	int start;
	int end;
	int weight;
}CloseEdge;

class MGraph{  //以邻接矩阵为存储方式的图类(默认采用无向网)
public:
	MGraph();
	MGraph(int vexnum, int arcnum);
	~MGraph();
	void CreateGraph(void);
	void PrintGraph(void);
	void ClearGraph(void);
	void Prim(int begin);
		
private:
	int vexnum; // 顶点个数
	int arcnum; // 边或弧的个数

	vector<string> vex;  //顶点信息
//	GraphKind kind;  //图的类型，有向图、无向图、有向网、无向网
	int **adjMatrix;   //二级指针，相当于一个二维数组，就是用于保存图的信息的
	CloseEdge *closedge; //这个数组记录到达某个顶点的各个边中的权重最小的那个边。当某个顶点的closedge数组中的weight值为-1，则代表这个顶点在集合U中了，而非在集合V中
};

MGraph::MGraph()
{
	int i,j;
	cout << "输入顶点个数、边或弧的个数:\n";
	cin >> i;
	cin >> j;
	vexnum = i;
	arcnum = j;
	
	closedge = new CloseEdge[vexnum];
}

MGraph::MGraph(int vexnum, int arcnum)
{
	this->vexnum = vexnum;
	this->arcnum = arcnum;

	closedge = new CloseEdge[vexnum];
}

MGraph::~MGraph()
{
	delete [] closedge;
}

void MGraph::CreateGraph(void)
{
	int i, j, weight;
	string msg;

	adjMatrix = new int*[vexnum];
	if(NULL == adjMatrix) {cout << "In CreateGraph, new error\n"; exit(1);} 


	for(i = 0; i < vexnum; ++i)
	{
		adjMatrix[i] = new int[vexnum];
		if(NULL == adjMatrix[i]) 
		{
			cout << "In CreateGraph, new error\n"; exit(1);
		}
	}

	cout << "输入顶点信息:\n";
	for(i = 0; i < vexnum; ++i)
	{
		for(j = 0; j < vexnum; ++j)
		{
			adjMatrix[i][j] = INT_MAX;
		}

		cin >> msg;
		vex.push_back(msg);
	}

	cout << "输入相关联的两个顶点序号即其权值:(例如1 2 4代表顶点1与顶点2相关联，权值为4)\n";
	for(int k = 0; k < arcnum; ++k)
	{
		cin >> i;
		cin >> j;
		cin >> weight;
		
		adjMatrix[i-1][j-1] = weight;
		adjMatrix[j-1][i-1] = weight;
	}//for
}

void MGraph::PrintGraph(void)
{
	int i,j;
	cout << "\n无向网:\n";
	for(i = 0; i < vexnum; ++i)
	{
		cout << vex[i] << ": ";
		for(j = 0; j < vexnum; ++j)
		{
			if(adjMatrix[i][j] != INT_MAX)
				cout << adjMatrix[i][j] << " ";
			else
				cout << "0 ";
		}
		cout << endl;
	}
	cout << endl;
}

void MGraph::ClearGraph(void)
{
	for(int i = 0; i < vexnum; ++i)
	{
		delete adjMatrix[i];
		adjMatrix[i] = NULL;
	}
	delete adjMatrix;
}

void MGraph::Prim(int begin)
{
	if(begin < 1 || begin >vexnum)
	{
		cout << "In Prim, wrong begin\n";
		exit(1);
	}

	int i;
	
	for(i = 0; i < vexnum; ++i) //初始化辅助数组
	{
		if(i != (begin - 1))
		{
			closedge[i].start = begin-1;
			closedge[i].end = i;
			closedge[i].weight = adjMatrix[begin-1][i]; //顶点i的辅助数组closedge的权值等于初始顶点begin与顶点i间的权值
		}
	}

	closedge[begin-1].weight = -1; //把起点的close_edge中的值设置为-1，代表已经加入到集合U了。 此时集合U中只有一开始指定的顶点begin
	
	cout << "树结点间的权值:\n";
	for(i = 1; i < vexnum; ++i) //访问剩下的顶点，并加入依次加入到集合U ****重点理解****     循环内不能再使用i作为for循环的变量！！！
	{
		int min = INT_MAX;
		int k, index;
		
		for(k = 0; k < vexnum; ++k)
		{
			if(closedge[k].weight != -1) //找集合V中集合U中顶点之间权值最小的边。 因为在集合V中的顶点的closedge.weight值不为-1，集合U中顶点的closedge.weight才为-1
			{
				if(closedge[k].weight < min)
				{
					min = closedge[k].weight;
					index = k;  //最小权值的那个边的下标
				}
			}
		}//for

		closedge[index].weight = -1; //将与U集合中的顶点间权重最小的那条边的终点也加入集合U中
		
		//输出对应的生成树的边信息
		cout << vex[closedge[index].start] << "---" << vex[closedge[index].end] 
		     << " : " << adjMatrix[closedge[index].start][closedge[index].end] << endl;  
		//这里第一个不能是vex[begin-1]，之后还会更新的,所以一律写成vex[closedge[x].start]和vex[closedge[x].end]形式！！！

		//*********************************最关键的一步！！！**********************************
		for(k = 0; k < vexnum; ++k) //新顶点进入集合U后，重新选择最小边。 即:去找原先closedge数组中那些顶点权值比 "集合U中新增结点与那些顶点间的权值" 大的closedge顶点， 
		{			     //并把这些顶点的closedge值替换为:"起点start为集合U中新增结点、终点end为这些顶点、权值weight为U中新增结点和这些顶点间的权值"
			if(adjMatrix[closedge[index].end][k] < closedge[k].weight) //作用:去找原先closedge数组中那些顶点权值比 "集合U中新增结点与那些顶点间的权值" 大的closedge顶点
			{       //closedge[index:集合U中新增的顶点下标、 k:各顶点
				closedge[k].start = index;
				closedge[k].end = k;
				closedge[k].weight = adjMatrix[closedge[index].end][k];  //这里adjMatrix的下标closedge[x].end，其实就等于index！
			}
		}
	}//for	
}

int main()
{
	MGraph G;
	G.CreateGraph();
	G.PrintGraph();
	G.Prim(1);
}








