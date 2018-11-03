//---------------------------------------最短路径————Dijkstra算法---------------------------------------
//时间复杂度：O(n^2)
//
//解决问题： 单源点的最短路径问题
//
//思想： 按路径长度递增的次序产生最短路径的算法
//
//步骤：(1)假设用带权的邻接矩阵arcs来表示带权有向图，arcs[i][j]表示弧<Vk,Vj>上的权值。若<Vk,Vj>不存在，则置arcs[i][j]为∞
//	  S为已找到从V(这里的V就是源点)出发的最短路径的终点的集合，它的初始状态为空集。那么，从V出发到图上其余各顶点(终点)Vi可能达到的
//	  最短路径长度的初值为：D[i]=arcs[V][i], Vi ∈ V
//
//     (2)选择Vj，使得 D[j] = Min{ D[j] | Vi ∈ V-S }， Vj就是当前求得的一条从V出发的最短路径的终点。 令 S = S U {j}
//
//     (3)修改从V出发到集合V-S上任一顶点Vk可达的最短路径长度。如果 D[j]+arcs[j][k] < D[k] ，则修改 D[k] 为: D[k] = D[j]+arcs[j][k]
//
//     (4)重复操作(2)、(3)共n-1次。由此求得从V到图上其余各顶点的最短路径是依路径长度递增的序列。
//


#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#define INT_MAX 32767

//记录起点到每个顶点的最短路径的信息
struct Dis{
	bool visit;
	int value;
	string path;

	Dis(){
		visit = false;
		value = 0;
		path = "";
	}
};


class Graph_DG{
private:
	int vexnum;  //顶点个数
	int arcnum;  //弧的个数
	int **arcs;  //邻接矩阵
	Dis *dis;    //记录各个顶点最短路径的信息
public:
	Graph_DG(int vexnum, int arcnum);
	~Graph_DG();
	bool check_edge_value(int start, int end, int weight);
	void createGraph();
	void print();
	void Dijkstra(int begin);
	void print_path(int begin);
};

Graph_DG::Graph_DG(int vexnum, int arcnum)
{
	this->vexnum = vexnum;
	this->arcnum = arcnum;

	arcs = new int*[this->vexnum];
	dis = new Dis[this->vexnum];
	
	for(int i = 0; i < this->vexnum; ++i)
	{
		arcs[i] = new int[this->vexnum];
		for(int j = 0; j < this->vexnum; ++j)
		{
			arcs[i][j] = INT_MAX;
		}
	}
}

Graph_DG::~Graph_DG()
{
	for(int i = 0; i < this->vexnum; ++i)
	{
		delete this->arcs[i];
	}
	delete [] arcs;
	delete [] dis;
}

bool Graph_DG::check_edge_value(int start, int end, int weight)
{
	if(start < 1 || start > this->vexnum || end < 1 || end > this->vexnum || weight < 0)
		return false;
	else
		return true;
}

void Graph_DG::createGraph()
{
	int i;
	int end,start,weight;
	cout << "输入弧的尾、头顶点，权值:\n";
	for(i = 0; i < this->arcnum; ++i)
	{
		cin >> start;  //弧尾
		cin >> end;    //弧头
		cin >> weight;
		if(!check_edge_value(start, end, weight))
		{
			cout << "请输入正确的弧尾、弧头、权值:\n";
			cin >> start;  //弧尾
			cin >> end;    //弧头
			cin >> weight;
		}

		arcs[start-1][end-1] = weight;
	}
}

