
/**************************************二叉平衡树 C源文件*************************************/
//****总结1****：从函数中返回形参是可以的，但要搞清楚这个形参是什么。如果是非指针类型(比如int，char之类的，不能是数组名)，那么可以直接返回没问题；但如果是指针类型(int*,char*,char a[12])的，
//		那么得搞清楚返回时这个指针指向的地址是哪里的内存，如果是外部传进来的内存地址，可以安全返回，但如果指向的地址是栈内的地址，就不能返回，因为离开函数后，栈内存释放了，此时就不能返回！
//		举个例子：如果函数内定义了一个数组 char a[10];那么就不能返回数组名a，因为离开函数后，这个数组的地址就会释放！！！
//总结2:不管是插入结点还是删除结点，都是通过迭代进行的，但是每次插入或删除后都要检查AVL树的平衡性，若不平衡了(即左、右子树的高度差为2)，就要根据情况就行平衡旋转！
//
//总结3:最后树的高度还是取决于插入树结点的顺序，但相对比二叉查找树好多了
//
//

#include "AVL_Tree.h"

#define HEIGHT(p) ( (p==NULL)?0:(((Node*)(p))->height) ) 
#define MAX_VALUE(a, b) ( (a)>(b)?(a):(b) )

static AVLTree delete_node(AVLTree *tree, Node *z);


/****************获取AVL树的高度****************/
int avltree_height(AVLTree tree)
{
	return HEIGHT(tree);
}


/****************前序遍历“AVL树”****************/
void PreOrder_AVLTree(AVLTree tree)
{
	if(tree != NULL)
	{
		printf("%d ", tree->key);
		PreOrder_AVLTree(tree->left);
		PreOrder_AVLTree(tree->right);
	}
}


/****************中序遍历“AVL树”****************/
void InOrder_AVLTree(AVLTree tree)
{
	if(tree != NULL)
	{
		InOrder_AVLTree(tree->left);
		printf("%d ", tree->key);
		InOrder_AVLTree(tree->right);
	}
}


/****************后序遍历“AVL树”****************/
void PostOrder_AVLTree(AVLTree tree)
{
	if(tree != NULL)
	{
		PostOrder_AVLTree(tree->left);
		PostOrder_AVLTree(tree->right);
		printf("%d ", tree->key);
	}
}


/****************打印“AVL树”****************/
void print_avltree(AVLTree Tree, Type key, int direction)
{
	if(Tree != NULL)
	{
		if(direction == 0)  //根结点
		{
			printf("%3d is root.\t\t\theight=%d\n", Tree->key, Tree->height);
		}
		else
		{
			printf("%3d is %3d's %6s child\theight=%d\n", Tree->key, key, direction==-1?"left":"right", Tree->height);
		}
		
		print_avltree(Tree->left, Tree->key, -1);
		print_avltree(Tree->right, Tree->key, 1);
	}
}


/*****查找“AVL树T”中键值为key的结点(递归实现)******/
AVLTree iterative_avltree_search(AVLTree T, Type key)
{
	if(T == NULL || T->key == key)
		return T;

	if(key < T->key)
		return iterative_avltree_search(T->left, key);
	else
		return iterative_avltree_search(T->right, key);
}


/*****查找“AVL树T”中键值为key的结点(非递归实现)*****/
AVLTree avltree_search(AVLTree T, Type key)
{
	while((T != NULL) && (T->key != key))
	{
		if(key < T->key)
			T = T->left;
		else
			T = T->right;
	}

	return T;
}


/*****查找最小结点：返回tree为根结点的AVL树的最小结点*****/
AVLTree avltree_minimum(AVLTree tree)
{
	if(tree == NULL)
		return NULL;

	while(tree->left != NULL)
		tree = tree->left;

	return tree;
}


/*****查找最大结点：返回tree为根结点的AVL树的最大结点*****/
AVLTree avltree_maximum(AVLTree tree)
{
	if(tree == NULL)
		return NULL;

	while(tree->right != NULL)
		tree = tree->right;

	return tree;
}


// LL：左左对应的情况（左单旋转）
// 返回值：旋转后的根节点
//对于LL旋转，你可以这样理解为：LL旋转是围绕"失去平衡的AVL根节点"进行的，也就是节点k2；而且由于是LL情况，即左左情况，就用手抓着"左孩子，即k1"使劲摇。
//			   将k1变成根节点，k2变成k1的右子树，"k1的右子树"变成"k2的左子树"。
static Node *left_left_rotation(AVLTree k2)
{
	Node *k1;

	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;

	k2->height = MAX_VALUE(HEIGHT(k2->left), HEIGHT(k2->right)) + 1;
	k1->height = MAX_VALUE(HEIGHT(k1->left), k2->height) + 1;

	return k1;  //因为这里的k1指向的是已有的内存(即传进来的k2的left)，而不是栈内存，所以可以返回，不会有问题。
}


