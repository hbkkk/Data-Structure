/***************************************************线索二叉树***************************************************/
//线索二叉树代码
//	创建二叉树：记得创建每个结点时给左右标志域rtag、ltag赋值
//	中序线索化二叉树：跟中序遍历一样，只不过把打印那行换成线索化
//	新增头结点：增加一个头结点，提前把它右链(即后继)设为自己、标识符设为线索，然后左链设为头结点、标志域置Link，
//		  然后开始线索化，结束线索化后记得把pre(此时为中序遍历中最后一个结点)的后继指向头结点、标志域置Thread，
//		  同时把头结点的右链(即后继)指向中序遍历中最后一个结点(即此时的pre)
/******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef enum {Link, Thread}PointerTag;  //！！！注： 不能写成:typedef enum PointerTag {..};这种形式

typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild;   //左孩子、前驱(ltag为1时)
	struct BiTNode *rchild;   //右孩子、后继(rtag为1时)
	PointerTag ltag;
	PointerTag rtag;
}BiTNode, *BiTree;

BiTree pre; //全局变量，前一个结点

void CreateTree(BiTree *t);  //前序建立二叉树
int InOrderThraverse_Thr(BiTree t); //中序遍历线索化的二叉树，t指向头结点，其左链指向根节点、右链指向中序遍历中最后一个结点
void InThreading(BiTree p); //中序遍历进行中序线索化二叉树
int InOrderThread_Head(BiTree *h, BiTree t); //建立头结点，并中序线索化二叉树
void InOrder(BiTree p);


void CreateTree(BiTree *t)
{
	char ch;
	scanf("%c", &ch);
	getchar();   //清除输入流中的\n

	if(ch == '#')
		*t = NULL;
	else
	{
		(*t) = (BiTree)malloc(sizeof(BiTNode));   //反了兄嘚！！！sizeof()里的应该是BiTNode,malloc返回结果应该强制转换为BiTree(指针！！)
		if(NULL == *t)
		{
			printf("malloc error\n");
			exit(1);
		}
		(*t)->data = ch;
		(*t)->ltag = (*t)->rtag = Link;   //提前定义好两个标志域，很重要 ***************************************
		CreateTree(&(*t)->lchild);
		CreateTree(&(*t)->rchild);		
	}
}


void InThreading(BiTree p)  //这个p是根结点       //这个函数有问题！。。。找到问题了 就是最外面要加个判断p是否为NULL的判断条件=。=
{
	if(p)  //这句话不能忘！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	{
//		printf("777: %c\n",p->data);
		InThreading(p->lchild);

		//==                      ***********************************  星号这段代替了原来中序遍历时的打印语句
		if(NULL == p->lchild)   //表示如果某结点的左指针域为空，因为其前驱结点刚刚访问过，赋值了pre，所以可以将pre赋值给p->lchild，
		{			//并修改p->ltag = Thread（也就是定义为1）以完成前驱结点的线索化。
			p->ltag = Thread;
			p->lchild = pre;
		}
		if(NULL == pre->rchild)  //因为此时p结点的后继还没有访问到，因此只能对它的前驱结点pre的右指针rchild做判断
		{			//表示如果为空，则p就是pre的后继，于是pre->rchild = p，并且设置pre->rtag = Thread，完成后继结点的线索化。
			pre->rtag = Thread;
			pre->rchild = p;
		}
		pre = p;
//		printf("pre->data: %c\n", pre->data);
		//==                      ***********************************

		InThreading(p->rchild);
	}
}


int InOrderThread_Head(BiTree *h, BiTree t)   //创建头结点，并中序化  //1、头结点左链指向根结点
{								  //2、头结点右链指向中序遍历中最后一个结点
	(*h) = (BiTree)malloc(sizeof(BiTNode));			  //3、中序遍历中第一个结点的左链(即前驱)指向头结点
								  //4、中序遍历中最后一个结点的右链(即后继)指向头结点
	if(NULL == (*h))
	{
		printf("malloc error\n");
		return -1;
	}
	(*h)->rtag = Thread;   
	(*h)->rchild = *h;   //先让头结点的右链指向自己，为了之后线索化时第一次判断pre->rchild时结果为假，因为之后会先让pre=*h

	if(NULL == t)
	{
		(*h)->ltag = Thread;
		(*h)->lchild = *h;
	}
	else
	{
		pre = *h;
		(*h)->ltag = Link;
		(*h)->lchild = t;   //让头结点的左链指向根结点
		InThreading(t);   //结束后，pre为中序遍历中最后一个结点

		pre->rchild = *h;   //这两行是把中序遍历中最后一个结点的右链补上！！！！别忘了!!!!!!!!!!!!!!!!!!!!!!!!
		pre->rtag = Thread;

		(*h)->rchild = pre;   //头结点的右链指向中序遍历中最后一个结点，即这里的pre
	}

	return 0;
}


void InOrder(BiTree p)
{
	if(NULL == p)
		return;
	InOrder(p->lchild);
	printf("%c ", p->data);
//	printf("ltag:%d、rtag:%d   ", p->ltag, p->rtag);
	InOrder(p->rchild);
}


int InOrderThraverse_Thr(BiTree t)   //中序遍历线索化后的二叉树，  传进来的t是头结点
{
	BiTree p = t->lchild;   //让p指向根结点开始遍历
	
	while(p != t)  //循环直到p指向头结点，否则一直循环下去进行遍历操作
	{
		while(p->ltag == Link)  //首先遍历到左子树最后一个叶子结点(中序遍历)
		{
			p = p->lchild;
		}

		printf("%c ", p->data);  //中序遍历的递归中先打印左子树的最后一个叶子结点

		while(p->rtag == Thread && p->rchild != t)  //******************这里好好理解！！！！********************
		//其实这里如果条件成立进入循环，就意味着左子树最后一个结点的右标志域是Thread，代表有后继，
		//这样打印的右链就是p的后继结点，即中序遍历递归中第二个遍历的是左子树的根结点。一直循环到p的右标志域
		//是Link(或右链为头结点为止)，此时就跳出循环让p等于它的右链，然后继续第二次递归(左子树→根节点→右子树)
		{
			p = p->rchild;
			printf("%c ", p->data);  //一直打印p结点的后继，因为此时的二叉树是线索化好的，所以可以直接用后继进行打印
		}
		
		p = p->rchild;  //当p的右标识符是Link的时候，让p等于它的右链，然后继续循环下去，然后返回上面的第一个打印p->data，
	}			//这时候实际上打印的是递归中第二个，即打印根节点

	return 0;
}

int main()
{
	BiTree p;
	BiTree phead;

	CreateTree(&p);
	printf("\nInOrder:\n");
	InOrder(p);
	printf("\n\n");
	InOrderThread_Head(&phead, p);
	printf("InOrder_Thread:\n");
	InOrderThraverse_Thr(phead);
	printf("\n");

	return 0;	
}

