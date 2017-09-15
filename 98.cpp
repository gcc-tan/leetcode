//Validate Binary Search Tree

/*
Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

1. The left subtree of a node contains only nodes with keys less than the node's key.
2. The right subtree of a node contains only nodes with keys greater than the node's key.
3. Both the left and right subtrees must also be binary search trees.
Example 1:
    2
   / \
  1   3
Binary tree [2,1,3], return true.
Example 2:
    1
   / \
  2   3
Binary tree [1,2,3], return false.
*/


/*
判断一个二叉树是否是合法的二叉搜索树
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
/*
根据二叉搜索树的定义，中序遍历的结果就是一个有序的列表。所以只要中序遍历判断是否是有序的就行。可以采用递归和非递归的方式遍历
*/
class Solution 
{
public:
    bool isValidBST(TreeNode* root) 
	{
		TreeNode *pre = 0;
		return validate(root, &pre);
    }
	bool validate(TreeNode *root, TreeNode **pre)
	{
		if(!root) return true;
		if(!validate(root->left, pre)) return false;
		if(*pre && (*pre)->val >= root->val) return false;
		*pre = root;
		return validate(root->right, pre);
	}
};