// RR：右右对应的情况（右单旋转）
// 返回值：旋转后的根节点
static Node *right_right_rotation(AVLTree k1)
{
	Node *k2;

	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;

	k1->height = MAX_VALUE(HEIGHT(k1->left), HEIGHT(k1->right)) + 1;
	k2->height = MAX_VALUE(HEIGHT(k2->right), k1->height) + 1;

	return k2;
}


// LR：左右对应的情况（左双旋转）
// 返回值：旋转后的根节点
// 
// 先对根节点k1的左孩子进行RR旋转，再对根结点LL旋转
static Node *left_right_rotation(AVLTree k1)
{
	k1->left = right_right_rotation(k1->left);
	return left_left_rotation(k1);
}


// RL：右左对应的情况（右双旋转）
// 返回值：旋转后的根节点
//
// 先对根结点k1的右孩子进行LL旋转，再对根节点RR旋转
static Node *right_left_rotation(AVLTree k1)
{
	k1->right = left_left_rotation(k1->right);
	return right_right_rotation(k1);
}


/******创建树结点******/
static Node *avltree_create_node(Type key, Node *left, Node* right)
{
	Node *p;

	if((p = (Node *)malloc(sizeof(Node))) == NULL)
		return NULL;

	p->key = key;
	p->height = 0;
	p->left = left;
	p->right = right;

//	printf("In create node, key:%d\n", p->key);

	return p;
}


/********将结点插入到AVL树中，返回根节点********/
//参数：	  tree:AVL树的根结点   key:插入的结点的键值
//返回值：  AVL树的根节点
AVLTree avltree_insert(AVLTree *tree, Type key)
{
	if((*tree) == NULL)
	{  //新建结点
		*tree = avltree_create_node(key, NULL, NULL);

		if((*tree) == NULL)
		{
			printf("ERROR: create avltree node failed\n");
			return NULL;
		}
//		else
//		{
//			printf("In avltree_insert, key:%d, height:%d\n", (*tree)->key, (*tree)->height);
//		}
	}
	else if(key < (*tree)->key)  //应该将key插入到“tree的左子树”的情况
	{
		(*tree)->left = avltree_insert(&((*tree)->left), key);
		// 插入结点后，若AVL树失去平衡，则进行相应的调节
		if(HEIGHT((*tree)->left) - HEIGHT((*tree)->right) == 2)
		{
			//********好好理解下面这两个if判断********
			if(key < (*tree)->left->key)	//当key比tree左孩子的键值还小时，会插到tree左孩子的左孩子上，自然是左左的情况
				(*tree) = left_left_rotation(*tree);
			else	//当key比tree左孩子的键值还大时，会插到tree左孩子的右孩子上，自然是左右的情况
				(*tree) = left_right_rotation(*tree);
		}
	}
	else if(key > (*tree)->key)  // 应该将key插入到"tree的右子树"的情况
	{
		(*tree)->right = avltree_insert(&((*tree)->right), key);
		// 插入节点后，若AVL树失去平衡，则进行相应的调节。
		if(HEIGHT((*tree)->right) - HEIGHT((*tree)->left) == 2)
		{
			if(key < (*tree)->right->key)
				(*tree) = right_left_rotation((*tree));
			else
				(*tree) = right_right_rotation((*tree));
		}
	}
	else  //key == tree->key
	{
		printf("添加失败：不允许添加相同的结点！\n");
	}

	/**********很重要！！！！***********/
	//这行代码就是在递归中给每个树节点赋予高度值！ 这句代码好好理解！！！ 迭代的思想！！！
	(*tree)->height = MAX_VALUE(HEIGHT((*tree)->left), HEIGHT((*tree)->right)) + 1;
//	printf("tree's height: %d \n", (*tree)->height);

	return (*tree);
}


/********删除结点(key是节点值)，返回根节点********/
//参数： tree:AVL树根节点  key:要删除的结点的键值
AVLTree avltree_delete(AVLTree *tree, Type key)
{
	Node *z;
	if((z = iterative_avltree_search(*tree, key)) != NULL)
		*tree = delete_node(tree, z);
	return *tree;
}

