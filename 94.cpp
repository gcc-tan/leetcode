//Binary Tree Inoder Traversal


/*
Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree [1,null,2,3],
   1
    \
     2
    /
   3
return [1,3,2].

Note: Recursive solution is trivial(微不足道), could you do it iteratively?
*/


/*
二叉树的中序遍历，要求使用非递归的实现。
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
直接看文档中有介绍
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
    vector<int> inorderTraversal(TreeNode* root) 
	{
		stack<TreeNode *> st;
		vector<int> ans;
		while(root || !st.empty())
		{
			if(root)
			{
				st.push(root);
				root = root->left;
			}
			else
			{
				root = st.top();
				st.pop();
				ans.push_back(root->val);
				root = root->right;
			}
		}
		return ans;
    }
};
