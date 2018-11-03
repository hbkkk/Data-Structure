//---------------------------------------关键路径---------------------------------------
//AOE网：边表示活动的网。 AOE-网是一个带权的有向无环图，顶点表示时间、弧表示活动、权表示活动持续的时间。AOE-网只是比AOV-网多了一个边的权重
//AOV-网一般是设计一个庞大的工程各个子工程实施的先后顺序； 而AOE-网就是不仅仅关系整个工程中各个子工程的实施的先后顺序，同时也关系整个工程完成最短时间。
//名词解释：  关键路径：AOE-网中，从起点到终点最长的路径的长度（长度指的是路径上边的权重和）  ********关键活动：关键路径上的边，其l(i)=e(i)********
//							            称l(i)-e(i)为完成活动ai的时间余量，当活动的余量为0时，该活动自然就是关键活动了呀！
//			  ****↓↓↓↓↓↓↓↓↓****
//*********注：从顶点v0到顶点vi的"最长路径"的长度为顶点vi的最早发生时间，同时，vi的最早发生时间也是所有以vi为尾的弧所表示的活动的最早开始时间********
//
//假设a(i)是弧<j,k>上的活动，j为尾、k为头： e(i)————活动a(i),即弧i的最早发生时间   l(i)————活动a(i),即弧i的最晚发生时间    
//				       ve(j)————弧尾顶点j的最早发生时间       vl(k)————弧头顶点k的最晚发生时间   dut(<j,k>)————活动持续时间，即弧的权值
//
//*******要求的就是：******* 每条弧的e(i)和l(i)   e(i) = ve(j)
//				 	      l(i) = vl(k)-dut(<j,k>)
//求e（i）和l（i）就必须先知道各个顶点的ve和vl
// (1)先求ve
//    从ve（0）=0开始往前推（其实就是从起点开始往后，求各个顶点最早发生时间），
//    公式如下： ve(j)=Max{ve{i}+dut(<i,j>)},  <i,j>属于T，j=1,2.....n-1，其中T是所有以第j个顶点为头的弧的集合。n为顶点的个数
// (2)再求vl
//    vl是从vl（n-1）=ve（n-1）往后推进（其实就是从终点开始往前求各个顶点的最迟发生时间，其中终点的ve和vl是相等的）
//    公式如下： vl(i)=Min{vl(j)-dut(<i,j>)}， <i,j>属于S，i=n-2,n-3.....0， 其中，S是所有以第i个顶点为尾的弧的集合
//
//求关键路径的步骤：1）输入顶点数和边数，已经各个弧的信息建立图
//		 2）从源点v1出发，令ve[0]=0;按照拓扑序列往前求各个顶点的ve。如果得到的拓扑序列个数小于网的顶点数n，说明我们建立的图有环，无关键路径，直接结束程序
//		 3）从终点vn出发，令vl[n-1]=ve[n-1]，按逆拓扑序列，往后求其他顶点vl值
//		 4）根据各个顶点的ve和vl求每个弧的e（i）和l（i），如果满足e（i）=l（i），说明是关键活动。
//
//主要用途： 估算某些工程完成的时间(非常有用)


#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <string.h>
using namespace std;

typedef string vextype; //顶点类型

typedef struct ArcNode{  //表结点
	int end;     //弧头的顶点下标，有箭头的一方
	int start;   //弧尾的顶点下标
	int weight;  //弧的权值
	struct ArcNode *nextarc;  //指向的是下一条依附在该顶点的边的信息
}ArcNode;

typedef struct VNode{ //头结点
	vextype data;
	ArcNode *firstarc;
}VNode;

class Graph_DG{ //有向网 类
private:
	int vexnum;     //顶点个数
	int arcnum;     //边的个数
	int *indegree;  //记录顶点入度的数组
	int *ve;	//记录每个顶点的最早发生时间
	int *vl;	//记录每个顶点的最晚发生时间
	stack<int> List;//拓扑序列中各个边的情况
	VNode *arclist; //头结点顺序存储结构指针，即邻接表

public:
	Graph_DG(int vexnum, int arcnum);
	~Graph_DG();

