//Binary Tree Preorder Traversal

/*
Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
	\
	 2
	/
   3
return [1,2,3].

Note: Recursive solution is trivial, could you do it iteratively
*/

/*
二叉树的前序遍历，写法有很多种，反正都是先向左遍历，左为空弹栈...
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
    vector<int> preorderTraversal(TreeNode* root) 
	{
		stack<TreeNode *> st;
		TreeNode *cur = root;
		vector<int> ans;
		while(cur || st.size())
		{
			if(cur)
			{
				ans.push_back(cur->val);
				st.push(cur);
				cur = cur->left;
			}
			else
			{
				cur = st.top();
				st.pop();
				cur = cur->right;
			}
		}
		return ans;
    }
};






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
    vector<int> preorderTraversal(TreeNode* root) 
	{
		TreeNode *cur = root;
		stack<TreeNode *> st;
		vector<int> ans;
		while(cur)
		{
			ans.push_back(cur->val);
			if(cur->right)
				st.push(cur->right);
			cur = cur->left;
			if(!cur && !st.empty())
			{
				cur = st.top();
				st.pop();
			}
		}
		return ans;
    }
};















/*
不太明白，在提交的代码中为什么这个代码最快，我把代码贴上发现速度和之前写的两个一样........都是3ms
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
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        if (!root) {
            return result;
        }
        stack<TreeNode*> stk;
        stk.push(root);
        while (stk.size()) {
            auto cur = stk.top();
            stk.pop();
            result.push_back(cur->val);
            if (cur->right) {
                stk.push(cur->right);
            }
            if (cur->left) {
                stk.push(cur->left);
            }
        }
        return result;
    }
};
