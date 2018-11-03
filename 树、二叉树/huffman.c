#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode, *HuffmanTree;

typedef char ** HuffmanCode;  //编码表

void Select(HuffmanTree ht, int n, int *s1, int *s2);
void CreateHuffmanTree(HuffmanTree *ht, int *w, int n);
void CreateHuffmanCode(HuffmanTree ht, HuffmanCode *hc, int n);
void CreateHuffmanCode2(HuffmanTree ht, HuffmanCode *hc, int n);
void TranCode(HuffmanTree ht,char a[],char zf[],char b[],int n); 

void CreateHuffmanTree(HuffmanTree *ht, int *w, int n) //ht：赫夫曼树、w：赫夫曼树叶子结点的权值数组，n：赫夫曼树叶子结点个数
{
	if(n <= 1) {printf("In create huffmantree, wrong n\n"); exit(1);}

	int i = 0;
	int m = 2 * n - 1;  //若有n个叶子结点，那么赫夫曼树就总共2n-1个结点
	*ht = (HuffmanTree)malloc((m+1)*sizeof(HTNode));  //0号元素不用,所以这里分配空间时要 m+1 个！！！！
	if(NULL == *ht)
	{
		printf("In create huffman tree, malloc failed\n");
		exit(1);
	}
	
	for(i = 1; i <= m; ++i)   //从数组下标为1的开始
	{
		(*ht)[i].parent = 0;
		(*ht)[i].lchild = 0;
		(*ht)[i].rchild = 0;
		(*ht)[i].weight = 0;
//		++(*ht);  //这句话不能加，没意义啊！！！这里用的是增加i来给每个结点赋值。如果加上这句话，会一直使下标为1的结点的左孩子的值非0！！！

/*		(*ht)->parent = 0;   /********************下面这5行的初始化法有个问题，就是会让下标为1的结点的左孩子的值非0！！！！***********************
		(*ht)->lchild = 0;
		(*ht)->rchild = 0;
		(*ht)->weight = 0;
		++(*ht);*/
	}
	for(i = 1; i <= n; ++i)  //前n个分量表示的是叶子结点
	{
		(*ht)[i].weight = w[i-1];
	}

//	printf("lchild 1 inside:%d\n", (*ht)[1].lchild);
//	printf("lchild 0 inside:%d\n", (*ht)[0].lchild);
	int s1,s2;
	//通过n-1次的选择，删除，合并来构造哈夫曼树
	for(i = n+1; i <= m; ++i)  //最后一个分量是根结点，即(*ht)[m]
	{				     //*********************注：这里Select函数传进去的第二个参数是i-1！！！！！！不能传n进去
		Select(*ht, i-1, &s1, &s2); //这里之所以是i-1,是因为这里的i是等于n+1的，故在进行第一次Select函数时，赫夫曼树中只有n个节点是有权值的，之后以此类推
//		printf("(*ht + s1)->weight:%d, (*ht + s2)->weight:%d\n", (*ht + s1)->weight, (*ht + s2)->weight);
		(*ht + i)->weight = (*ht + s1)->weight + (*ht + s2)->weight;  //结点i的权值为s1,s2权值之和
									      //当最后一次循环时，即*ht+i为根结点，它的双亲parent为0，因为最开始全都初始化为0了
//		(*ht)[i].weight = (*ht)[s1].weight + (*ht)[s2].weight; //这么写也行！！

		(*ht + s1)->parent = i;  //这里的i就是新结点的下标，这两行就是将两颗根结点权值最小的树作为左右子树构造新的一颗二叉树，而新的二叉树的2子树就是(*ht)[s1]和(*ht)[s2]了
		(*ht + s2)->parent = i;	 //这样就可以达到在二叉树集合中删除原来两颗二叉树的效果，因为在二叉树集合F中找的是“根结点权值”最小的2颗，即parent！！！

		(*ht + i)->lchild = s1;  //可以把这里的(*ht+i)理解为数组中第i个结点，也是赫夫曼算法中选2颗根节点权值最小的树作为左右子树构造一颗新的二叉树中的那个新的根节点！！！！
		(*ht + i)->rchild = s2;
	}
}

//选取数组中根节点权值最小的那两个，并在s1和s2中保存这两个节点在数组中的下标
void Select(HuffmanTree ht, int n, int *s1, int *s2)
{
	int i = 0;
	for(i = 1; i <= n; ++i)  //一开始先找到第一个父结点为0的叶子结点,因为找的是父节点为0的，所以之前用过的子结点就不会包含在内(他们的父结点都是新的父节点的数组下标值，故不再为0)
	{
		if(ht[i].parent == 0)
		{		
			*s1 = i;
			break;
		}
	}
	for(i = 1; i <= n; ++i)
	{
		if(ht[i].parent == 0 && ht[i].weight < ht[*s1].weight)
			*s1 = i;
	}

	for(i = 1; i <= n; ++i)  //先找到第一个父结点为0，且下标不是上面找到的s1
	{
		if(ht[i].parent == 0 && i != *s1)
		{
			*s2 = i;
			break;
		}
	}
	for(i = 1; i <= n; ++i)
	{
		if(ht[i].parent == 0 && ht[i].weight < ht[*s2].weight && i != *s1)
			*s2 = i;
	}
}

