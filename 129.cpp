//Sum Root to Leaf Numbers

/*
Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

For example,

    1
   / \
  2   3
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

Return the sum = 12 + 13 = 25.
*/


/*
从根节点到叶节点节点上数字组合成一个数，所有路径组成数的和，和之前的Path Sum II很是类似
----------------------------------------------------------------------------------------------------------------------------------------
代码很简单，直接看代码
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
private:
	//pre_sum 表示之前路径节点上的和
	int recursive(TreeNode *root, int pre_sum)
	{
		if(!root) return 0;
		pre_sum = pre_sum * 10 + root->val;
		if(!root->left && !root->right) return pre_sum;
		return recursive(root->left, pre_sum) + recursive(root->right, pre_sum); 
	}
public:
    int sumNumbers(TreeNode* root) 
	{
		return recursive(root, 0);
    }
};
