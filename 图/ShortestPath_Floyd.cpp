//---------------------------------------最短路径————Floyd算法---------------------------------------
//时间复杂度：O(n^3)
//
//解决问题： 每一对顶点间的最短路径
//
//思想: 如果要让任意两点（例如从顶点a点到顶点b）之间的路程变短，只能引入第三个点（顶点k），并通过这个顶点k中转即a->k->b，才可能缩短原来从顶点a点到顶点b的路程。
//     那么这个中转的顶点k是1~n中的哪个点呢？甚至有时候不只通过一个点，而是经过两个点或者更多点中转会更短，即a->k1->k2b->或者a->k1->k2…->k->i…->b。
//即：最开始只允许经过1号顶点进行中转，接下来只允许经过1和2号顶点进行中转……允许经过1~n号所有顶点进行中转，求任意两点之间的最短路程。
//
//用一句话概括就是：从i号顶点到j号顶点只经过前k号点的最短路程。
//
//
//

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#define INT_MAX 1000000

class Graph_DG{
private:
	int kind; //图的种类，1为有向图、2为无向图
	int vexnum;
	int arcnum;
	int **arcs; //用于记录各弧的权值
	int **dis;  //用于记录各顶点间的最短路径
	int **path; //矩阵P中的元素path[i][j]，表示顶点i到顶点j经过了path[i][j]记录的值所表示的顶点。 *****************
public:
	Graph_DG(int vexnum, int arcnum, int kind);
	~Graph_DG();
	bool check_edge_value(int start, int end, int weight);
	void createGraph();
	void print();
	void floyd();
	void print_floyd();
};


Graph_DG::Graph_DG(int vexnum, int arcnum, int kind)
{
	this->kind = kind;
	this->vexnum = vexnum;
	this->arcnum = arcnum;
	arcs = new int*[this->vexnum];
	dis = new int*[this->vexnum];
	path = new int*[this->vexnum];  //
	
	for(int i = 0; i < this->vexnum; ++i)
	{
		arcs[i] = new int[this->vexnum];
		dis[i] = new int[this->vexnum];
		path[i] = new int[this->vexnum];
		
		for(int j = 0; j < this->vexnum; ++j)
		{
			arcs[i][j] = INT_MAX;  //初始化每条弧的权值
		}
	}
}


Graph_DG::~Graph_DG()
{
	for(int i = 0; i < vexnum; ++i)
	{
		delete [] arcs[i];
		delete [] dis[i];
		delete [] path[i];
	}

	delete [] arcs;
	delete [] dis;
	delete [] path;
}


bool Graph_DG::check_edge_value(int start, int end, int weight)
{
	if(start < 1 || start > vexnum || end < 1 || end > vexnum || weight < 0)
		return false;
	else
		return true;
}


void Graph_DG::createGraph()
{
	int end,start,weight;
	cout << "输入图中弧的起点、终点、权值:\n";
	for(int i = 0; i < arcnum; ++i)
	{
		cin >> start;
		cin >> end;
		cin >> weight;
		while(!check_edge_value(start, end, weight))
		{
			cout << "请输入正确的弧的起点、终点、权值:\n";
			cin >> start;
			cin >> end;
			cin >> weight;
		}
		arcs[start-1][end-1] = weight;

		if(kind == 2)
			arcs[end-1][start-1] = weight;
	}
}


void Graph_DG::print()
{
	cout << "图的邻接矩阵:\n";
	for(int i = 0; i < vexnum; ++i)
	{
		for(int j = 0; j < vexnum; ++j)
		{
			if(arcs[i][j] == INT_MAX)
				cout << "∞" << " ";
			else
				cout << arcs[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}


void Graph_DG::floyd()
{
	int i,j;
	for(i = 0; i < vexnum; ++i)  //行
	{
		for(j = 0; j < vexnum; ++j)  //列
		{
			dis[i][j] = arcs[i][j]; //初始化每两个顶点间的最短路径为这两个顶点间的距离
			path[i][j] = j; //初始化矩阵P的初值则为各个边的终点顶点的下标
		}
	}

	int temp = 0; //中间顶点的序号
	int select = 0; //用于防止溢出，保存起点到中间点权值加上中间点到终点权值的值
	for(temp = 0; temp < vexnum; ++temp) //这里是每个中间顶点  *******注：第一次循环可看做是只有一个顶点作为中间顶点，第二次循环可看做是只有一个或只有两个顶点作为中间顶点，
	{							        //第三次循环可看做是只有一个或只有两个或只有三个顶点作为中间顶点，以此类推...
		for(i = 0; i < vexnum; ++i) //这里的i是每个起点
		{
			for(j = 0; j < vexnum; ++j) //这里的j是每个终点
			{
				//这里的if判断条件是为了保证中间点temp与起点、终点都是相通的
				select = (dis[i][temp] == INT_MAX || dis[temp][j] == INT_MAX) ? INT_MAX : (dis[i][temp]+dis[temp][j]);
				if(dis[i][j] > select)
				{
					dis[i][j] = select; //更新各点间最短距离矩阵dis
					path[i][j] = path[i][temp];  //更新矩阵P
				}//if
			}//for
		}//for
	}//for
}


void Graph_DG::print_floyd()
{
	int i,j;
	cout << "图的各点对间最短距离为:\n";
	for(i = 0; i < vexnum; ++i)  //起点
	{
		if(kind == 2)
			j = i+1; //*********注：这种是无向图的情况，此时顶点A、顶点B间的最短路径 等价于 顶点B、顶点A间的路径
		else
			j = 0;

		for(; j < vexnum; ++j)  //终点
		{
			if(j == i)
				continue;
			stringstream s1, s2;
			s1 << (i+1);
			s2 << (j+1);
			string str1, str2;
			str1 = "V"+s1.str();
			str2 = "V"+s2.str();

			cout << str1 << "--->" << str2 << " ,weight: ";
			if(dis[i][j] == INT_MAX)
			{				
				cout << " 这两个顶点间无最短距离\n";
				continue;					
			}

			int temp = path[i][j];
			cout << dis[i][j] << " ,path:" << str1 << "--->";
			while(temp != j)
			{
				stringstream s3;
				s3 << (temp+1);
				string str3 = "V" + s3.str();
				cout << str3 << "--->";
				temp = path[temp][j];
			}
			cout << str2 << endl;
		}//for
		cout << endl;
	}//for
}

int main()
{
	int vexnum, arcnum, kind;
	cout << "输入顶点个数、弧的个数:\n";
	cin >> vexnum;
	cin >> arcnum;
	while(1)
	{
//		if(vexnum < 1 || arcnum <1 || vexnum*(vexnum-1)/2 < arcnum)
		if(vexnum < 1 || arcnum <1)
		{
			cout << "请输入正确的顶点个数、弧的个数:\n";
			cin >> vexnum;
			cin >> arcnum;
		}
		else
			break;
	}
	cout << "输入图的类型，1为有向图、2为无向图:\n";
	cin >> kind;
	while(1)
	{
		if(kind != 1 && kind != 2)
		{
			cout << "请输入正确的图的类型:\n";
			cin >> kind;
		}
		else
			break;
	}

	Graph_DG G(vexnum, arcnum, kind);
	G.createGraph();
	G.print();
	G.floyd();
	G.print_floyd();

	return 0;
}
