	bool check_edge_value(int a, int b); //检查输入的边是否正确
	void createGraph();
	void print(); //打印邻接表
	bool topological_sort();//进行拓扑排序,Kahn算法，在这个函数中计算各顶点ve
	bool CriticalPath(); //求图的关键路径
};

Graph_DG::Graph_DG(int vexnum, int arcnum)
{
	this->vexnum = vexnum;
	this->arcnum = arcnum;
	this->ve = new int[this->vexnum];
	this->vl = new int[this->vexnum];
	this->arclist = new VNode[this->vexnum];
	this->indegree = new int[this->vexnum];

	for(int i = 0; i < this->vexnum; ++i)
	{
		stringstream ss;
		ss << (i+1);
		string s1 = ss.str();

		this->indegree[i] = 0;
		this->ve[i] = 0;
		this->arclist[i].firstarc = NULL;
//		this->arclist[i].data = "V" + to_string(i+1);
		this->arclist[i].data = "V" + s1;
	}
}

Graph_DG::~Graph_DG()
{
	ArcNode *p, *q;
	for(int i = 0; i < this->vexnum; ++i)
	{
		if(NULL != this->arclist[i].firstarc)
		{
			p = this->arclist[i].firstarc;
/*			while(p->nextarc) 
			{ //不用这样，因为有上面的if判断，此时的p一定不是NULL，所以while的循环条件是p就行了。
				q = p->nextarc;
				delete p;
				p = q;
			}*/
			while(p)
			{
				q = p->nextarc;
				delete p;
				p = q;
			}//while
		}//if
	}//for
	delete [] this->indegree;
	this->indegree = NULL;
	delete [] this->arclist;
	this->indegree = NULL;
	delete [] this->ve;
	this->ve = NULL;
	delete [] this->vl;
	this->vl = NULL;
}

bool Graph_DG::check_edge_value(int a, int b)
{
	if(a < 1 || b < 1 || a > this->vexnum || b > this->vexnum)
		return false;
	return true;
}

void Graph_DG::createGraph()
{
	int i, j, weight;
	ArcNode *next, *p;

	cout << "输入弧的两个顶点(尾 头)及权值:\n";
	for(int k = 0; k < this->arcnum; ++k)  //这里循环变量不能用i！！！因为循环里面也用到了i，会覆盖！！！！
	{
		cin >> i;
		cin >> j;
		cin >> weight;
		while(!check_edge_value(i, j))
		{
			cout << "请输入正确的顶点序号:\n";
			cin >> i;
			cin >> j;
			cin >> weight;
		}

		next = new ArcNode;
		next->start = i-1;
		next->end = j-1;  //*****是j-1，不是j！
		next->weight = weight;
		next->nextarc = NULL;

		++this->indegree[next->end]; //对应弧头入度加1		

		if(NULL == arclist[i-1].firstarc)
		{
			arclist[i-1].firstarc = next;
		}
		else  //尾插法,即:顺序
		{
			p = arclist[i-1].firstarc;
			while(p->nextarc) //********!!!不能是p，否则退出循环后的p->nextarc=next会报错，因为此时的p是NULL！！！！
				p = p->nextarc;
			p->nextarc = next;
		}
	}
}

void Graph_DG::print()
{
	cout << "图的邻接表\n";
	for(int i = 0; i < this->vexnum; ++i)
	{
		cout << this->arclist[i].data << ": ";
		ArcNode *p = this->arclist[i].firstarc;
		while(p)
		{
			cout << p->end << " ";
			p = p->nextarc;
		}
		cout << endl;
	}
}

