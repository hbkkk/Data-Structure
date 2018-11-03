#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char ** HuffmanCode;

typedef struct{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode, *HuffmanTree;

void Select(HuffmanTree ht, int n, int *s1, int*s2);
void CreateHuffmanTree(HuffmanTree *ht, int w[], int n);
void CreateHuffmanCode(HuffmanTree ht, HuffmanCode *hc, int n);
void CreateHuffmanCode2(HuffmanTree ht, HuffmanCode *hc, int n);
void TranCode(HuffmanTree ht, char a[], char zf[], char b[], int n);

void CreateHuffmanTree(HuffmanTree *ht, int w[], int n)
{
	if(n <= 1) {printf("In create huffman tree, wrong n\n"); exit(1);}

	int s1,s2;
	int i = 0;
	int m = 2*n -1;
	*ht = (HuffmanTree)malloc((m+1)*sizeof(HTNode));
	if(NULL == *ht) {printf("In create huffman tree, malloc ht failed\n"); exit(1);}

	for(i = 1; i <= m; ++i)
	{
		(*ht)[i].weight = 0;
		(*ht)[i].parent = 0;
		(*ht)[i].lchild = 0;
		(*ht)[i].rchild = 0;			
	}
	for(i = 1; i <= n; ++i)
	{
		(*ht)[i].weight = w[i];
	}

	for(i = n+1; i <= m; ++i)
	{
		Select(*ht, i-1, &s1, &s2); //注： 这里传进去的是i-1 ！！！！
		(*ht)[i].weight = (*ht)[s1].weight + (*ht)[s2].weight;
		(*ht)[i].lchild = s1;
		(*ht)[i].rchild = s2;			
		(*ht)[s1].parent = i;
		(*ht)[s2].parent = i;
	}
}

void Select(HuffmanTree ht, int n, int *s1, int*s2)
{
	for(int i = 1; i <= n; ++i)
	{
		if(ht[i].parent == 0)
		{
			*s1 = i;
			break;
		}
	}
	for(int i = 1; i <= n; ++i)
	{
		if(ht[i].parent == 0 && ht[i].weight < ht[*s1].weight)
			*s1 = i;
	}

	for(int i = 1; i <= n; ++i)
	{
		if(ht[i].parent == 0 && i != *s1)
		{
			*s2 = i;
			break;
		}
	}
	for(int i = 1; i <= n; ++i)
	{
		if(ht[i].parent == 0 && ht[i].weight < ht[*s2].weight && i != *s1)
			*s2 = i;
	}
}

void CreateHuffmanCode(HuffmanTree ht, HuffmanCode *hc, int n)
{
	if(n <= 1) {printf("In create huffman code, wrong n\n"); exit(1);}

//	int p = 2*n -1;
	int c,p,start;
	
	*hc = (HuffmanCode)malloc((n+1)*sizeof(char *));
	if(NULL == *hc) {printf("In create huffman code, malloc hc error\n"); exit(1);}

	char *cd = (char*)malloc(n*sizeof(char));
	if(NULL == cd) {printf("In create huffman code, malloc cd error\n"); exit(1);}
	cd[n-1] = '\0';  //**************************

	for(int i = 1; i <= n; ++i)
	{
		start = n-1;
		for(c = i, p = ht[c].parent; p != 0; c = p, p = ht[p].parent)
		{
			if(ht[p].lchild == c)
			{
				cd[--start] = '0';
			}
			else
			{
				cd[--start] = '1';
			}
		}
		(*hc)[i] = (char*)malloc((n-start)*sizeof(char));
		strcpy((*hc)[i], cd+start);
	}
}

void CreateHuffmanCode2(HuffmanTree ht, HuffmanCode *hc, int n)
{
	if(n <= 1) {printf("In create huffman code, wrong n\n"); exit(1);}

	int cdlen = 0;
	int p = 2*n -1;

	*hc = (char **)malloc((p+1)*sizeof(char*));
	if(NULL == *hc)	{printf("In create huffman code 2, malloc hc wrong\n"); exit(1);}

	char *cd = (char*)malloc(n*sizeof(char));
	if(NULL == cd) {printf("In create huffman code 2, malloc cd wrong\n"); exit(1);}

	for(int i = 1; i < p; ++i)
	{
		ht[i].weight = 0;
	}

	while(p)
	{
		if(ht[p].weight == 0)  //这里要加判断状态位！！！
		{
			ht[p].weight = 1;
			if(ht[p].lchild != 0)    //这里应该是跟0比较，不是'0'，赫夫曼树中左、右孩子的值都是结点的下标值！！！因为这里用的是数组形式表示树
			{
				cd[cdlen++] = '0';
				p = ht[p].lchild;
			}
			else
			{
				cd[cdlen] = '\0';
				(*hc)[p] = (char*)malloc((cdlen+1)*sizeof(char));
				strcpy((*hc)[p], cd);  //不能写成strcpy((*hc+p), cd); 第一个参数要是这样的：(*hc)[p]
			}
		}
		else if(ht[p].weight == 1)
		{
			ht[p].weight = 2;
			if(ht[p].rchild != 0)
			{
				cd[cdlen++] = '1';
				p = ht[p].rchild;
			}
		}
		else
		{
			ht[p].weight = 0;
			p = ht[p].parent;  //******************如果该点的左右孩子均遍历过，便返回它的双亲结点
			--cdlen;
		}
	}
}


void TranCode(HuffmanTree ht, char a[], char zf[], char b[], int n)
{
	int p = 2*n-1;
	int k = 0; //用于记录已翻译字符个数
	
	for(int i = 0; a[i] != '\0'; ++i)
	{
		if(a[i] == '0')
			p = ht[p].lchild;
		else if(a[i] == '1')
			p = ht[p].rchild;
		if(ht[p].lchild == 0 && ht[p].rchild == 0)
		{
			b[k++] = zf[p];   //注意：如果这里是zf[p]的话，那么在最初给定字符数组zf的时候要从下标为1的开始输入！
			p = 2*n-1;    //这行是加在这个if语句块里的
		}

	}
	b[k] = '\0';
}

int main()
{
	HuffmanTree HT;
	HuffmanCode HC;
	char a[100] = {0}; //待翻译的编码保存在这里面
	char b[100] = {0}; //保存译码后的内容

	int i = 0;
	int n = 0;
	
	printf("输入字符个数：");
	scanf("%d", &n);
	getchar();

	char zf[n+1];  //保存输入的字符数组，从下标1开始
	int w[n+1];    //保存每个字符对应的权值，从下标1开始
	for(i = 1; i <= n; ++i)
	{
		printf("请输入第%d个字符及其对应权值：", i);
		scanf("%c %d", &zf[i], &w[i]);   //scanf输入的值到数组，scanf第二个参数有两种写法: 1) &zf[i] 、 2)zf+i
		getchar();
	}

	CreateHuffmanTree(&HT, w, n);
	printf("\nafter create huffman tree:\n");
	printf("结点\t字符\t权值\t双亲\t左孩子\t右孩子\n");
	for(i = 1; i <= n; ++i)
		printf("%d\t%c\t%d\t%d\t%d\t%d\n", i, zf[i], HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
	for(i = n+1; i <= 2*n-1; ++i)
		printf("%d\t%c\t%d\t%d\t%d\t%d\n", i, '\0', HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);

	CreateHuffmanCode(HT, &HC, n);
	printf("\nafter create huffman code:\n");
	printf("结点\t字符\t权值\t编码\n");
	for(i = 1; i <= n; ++i)
	{
		printf("%d\t%c\t%d\t%s\n", i, zf[i], HT[i].weight, HC[i]);
	}

	printf("\n请输入要译码的编码：");
	scanf("%s", a);
	getchar();

	TranCode(HT, a, zf, b, n);
	printf("after trancode: %s\n", b);

	return 0;
}	

