/************************好好看看这个函数中第二个参数怎么用的，用到了三级指针******************************************/
void CreateHuffmanCode(HuffmanTree ht, HuffmanCode *hc, int n) //从叶子到根逆向求每个字符的哈夫曼编码，储存在编码表hc中  三级指针*hc
{								//如果函数形参表中用的是二级指针的引用(即: HuffmanCode &hc)，那么下面对应有*hc的地方，星号*都省略就行
	if(n <= 1) {printf("In create huffman code, wrong n\n"); exit(1);}
	int c,p,start;

	//分配储存n个字符编码的编码表空间
	*hc = (char**)malloc((n+1)*sizeof(char*)); //这里给传进来的二级指针hc分配空间，所以函数参数用的是三级指针！！  注意：malloc输出后的强制类型转换是char** ！！！
						   //指向一级指针数组头的二级指针，数组中每个一级指针都指向每个字符对应的编码
	if(NULL == *hc) {printf("In create huffman code, malloc *hc error\n"); exit(1);}

	char *cd = (char *)malloc(n*sizeof(char)); //分配临时编码空间，n个节点，各结点的编码不超过n-1,算上最后一个结束符\0，所以n个字符空间够了
	if(NULL == cd) {printf("In create huffman code, malloc cd error\n"); exit(1);}
	cd[n-1] = '\0';  //最后一个结束符设为0，因为这个临时编码数组是从数组尾向数组头开始一个个保存到 ***********************这个很巧妙！！！***************************

	for(int i = 1; i <= n; ++i)  //开始对每个叶子节点进行编码1~n
	{
		start = n-1; //结束符位置
		for(c = i, p = ht[i].parent; p != 0; c = p, p = ht[p].parent)//这里的c是当前的叶子结点的数组下标，而p是当前叶子结点双亲的数组下标
		{
			if(ht[p].lchild == c)  //当当前结点的下标c等于双亲的左孩子下标即：ht[p].lchild，编码为0
				cd[--start] = '0';
			else  //当当前结点的下标c等于双亲的右孩子下标即：ht[p].rchild，编码为1
				cd[--start] = '1';
		}
		(*hc)[i] = (char *)malloc((n-start)*sizeof(char));  //这里n-start就是已经有编码个数加1(结束符\0)   这里的(*hc)[i]就是这个二级指针指向的char类型指针，
		//上面不能写成(*ht+i)=(char*)malloc...!!!!	    //每个char类型指针对应的是每个字符的编码表的数组头地址
		strcpy((*hc)[i], cd+start);  //这里拷贝是从cd+start开始拷贝，是因为start之前是每次增加一个编码都会减1
	}
}


void CreateHuffmanCode2(HuffmanTree ht, HuffmanCode *hc, int n) //从根节点到叶子节点无栈非递归遍历赫夫曼树HT，求其中n个叶子节点的赫夫曼编码，并保存在HC中
{
	if(n <= 1) {printf("In create huffman code2, wrong n\n"); exit(1);}

	int cur = 2*n-1;
	int cdlen = 0;	

	*hc = (char**)malloc(n*sizeof(char*));  //给二级指针hc分配n给空间，用与储存n个字符的编码
	if(NULL == *hc) {printf("In create huffmancode2, malloc hc failed\n"); exit(1);}

	for(int i = 1; i <= cur; ++i)   //这里先把赫夫曼树中所有结点的weight清0，这里的weight代表每个结点的状态标志
	{	
		ht[i].weight = 0;     //weight为0:还没遍历该结点的左右孩子； weight为1:已经遍历该结点左孩子、右孩子还未遍历； weight为2:已经遍历该结点的左右孩子
	}

	char *cd = (char*)malloc(n*sizeof(char));
	if(NULL == cd) {printf("In create Huffmancode2, malloc cd failed\n"); exit(1);}
	
	while(cur)   //从根节点开始遍历，最后回到根节点结束. 当cur为根结点的parent时，退出循环
	{
		if(ht[cur].weight == 0)
		{
			ht[cur].weight = 1;   //表明其左孩子已经被遍历过了
			if(ht[cur].lchild != 0)
			{	//如果当前节点不是叶子节点，则记下编码，并继续向左遍历
				cd[cdlen++] = '0';
				cur = ht[cur].lchild;
			}
			else
			{	//如果当前节点是叶子节点，则终止编码，并将其保存起来
				cd[cdlen] = '\0';
				(*hc)[cur] = (char*)malloc((cdlen+1)*sizeof(char));  //这里cdlen是从0开始的，而且最后要加一个结束符'\0'，所以要加1
				strcpy((*hc)[cur], cd);
			}
		}//左孩子已被遍历，开始向右遍历右孩子
		else if(ht[cur].weight == 1)
		{
			ht[cur].weight =2;
			if(ht[cur].rchild != 0)   //这里不判断ht[cur].rchild等于0的情况，是因为赫夫曼树中如果一个结点要么左右子树都有、要么左右子树都没有
			{
				cd[cdlen++] = '1';
				cur = ht[cur].rchild;
			}
		}
		else  //当这个结点遍历过自己的左右孩子时，便退回自己的双亲结点继续遍历其右孩子(因为双亲结点的左孩子一定是遍历过的)
		{
			ht[cur].weight = 0;
			cur = ht[cur].parent;			
			--cdlen;
		}
	}//while
}

