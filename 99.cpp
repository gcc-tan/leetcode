//Recover Binary Search Tree

/*
Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.
Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution
*/



/*
一个合法的二叉搜索树两个节点的值被交换了，要求恢复在这个二叉搜索树，并且使用O(1)的时间复杂度
--------------------------------------------------------------------------------------------------------------------------------------------------
假设这个二叉搜索树的中序遍历的结果是1, 2, 3, 4, 5。那么交换其中的任意两个节点1, 3。所得的结果是3, 2, 1, 4, 5。从这个结果中我们怎么发现这两个元素是被交换的？
从左向右，第一个被交换的元素是大于其身后的元素，第二个被交换的元素是小于其前面的元素。只要首先找到这两个元素就行。使用的方法还是中序遍历
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
//额好像忘了O(1)的时间复杂度了，使用了非递归的遍历，可以使用中序遍历递归访时插入更新first和second的代码，最后交换first和second值
class Solution 
{
public:
    void recoverTree(TreeNode* root) 
	{
		TreeNode *pre = 0, *first = 0, *second = 0;
		stack<TreeNode *> st;
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
				//中序遍历访问root值
				if(pre && pre->val > root->val)
				{
					if(!first)//第一个找到的不符合的节点赋值给first
						first = pre;
					second = root;
				}
				pre = root;
				root = root->right;
			}
		}
		swap(first->val, second->val);
    }
};

//还有采用非递归的方式，但是是常量的空间复杂度，使用了Morris遍历二叉树



