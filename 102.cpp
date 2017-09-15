//Binary Tree Level Order Traversal 

/*
Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]
*/

/*
二叉树的层次遍历
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
    vector<vector<int>> levelOrder(TreeNode* root) 
	{
		vector<vector<int>> ans;
		queue<TreeNode *> q;
		TreeNode *cur;
		int n, i;
		if(!root) return ans;
		q.push(root);
		while(!q.empty())
		{
			n = q.size();
			vector<int> v;
			for(i = 0; i < n; ++i)
			{
				cur = q.front();
				if(cur->left) q.push(cur->left);
				if(cur->right) q.push(cur->right);
				v.push_back(cur->val);
				q.pop();
			}
			ans.push_back(v);
		}
		return ans;
    }
};



//递归的写法，很有灵性
vector<vector<int>> ret;
void buildVector(TreeNode *root, int depth)
{
    if(root == NULL) return;
    if(ret.size() == depth)
        ret.push_back(vector<int>());
    
    ret[depth].push_back(root->val);
    buildVector(root->left, depth + 1);
    buildVector(root->right, depth + 1);
}
vector<vector<int> > levelOrder(TreeNode *root) {
    buildVector(root, 0);
    return ret;
}
