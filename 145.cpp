//Binary Tree Postorder Traversal

/*
Given a binary tree, return the postorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3
return [3,2,1].

Note: Recursive solution is trivial, could you do it iteratively?
*/

/*
二叉树的后续遍历
----------------------------------------------------------------------------------------
只有在访问完左右子树才能弹栈，所以需要用变量记录之前访问的节点，判断该节点的右子树是否被访问
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
    vector<int> postorderTraversal(TreeNode* root) 
	{
		stack<TreeNode *> st;
		TreeNode *pre = 0, *cur = root;
		vector<int> ans;
		while(cur || st.size())
		{
			if(cur)
			{
				st.push(cur);
				cur = cur->left;
			}
			else if(st.top()->right != pre)
			{
				cur = st.top()->right;
				pre = 0;
			}
			else
			{
				pre = st.top();
				st.pop();
				ans.push_back(pre->val);
			}
		}
		return ans;
    }
};


/*
discuss里面的答案，也算是个人才，将遍历顺序颠倒，将vector也颠倒，结果就是正确的
*/
class Solution {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        stack<TreeNode*> nodeStack;
        vector<int> result;
        //base case
        if(root==NULL)
            return result;
        nodeStack.push(root);
        while(!nodeStack.empty())
        {
            TreeNode* node= nodeStack.top();  
            result.push_back(node->val);
            nodeStack.pop();
            if(node->left)
                nodeStack.push(node->left);
            if(node->right)
                nodeStack.push(node->right);
        }
        reverse(result.begin(),result.end());
        return result;
        
    }
};
