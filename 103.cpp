//Binary Tree Zigzag Level Order Traversal


/*
Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its zigzag level order traversal as:
[
  [3],
  [20,9],
  [15,7]
]
*/


/*
二叉树按层蛇形遍历
-------------------------------------
和之前的Binary Tree Level Order Traversal一样，进行层次遍历，不过在填充当前层的值时偶数层从左至右，奇数层从右至左填充
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) 
	{
		vector<vector<int>> ans;
		queue<TreeNode *> q;
		TreeNode *cur;
		int i, n, level = 0, pos;
		if(!root) return ans;
		q.push(root);
		while(!q.empty())
		{
			n = q.size();
			vector<int> v(n);
			for(i = 0; i < n; ++i)
			{
				cur = q.front();
				q.pop();
				pos = (level % 2) == 0 ? i : n - i - 1;
				v[pos] = cur->val;
				if(cur->left)  q.push(cur->left);
				if(cur->right) q.push(cur->right);
			}
			ans.push_back(v);
			++level;
		}
		return ans;
    }
};
