
/**************************************二叉平衡树 C头文件*************************************/
#include <stdio.h>
#include <stdlib.h>


typedef int Type;

typedef struct AVLTreeNode{
	Type key;    			//键值
	int height;  			//树节点高度
	struct AVLTreeNode *left;	//左孩子
	struct AVLTreeNode *right;	//右孩子
}Node, *AVLTree;

int avltree_height(AVLTree tree); //获取AVL树的高度

void PreOrder_AVLTree(AVLTree tree); //前序遍历“AVL树”
void InOrder_AVLTree(AVLTree tree); //中序遍历“AVL树”
void PostOrder_AVLTree(AVLTree tree); //后序遍历“AVL树”

void print_avltree(AVLTree Tree, Type key, int direction);

AVLTree iterative_avltree_search(AVLTree T, Type key); //查找“AVL树T”中键值为key的结点(递归实现)

AVLTree avltree_search(AVLTree T, Type key); //查找“AVL树T”中键值为key的结点(非递归实现)

AVLTree avltree_minimum(AVLTree tree); //查找最小结点：返回tree为根结点的AVL树的最小结点。
AVLTree avltree_maximum(AVLTree tree); //查找最大结点：返回tree为根结点的AVL树的最大结点。

AVLTree avltree_insert(AVLTree *tree, Type key); //将结点插入到AVL树中，返回根节点

AVLTree avltree_delete(AVLTree *tree, Type key); //删除结点(key是节点值)，返回根节点

void destroy_avltree(AVLTree tree); //销毁AVL树












