//Same Tree




/*
Given two binary trees, write a function to check if they are equal or not.

Two binary trees are considered equal if they are structurally identical and the nodes have the same value.
*/


/*
判断两个二叉树是否是一样，使用递归很简单，就是二叉树的遍历判断
*/


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution 
{
public:
    bool isSameTree(TreeNode* p, TreeNode* q) 
	{
		if(!p && !q) return true;//p，q都为空
		if(p && q && p->val == q->val)//p，q都不为空，且值相同，再对子树进行判断
			return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);

		return false;
    }
};