//函数功能：赫夫曼译码
//参数：  ht:   建立好的赫夫曼树	b[]: 保存译码后结果的字符数组
//	 a[]:  待翻译的编码	n：  赫夫曼树中叶子结点的个数
//	 zf[]: 赫夫曼树叶子结点的字符数组
void TranCode(HuffmanTree ht,char a[],char zf[],char b[],int n) 
{
	int k = 0; //记录已经译出的字符个数
	int p = 2*n-1; //根结点下标
	for(int i = 0; a[i] != '\0'; ++i) //循环结束条件是读到待翻译编码的结束符\0
	{
		//此代码块用来判断读入的二进制字符是0还是1
		if(a[i] == '0')     //**************************好好理解这种方法！！！！*********************如果编码是0就到结点的左子树，如果编码是1就到结点的右子树！！！！编码的规则
			p = ht[p].lchild;
		else if(a[i] == '1')
			p = ht[p].rchild;
		
		//此代码块用来判断HT[q]是否为叶子结点
		if(ht[p].lchild == 0 && ht[p].rchild == 0)	//是叶子结点，说明已经译出一个字符该字符的下标就是找到的叶子结点的下标
		{	
			b[k++] = zf[p-1];  //把下标为p的字符赋给字符数组b[]  **************注：这里的zf的下标应该是p-1，因为赫夫曼树中叶子结点下标是从1开始的，
										//        而给定的字符数组下标是从0开始的，所以要减一！！！
			p = 2*n-1; //重新初始化p为根节点下标，翻译下一个数组a中字符时，从根节点开始
		}
	}
 	//译码完成之后，用来记录译出字符的数组由于没有结束符输出的时候回报错，故紧接着把一个结束符加到数组最后
	b[k] = '\0';  //***********************************
}

int main()
{
	HuffmanTree HT = NULL;
	HuffmanCode HC = NULL;
	int n = 0;
	char a[100] = {0};
	char b[100] = {0};

	printf("请输入要编码的字符个数：");
	scanf("%d", &n);
	getchar();	
	if(n <= 1) {printf("wrong n\n"); exit(1);}

	printf("依次输入%d个字符以及它们对应的权值\n", n);
	int w[n];   //输入字符对应的权值
	char zf[n]; //输入的字符
	for(int i = 0; i < n; ++i)
	{
		printf("第%d个字符以及其权值：", i+1);
		scanf("%c %d", &zf[i], &w[i]);
		getchar();
	}

	CreateHuffmanTree(&HT, w, n);
	printf("after create huffman tree:\n");
	printf("结点i\t字符\t权值\t双亲\t左孩子\t右孩子\t\n");
//	for(int i = 1; i <= 2*n-1; ++i)		//******************************注！！！************************
	//有时候程序运行会报错stack mash，找到原因了，就是这里的zf[i-1]，因为zf数组定义的时候只有n个，但这里循环里的i会达到2n-1，远远大于i了！！！应该分开写！！！
	for(int i = 1; i <= n; ++i)
		printf("%d\t%c\t%d\t%d\t%d\t%d\t\n",i, zf[i-1], HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
	for(int i = n+1; i <= 2*n-1; ++i)
		printf("%d\t%c\t%d\t%d\t%d\t%d\t\n",i, '\0', HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);

	CreateHuffmanCode(HT, &HC, n);
//	CreateHuffmanCode2(HT, &HC, n);  //编码法二
	printf("\nafter create Huffman code:\n");
	printf("结点\t字符\t权值\t编码\n");
	for(int i = 1; i <= n; ++i)
		printf("%d\t%c\t%d\t%s\n", i, zf[i-1], HT[i].weight, HC[i]);

	printf("\n输入二进制待翻译的编码：");
	scanf("%s", a);
	getchar();
	TranCode(HT, a, zf, b, n);
	printf("after TranCode: %s\n", b);
	
}






