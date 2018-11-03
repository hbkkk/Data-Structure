//---------------------------------------拓扑排序————Kahn算法、DFS算法---------------------------------------
//拓扑排序对应施工的流程图具有特别重要的作用，它可以决定哪些子工程必须要先执行，哪些子工程要在某些工程执行后才可以执行。
//
//实现步骤：1）在有向图中选一个没有前驱的顶点并且输出  2）从图中删除该顶点和所有以它为尾的弧（白话就是：删除所有和它有关的边）
//        3）重复上述两步，直至所有顶点输出，或者当前图中不存在无前驱的顶点为止，后者代表我们的有向图是有环的，因此，也可以通过拓扑排序来判断一个图是否有环。
//
//Kahn算法思想：Kahn的算法的思路其实就是我们之前那个手动展示的拓扑排序的实现，我们先使用一个栈保存入度为0 的顶点，
//        然后输出栈顶元素并且将和栈顶元素有关的边删除，减少和栈顶元素有关的顶点的入度数量并且把入度减少到0的顶点也入栈。
//
//DFS算法思想: 其实DFS就是深度优先搜索，它每次都沿着一条路径一直往下搜索，知道某个顶点没有了出度时，就停止递归，往回走，
//	      所以我们就用DFS的这个思路，我们可以得到一个有向无环图的拓扑序列，其实DFS很像Kahn算法的逆过程。
//
//两种算法总结：对于基于DFS的算法，增加结果集的条件是：顶点的出度为0。这个条件和Kahn算法中入度为0的顶点集合似乎有着异曲同工之妙，
//	      这两种算法的思想犹如一枚硬币的两面，看似矛盾，实则不然。一个是从入度的角度来构造结果集，另一个则是从出度的角度来构造。


#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <string.h>
using namespace std;

typedef string vextype; //顶点类型

typedef struct ArcNode{  //表结点
	int adjvex;  //表示的该边的另外一个顶点在顶点数组中的下标
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
	VNode *arclist; //头结点顺序存储结构指针，即邻接表

public:
	Graph_DG(int vexnum, int arcnum);
	~Graph_DG();

	bool check_edge_value(int a, int b); //检查输入的边是否正确
	void createGraph();
	void print(); //打印邻接表
	bool topological_sort();//进行拓扑排序,Kahn算法

	bool topological_sort_by_dfs();//进行拓扑排序，DFS算法
	void dfs(int n, bool * & visit, stack<string> & result);
};

Graph_DG::Graph_DG(int vexnum, int arcnum)
{
	this->vexnum = vexnum;
	this->arcnum = arcnum;
	this->arclist = new VNode[this->vexnum];
	this->indegree = new int[this->vexnum];

	for(int i = 0; i < this->vexnum; ++i)
	{
		stringstream ss;
		ss << (i+1);
		string s1 = ss.str();
		this->indegree[i] = 0;
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
}

bool Graph_DG::check_edge_value(int a, int b)
{
	if(a < 1 || b < 1 || a > this->vexnum || b > this->vexnum)
		return false;
	return true;
}

void Graph_DG::createGraph()
{
	int i, j;
	ArcNode *next, *p;

	cout << "输入边的两个顶点:\n";
	for(int k = 0; k < this->arcnum; ++k)  //这里循环变量不能用i！！！因为循环里面也用到了i，会覆盖！！！！
	{
		cin >> i;
		cin >> j;
		while(!check_edge_value(i, j))
		{
			cout << "请输入正确的顶点序号:\n";
			cin >> i;
			cin >> j;
		}

		next = new ArcNode;
		next->adjvex = j-1;  //*****是j-1，不是j！
		next->nextarc = NULL;
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
			cout << p->adjvex << " ";
			p = p->nextarc;
		}
		cout << endl;
	}
}

bool Graph_DG::topological_sort()  //Kahn算法
{
	cout << "图的拓扑排序如下(Kahn算法):\n";

	int i;
	int count = 0; //用于记录输出的顶点个数
	ArcNode *temp;
	stack<int> s; //用于保存顶点入度为0的栈

	//计算顶点入度，保存在数组indegree中
	for(i = 0; i < this->vexnum; ++i)
	{
		temp = this->arclist[i].firstarc;
		while(temp)
		{
			++(this->indegree[temp->adjvex]);  //表结点中的adjvex表示的顶点下标就是一条边的入度顶点
			temp = temp->nextarc;
		}
	}

	//将入度为0的顶点(即:没有前序的顶点)入栈s
	for(i = 0; i < this->vexnum; ++i)
	{
		if(this->indegree[i] == 0)
			s.push(i); //入栈
	}

	//如果栈为空，则结束循环
	while(!s.empty())
	{
		i = s.top(); //记录栈顶元素并将其从栈中删除
		s.pop();
		cout << this->arclist[i].data << " ";
		
		temp = this->arclist[i].firstarc;  //对顶点i的每个邻接顶点的入度减1，因为拓扑排序的实现就是删除以"没有前驱的顶点"为尾的所有弧，
		while(temp)  			   //代码中的表现就是将这个顶点的头结点后的所有表结点中保存的顶点的入度减1
		{
			if(!(--this->indegree[temp->adjvex]))  //**********注： 自减1"--"的优先级低于->**********
			{  //这个判断是，当与入度为0的顶点i相连接的其他顶点的入度也变为0时，将其入栈
				s.push(temp->adjvex);
			}
			temp = temp->nextarc;
		}
		++count; //记录输入的顶点个数
	}

	if(count == this->vexnum)
	{
		cout << endl;
		return true;
	}
	else
	{
		cout << "该图有环,无拓扑序列！\n";
		return false;
	}	
}

bool Graph_DG::topological_sort_by_dfs()
{
	int i;
	bool *visit;
	stack<string> result;
	
	visit = new bool[this->vexnum];
	memset(visit, 0, this->vexnum);  //初始化visit数组全为false
	
	cout << "图的拓扑序列(DFS算法):\n";
	
	for(i = 0; i < this->vexnum; ++i) //开始执行DFS算法
	{
		if(!visit[i])
		{
			dfs(i,visit, result);
		}
	}

	//输出拓扑序列，因为我们每次都是找到了出度为0的顶点加入栈中，所以输出时其实就要逆序输出，这样就是每次都是输出入度为0的顶点
	for(i = 0; i < this->vexnum; ++i)
	{
		cout << result.top() << " ";
		result.pop();
	}
	cout << endl;
	return true;
}

void Graph_DG::dfs(int n, bool * & visit, stack<string> & result)
{
	visit[n] = true;
	ArcNode *temp = this->arclist[n].firstarc;
	while(temp)
	{
		if(!visit[temp->adjvex])
			dfs(temp->adjvex, visit, result);
		temp = temp->nextarc;
	}

	//由于加入顶点到集合中的时机是在dfs方法即将退出之时，而dfs方法本身是个递归方法，仅仅要当前顶点还存在边指向其他不论什么顶点，它就会递归调用dfs方法，
        //而不会退出。因此，退出dfs方法，意味着当前顶点没有指向其他顶点的边了，即当前顶点是一条路径上的最后一个顶点。换句话说其实就是****此时该顶点出度为0了****
	result.push(this->arclist[n].data);
}

int main()
{
	int vexnum, arcnum;
	cout << "输入顶点个数和弧个数:\n";
	cin >> vexnum;
	cin >> arcnum;

	Graph_DG G(vexnum, arcnum);
	G.createGraph();
	G.print();
//	G.topological_sort();
	G.topological_sort_by_dfs();
}














