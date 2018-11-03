/********************************二叉树重建**********************************/
//已知: 前序遍历、中序遍历树的结点顺序
//欲求: 重新建立二叉树
//以下只包含关键代码


/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
	TreeNode *reConstructBinaryTree(vector<int> pre,vector<int> vin) {
		TreeNode *root = reConstructBinaryTree(pre, 0, pre.size()-1, vin, 0, vin.size()-1);
		return root;
	}
private:
	TreeNode *reConstructBinaryTree(vector<int> Pre, int startPre, int endPre, vector<int> In, int startIn, int endIn)
	{						//startPre:前序遍历中的起点、 endPre:前序遍历中的终点、 startIn:中序遍历中的起点、 endIn:中序遍历中的终点
		if(startPre > endPre || startIn > endIn)
			return NULL;
		int i;

		TreeNode *T = new TreeNode(Pre[startPre]);

		for(i = startIn; i <= endIn; ++i)
		{
			if(In(i) == Pre[startPre])  //找到中序遍历中与前序遍历中第一个结点相等的那个点，该点左边的结点是左子树、右边的结点是右子树。  
			{			    //  i-startIn:左子树结点个数， endIn-i:右子树结点个数
				//对中序遍历中第i个结点左边的结点(左子树)递归进行求解，这时传进去的startPre、endPre与startIn、endIn分别代表前序遍历、中序遍历中要递归求解的左子树的结点
				T->left = reConstructBinaryTree(Pre, startPre+1, startPre+i-startIn, In, startIn, i-1);  
				
				T->right = reConstructBinaryTree(Pre, startPre+i-startIn+1, endPre, In, i+1, endIn);
			}
		}
		return T;
	}
}