void Graph_DG::print()
{
	cout << "图的邻接矩阵:\n";
	for(int i = 0; i < this->vexnum; ++i)
	{
		for(int j = 0; j < this->vexnum; ++j)
		{
			if(this->arcs[i][j] == INT_MAX)
				cout << "∞" << " ";
			else
				cout << arcs[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}


void Graph_DG::Dijkstra(int begin)
{
	int i;
//	int min = INT_MAX;   //***************注：这句要放在下面的for循环里面！！！！！！！！！！！！！！！！！！！
	int temp; //用于保存那个最小的路径的顶点序号

	stringstream ss2;
	ss2 << begin;
	string s2 = ss2.str();

	for(i = 0; i < this->vexnum; ++i)  //初始化dis数组
	{
		this->dis[i].value = arcs[begin-1][i];

		stringstream ss;
		ss << (i+1);
		string s1 = ss.str();
		
		this->dis[i].path = "V" + s2 + "--->V" + s1;   //设置当前的路径
	}

	//设置起点的到起点的路径为0
	this->dis[begin-1].value = 0;
	this->dis[begin-1].visit = true;

	//计算剩余的顶点的最短路径(vexnum-1个)
	for(i = 1; i < this->vexnum; ++i)
	{
		int min = INT_MAX;  //这行必须放在for循环里面！！！不然第一次循环后min就一直是最小的不变了啊啊啊啊啊！！！！！！！！！！！！！！！！！！！

		/***********找所有集合U(即未列入最短路径中的顶点集合)中权值最小的那条路径**********/		
		for(int j = 0; j < this->vexnum; ++j)   
		{
			if(!this->dis[j].visit && this->dis[j].value < min)  //这里不能是arcs[begin-1][j] < min， 应该是dis[j].value < min
			{
				cout << "111 j:" << j << endl;
				min = this->dis[j].value;  //这里不是=arcs[begin-1][j]，应该是=this->dis[j].value！！！！！
				temp = j;   //这里是temp=j ,不是 temp=i !!!!!
			}
		}
		cout << "i:" << i << " ,temp:" << temp << endl;

		this->dis[temp].visit = true;  //把在集合U中找到的那个顶点加入已找到最短路径顶点集合中  这个算法是针对单源点最短路径的！！！！！！！！！！！！！！
		
		for(int j = 0; j < this->vexnum; ++j)
		{
			//***************注： 是arcs[temp][j] != INT_MAX，不是dis[j]!=INT_MAX！！！！！！！！
			//**************三个判断条件： 1）j顶点未访问过 2）temp顶点和j顶点间是相通的 3）temp与j顶点间距离小于源点与j顶点间的距离

			if(!this->dis[j].visit && arcs[temp][j] != INT_MAX && (this->dis[temp].value + arcs[temp][j]) < this->dis[j].value )
			{             //!=INT_MAX是为了保证temp和j之间是相通的    上面这个比较的条件是新得到的最短路径可以影响其他未访问的顶点的情况
				this->dis[j].value = this->dis[temp].value + arcs[temp][j];  //********注：即距离(源点→顶点temp→顶点j) < 距离(源点→顶点j)

				stringstream s;
				s << (j+1);
				string sj = s.str();

				this->dis[j].path = this->dis[temp].path + "--->V" + sj;
			}
			/*if(!this->dis[j].visit)
				cout << "j:" << j << " ,!this->dis[j].visit" << endl;
			if(arcs[temp][j] != INT_MAX)
				cout << "j:" << j << " ,arcs[temp][j] != INT_MAX" << endl;
			if((this->dis[temp].value + arcs[temp][j]) < this->dis[j].value)
				cout << "j:" << j << " ,(this->dis[temp].value + arcs[temp][j]) < this->dis[j].value" << endl;*/
		}	
	}
}


void Graph_DG::print_path(int begin)
{
	stringstream ss;
	ss << begin;
	string s1 = "V" + ss.str();
	
	cout << "以顶点" << s1 << "为起点的图的最短路径如下:\n";

	for(int i = 0; i < this->vexnum; ++i)
	{
		if(this->dis[i].value != INT_MAX)  //这里判断是否等于是2个等号！！！！！！！！！！！！！
		{
			cout << dis[i].path << " = " << this->dis[i].value << endl;
		}
		else
		{
			cout << dis[i].path << " 之间没有最短路径\n";
		}
	}
}


int main()
{
	int vexnum, arcnum;
	cout << "输入顶点数、弧的个数:\n";
	cin >> vexnum;
	cin >> arcnum;
	if(vexnum <= 0 || arcnum <=0)
	{
		cout << "请输入正确的顶点数、弧的个数:\n";
		cin >> vexnum;
		cin >> arcnum;
	}

	Graph_DG G(vexnum, arcnum);
	G.createGraph();
	G.print();

	G.Dijkstra(1);
	G.print_path(1);

	return 0;
}



/****************************************************Test*************************************************/
/*void Graph_DG::Dijkstra(int begin)
{
	int temp;
	
	stringstream ss;
	ss << begin;
	string s1 = "V" + ss.str();

	for(int i = 0; i < vexnum; ++i)
	{
		stringstream ss1;
		ss1 << (i+1);
		string s2 = "V" + ss1.str();
		dis[i].path = s1 + "--->" +s2;

		dis[i].value = arcs[begin-1][i];
	}

	dis[begin-1].value = 0;
	dis[begin-1].visit = true;

	for(int i = 1; i < vexnum; ++i)
	{
		int min = INT_MAX;

		for(int j = 0; j < vexnum; ++j)
		{
			if(!dis[j].visit && dis[j].value < min)
			{
				min = dis[j].value;
				temp = j;
			}
		}
		
		dis[temp].visit = true;

		for(int j = 0; j < vexnum; ++j)
		{			//***********注！不是dis[j].value!=INT_MAX，这里是为了保证temp顶点与j顶点之间是相通的
//			if(!dis[j].visit && dis[j].value != INT_MAX && (dis[temp].value + arcs[temp][j]) < dis[j].value)
			if(!dis[j].visit && arcs[temp][j] != INT_MAX && (dis[temp].value + arcs[temp][j]) < dis[j].value)
			{
				dis[j].value = dis[temp].value + arcs[temp][j];

				stringstream ss3;
				ss3 << (j+1);
				string s3 = "V" + ss3.str();
				dis[j].path = dis[temp].path + "--->" + s3;
			}
		}
	}
}*/










