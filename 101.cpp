//Symmetric Tree

/*
Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3
But the following [1,2,2,null,3,null,3] is not:
    1
   / \
  2   2
   \   \
   3    3
Note:
Bonus points if you could solve it both recursively and iteratively.
*/


/*
判断一颗二叉树是否是对称的
------------------------------------------------------------------------------------------------------------------
递归的解决方案很简单，递归函数的设定就是判断两个树p，q是否对称。p，q对称的条件是，p节点的值等于q节点的值，并且p的左子树和q的右子树是对称的，p的右子树和q的左子树是对称的。最终只要判断给定的树左右子树
是否对称，这个子树就是对称的


非递归的方法是使用两个队列进行层次遍历，队列p从左孩子到右孩子入队，队列q从右孩子到左孩子入队。每次出队时比较元素是否相同
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
	bool symmetric(TreeNode *p, TreeNode *q)
	{
		if(!p && !q) return true;
		if(p && q && p->val == q->val)
			return symmetric(p->left, q->right) && symmetric(p->right, q->left);
		return false;
	}
public:
    bool isSymmetric(TreeNode* root) 
	{
		if(!root) return true;
		return symmetric(root->left, root->right);
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
    bool isSymmetric(TreeNode* root) 
	{
		queue<TreeNode *> p, q;
		TreeNode *p_cur, *q_cur;
		if(!root) return true;
		p.push(root->left);//不管是不是空的都入队列，防止元素的值相同，但是位置不对称的情况
		q.push(root->right);
		while(!p.empty() && !q.empty())
		{
			p_cur = p.front(), q_cur = q.front();
			p.pop(), q.pop();
			if(!p_cur && !q_cur) continue;
			if(!p_cur || !q_cur) return false;
			if(p_cur->val != q_cur->val) return false;

			p.push(p_cur->left);
			p.push(p_cur->right);
			q.push(q_cur->right);
			q.push(q_cur->left);
		}
		return true;
    }
};