//参数:  AVL:树根节点  z:要删除的结点
static AVLTree delete_node(AVLTree *tree, Node *z)
{
	if((*tree)==NULL || z==NULL)
		return NULL;
	
	if(z->key < (*tree)->key)  // 待删除的节点在"tree的左子树"中
	{
		(*tree)->left = delete_node(&((*tree)->left), z); //所以以根结点的左孩子为根结点迭代删除
		// 删除节点后，若AVL树失去平衡，则进行相应的调节。
		if(HEIGHT((*tree)->right) - HEIGHT((*tree)->left) == 2) //删除左子树结点后，右子树高度比左子树高度大2
		{
			if(HEIGHT((*tree)->right->right) > HEIGHT((*tree)->right->left))
				(*tree) = right_right_rotation((*tree));
			else
				(*tree) = right_left_rotation((*tree));
		}
	}
	else if(z->key > (*tree)->key)  // 待删除的节点在"tree的右子树"中
	{
		(*tree)->right = delete_node(&((*tree)->right), z);
		// 删除节点后，若AVL树失去平衡，则进行相应的调节。
		if(HEIGHT((*tree)->left) - HEIGHT((*tree)->right) == 2) //删除右子树中结点后，左子树高度更高
		{
			if(HEIGHT((*tree)->left->left) > HEIGHT((*tree)->left->right))
				(*tree) = left_left_rotation((*tree));
			else
				(*tree) = left_right_rotation((*tree));
		}
	}
	else  //tree就是要删除的结点
	{
		//tree的左右孩子都非空
		if(((*tree)->left) && ((*tree)->right))
		{
			if(HEIGHT((*tree)->left) > HEIGHT((*tree)->right))		//如果tree的左子树比右子树高；
			{								//则(1)找出tree的左子树中的最大节点 (2)将该最大节点的值赋值给tree (3)删除该最大节点
				Node *max = avltree_maximum((*tree)->left);		//这类似于用"tree的左子树中最大节点"做"tree"的替身；
				(*tree)->key = max->key;				//采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
				(*tree)->left = delete_node(&((*tree)->left), max);
			}
			else
			{								//如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
				Node *min = avltree_minimum((*tree)->right);		//则(1)找出tree的右子树中的最小节点 (2)将该最小节点的值赋值给tree (3)删除该最小节点
				(*tree)->key = min->key;				//这类似于用"tree的右子树中最小节点"做"tree"的替身；
				(*tree)->right = delete_node(&((*tree)->right), min);	//采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
			}
		}
		else
		{  //tree左右孩子不都存在
			//当然，也考虑了左右孩子都不存在的情况！第二行的tree直接等于NULL了，然后tree被free了
			Node *tmp = (*tree);
			(*tree) = ((*tree)->left)?((*tree)->left):((*tree)->right);
			free(tmp);
		}
	}

	//************很关键！！！！当要删除的结点*tree是孩子结点时，上述删除过程完成后，*tree就是NULL了，所以这里要加个判断：“*tree是否为NULL”！
	if(NULL != (*tree)) 
		(*tree)->height = MAX_VALUE(HEIGHT((*tree)->left), HEIGHT((*tree)->right)) + 1;
	return (*tree);
}


/***********销毁AVL树**********/
void destroy_avltree(AVLTree tree)
{
	if(tree == NULL)
		return;
	if(tree->left != NULL)
		destroy_avltree(tree->left);
	else if(tree->right != NULL)
		destroy_avltree(tree->right);

	free(tree);
}


int main(int argc, char *argv[])
{
	AVLTree T = NULL;
	int a, n, key();
	printf("输入结点个数:\n");
	scanf("%d", &n);

	printf("输入结点键值:\n");
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", &a);
		if(!avltree_insert(&T, a))
			printf("Insert error\n");
//		else
//			printf("Here, root's key: %d\n", T->key);
	}
	
	printf("前序遍历:\n");
	PreOrder_AVLTree(T);
	printf("\n");

	printf("中序遍历:\n");
	InOrder_AVLTree(T);
	printf("\n");

	printf("后序遍历:\n");
	PostOrder_AVLTree(T);
	printf("\n\n");
	
	printf("打印AVL树:\n");
	print_avltree(T, 0, 0);
	printf("\n");

	printf("Maximum:%d\nMinimum:%d\n\n", avltree_maximum(T)->key, avltree_minimum(T)->key);	

	while(1)
	{
		printf("输入要删除的结点键值:\n");
		if(scanf("%d", &a) != 1 || a == -1)  //第一个判断条件：判断输入的值是否符合要求是整数
			break;
//		if(a == -1)
//			break;

		T = avltree_delete(&T, a);

		printf("中序遍历:\n");
		InOrder_AVLTree(T);
		printf("\n");
	
		printf("打印AVL树:\n");
		print_avltree(T, 0, 0);
		printf("\n");
	}
	
	destroy_avltree(T);

	return 0;
}













