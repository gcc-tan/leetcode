//Binary Tree Maximum Path Sum

/*
Given a binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path must contain at least one node and does not need to go through the root.

For example:
Given the below binary tree,

       1
      / \
     2   3
Return 6.
*/


/*
二叉树和最大的路径，路径的最小长度为1，开始点和结束点的位置可以是任意的
------------------------------------------------------------------------------------------------------------------------
思路就是不管路径是什么，反正这个路径肯定是有一个最高点(根节点)，以某个节点为根节点的路径的最大值有三种情况
1. 包含左子树为根的路径最大值加上当前节点
2. 包含右子树为根的路径最大值加上当前节点
3. 横跨两个子树，然后加上当前节点

最后用一个全局的值记录每个节点为根的路径值中最大的一个
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
	int sum;
	//cur_max返回以root为顶点的不横跨左右的最大路径，这样保证路径合法.
	//max_sum返回包括root的最大路径
	int max_sum(TreeNode *root)
	{
		int l, r;
		if(!root) return 0;
		l = max_sum(root->left);
		r = max_sum(root->right);
		cur_max = max(max(l + root->val, r + root->val), root->val);
		sum = max(max(cur_max, r + l + root->val), sum); // sum计算利用cur_max，r + l + root->val这以root为顶点，包含左右子树的路径
		return cur_max;
	}
public:
    int maxPathSum(TreeNode* root) 
	{
		sum = INT_MIN;
		max_sum(root);
		return sum;
    }
};


/*
思路都差不多，也可以看看
*/
public class Solution {
    int maxValue;
    
    public int maxPathSum(TreeNode root) {
        maxValue = Integer.MIN_VALUE;
        maxPathDown(root);
        return maxValue;
    }
    
    private int maxPathDown(TreeNode node) {
        if (node == null) return 0;
        int left = Math.max(0, maxPathDown(node.left));
        int right = Math.max(0, maxPathDown(node.right));
        maxValue = Math.max(maxValue, left + right + node.val);
        return Math.max(left, right) + node.val;
    }
}
