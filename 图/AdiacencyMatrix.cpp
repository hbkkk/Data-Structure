//---------------矩阵图---------------
//    优点：
//    直观、容易理解，可以很容易的判断出任意两个顶点是否有边，最大的优点就是很容易计算出各个顶点的度。
//    缺点：
//    当我么表示完全图的时候，邻接矩阵是最好的表示方法，但是对于稀疏矩阵，由于它边少，但是顶点多，这样就会造成空间的浪费。


#include <iostream>

#define INT_MAX 10000

using namespace std;

typedef enum {DG, DN, UDG, UDN} GraphKind;

typedef struct {
	int *vex;    //图中顶点的信息，可不用
	int vexnum;   //图中顶点的个数
	int edge;  //图中边或者弧的个数
	int **adjMatrix;   //二级指针，相当于一个二维数组，就是用于保存图的信息的
	GraphKind kind;  //图的类型，有向图、无向图、有向网、无向网
}MGraph;

void CreateGraph(MGraph &G, GraphKind kind)
{
	int i,j,k,weight;

	G.kind = kind;
	cout << "输入顶点个数:" << endl;
	cin >> G.vexnum;
	cout << "输入边或弧的个数:" << endl;
	cin >> G.edge;

	G.vex = new int[G.vexnum];   //申请顶点个数的整型数组空间，用于保存顶点信息
	G.adjMatrix = new int*[G.vexnum];  //创建二级指针空间，这里相当于创建一G.vexnum个数组***********************记住如何使用new的

	for(i = 0; i < G.vexnum; ++i)   //这里相当于在上面创建的G.vexnum个数组的基础上给每个数组创建G.vexnum个数组元素
	{
		G.adjMatrix[i] = new int[G.vexnum];
	}

	for(i = 0; i < G.vexnum; ++i)  //初始化二维数组
	{
		for(j = 0; j < G.vexnum; ++j)
		{
			if(G.kind == DG || G.kind == UDG)
				G.adjMatrix[i][j] = 0;
			else
				G.adjMatrix[i][j] = INT_MAX;
		}
	}

/*	cout << "输入顶点信息：\n";
	for(i = 0; i < G.vexnum; ++i)
	{
		cin >> G.vex[i];
	}*/

	cout << "输入相关联的两个顶点序号:(例如1 2代表顶点1指向顶点2)\n";
	for(k = 0; k < G.edge; ++k)
	{
		cin >> i;
		cin >> j;
		if(G.kind == DG)
		{				
			G.adjMatrix[i-1][j-1] = 1;  //注：记得加 "-1"， 因为数组是从下标0开始的，如果不加之后会数组越界！
		}
		else if(G.kind == UDG)
		{
			G.adjMatrix[i-1][j-1] = 1;
			G.adjMatrix[j-1][i-1] = 1;
		}
		else if(G.kind == DN)
		{
			cout << "请输入权值:";
			cin >> weight;
			G.adjMatrix[i-1][j-1] = weight;
		}
		else if(G.kind == UDN)
		{
			cout << "请输入权值:";
			cin >> weight;
			G.adjMatrix[i-1][j-1] = weight;
			G.adjMatrix[j-1][i-1] = weight;
		}
//		cout << "G.adjMatrix[" << (i-1) << "][" << (j-1) << "]:" << G.adjMatrix[i-1][j-1] << endl;
//		cout << "G.adjMatrix[" << (j-1) << "][" << (i-1) << "]:" << G.adjMatrix[j-1][i-1] << endl;
	}
}

void print(const MGraph &G)
{
	int i, j;
	for(i = 0; i < G.vexnum; ++i)
	{
		for(j = 0; j < G.vexnum; ++j)
		{
			if(G.adjMatrix[i][j] == INT_MAX)
				cout << "∞ ";
			else
				cout << G.adjMatrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void clear(MGraph &G)
{
	delete G.vex;
	G.vex = NULL;
	for(int i = 0; i < G.vexnum; ++i)
	{
		delete G.adjMatrix[i];
		G.adjMatrix[i] = NULL;
	}
	delete G.adjMatrix;
//	G.adjMatrix = NULL;
}


int main()
{
	MGraph G;

	cout << "有向图：\n";
	CreateGraph(G, DG);
	print(G);
	clear(G);

	cout << "无向图：\n";
	CreateGraph(G, UDG);
	print(G);
	clear(G);

	cout << "有向网：\n";
	CreateGraph(G, DN);
	print(G);
	clear(G);

	cout << "无向网：\n";
	CreateGraph(G, UDN);
	print(G);
	clear(G);

	return 0;
}


/*int main()
{
	int a, b;
	cin >> a;
	cin >> b;  //可以这么输入: 2 31，结果是a等于2，b等于31
	cout << "a:" << a << " ,b:" << b << endl;
}*/