bool Graph_DG::topological_sort()  //Kahn算法
{
	int i;
	ArcNode *temp;
	stack<int> s;
	int count = 0;  //统计输出顶点个数，用来判断是否有环
	
	for(i = 0; i < this->vexnum; ++i)
	{
		if(indegree[i] == 0)
			s.push(i);
	}

	cout << "图的拓扑排序:\n";
	
	while(!s.empty())  //***********注***********
	{
		i = s.top();
		s.pop();
		cout << this->arclist[i].data << " ";

		this->List.push(i); //增设一个栈以记录拓扑有序序列，则在求得各顶点的ve值之后，从栈顶至栈底便为逆拓扑有序序列

		temp = this->arclist[i].firstarc;
		while(NULL != temp)
		{
			if(!(--this->indegree[temp->end]))
			{
				s.push(temp->end);
			}

			/***************************************求ve***************************************/
			//每一次while循环中的i都是同一个顶点，到下一次循环再变
			if( (ve[i]+temp->weight) > ve[temp->end] )  //ve(j)=Max{ve{i}+dut(<i,j>)}，所以这里if中判断条件中是ve[i]!!!
			{					    //*****注：这个while循环里的都是与同一顶点相邻接的顶点，所以是ve[i]
				ve[temp->end] = ve[i]+temp->weight;
			}
		
			temp = temp->nextarc;
		}//while
		++count;
	}//while

	if(this->vexnum == count)
	{
		cout << "\ntopological_sort Done!" << endl << endl;
		return true;
	}
	cout << "count:" << count << endl;
	cout << "此图有环！\n";
	return false;	
}

bool Graph_DG::CriticalPath()
{
	if(!this->topological_sort())
	{
		cout << "此图有环啊！" << endl;
		return false;
	}

	cout << "图的关键路径：\n";

	int k;
	//初始化vl数组，让他们都等于最后一个顶点的ve值，即从vl(n-1) = ve(n-1)起向后递推
	for(k = 0; k < this->vexnum; ++k)
	{
		vl[k] = ve[this->vexnum-1];
	}

	/**********************************************求vl*********************************************/
	ArcNode *temp;
	while(!this->List.empty())
	{
		k = List.top();  //从逆拓扑排序开始，求vl
		List.pop();
		temp = this->arclist[k].firstarc;   //*****注：这个while循环中第一次到这步时，下面的while是不会进去的，因为此时的k是最后那个顶点，
						    //它不再指向其他顶点，所以此时的temp是NULL！
	
		while(NULL != temp)  //从以第k个顶点为***弧尾***集合中选择一个最小的值来作为第k个顶点的最迟发生时间
		{
			if(vl[k] > (vl[temp->end]-temp->weight))   //vl(i)=Min{vl(j)-dut(<i,j>)}
			{
				vl[k] = vl[temp->end]-temp->weight;   //以顶点k为弧尾的所有弧中选，vl[temp->end]中的"temp->end"代表顶点k指向的那个顶点
			}
			temp = temp->nextarc;
		}//while
	}//while


	/**********************************************求各活动(弧)的最早、最晚开始时间e和l*********************************************/
	int ee; //活动(弧)的最早开始时间
	int el; //活动(弧)的最晚开始时间

	for(k = 0; k < this->vexnum; ++k)
	{
		temp = this->arclist[k].firstarc;
		while(temp)
		{
			ee = ve[k];
			el = vl[temp->end] - temp->weight;

			if(ee == el)  //若temp指定的这条弧的ee与el相等，则说明这条弧是关键路径
			{
				cout << this->arclist[k].data << "----";
				cout << this->arclist[temp->end].data << " = ";
				cout << temp->weight << endl;
			}//if
			temp = temp->nextarc;
		}//while
	}//for
	
	return true;
}


int main()
{
	int vexnum, arcnum;
	cout << "输入顶点、弧的个数:\n";
	cin >> vexnum;
	cin >> arcnum;
	
	Graph_DG G(vexnum, arcnum);

	G.createGraph();
	G.print();
	G.CriticalPath();

	return 0;
}













