//Flatten Binary Tree to Linked List

/*
Given a binary tree, flatten it to a linked list in-place.

For example,
Given

         1
        / \
       2   5
      / \   \
     3   4   6
The flattened(扁平化) tree should look like:
   1
    \
     2
      \
       3
        \
         4
          \
           5
            \
             6
If you notice carefully in the flattened tree, each node's right child points to the next node of a pre-order traversal.
*/

/*
将一个二叉树扁平化，扁平化之后的二叉树的右子节点是前序遍历的下一个节点
---------------------------------------------------------------------------------------------------------------------
就是一个二叉树的前序遍历，要注意将左孩子的指针域清零，不然会影响二叉树的结构
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
    void flatten(TreeNode* root) 
	{
		stack<TreeNode *> st;
		TreeNode dummy(0), *tail = &dummy, *cur = root;//tail扁平二叉树最右侧的节点
		while(cur || !st.empty())
		{
			if(cur)
			{
				tail->left = 0;
				tail->right = cur;
				tail = tail->right;
				if(cur->right) st.push(cur->right);
				cur = cur->left;
			}
			else
			{
				cur = st.top();
				st.pop();
			}
		}
    }
};








/*
discuss里面最高票的答案(java代码)，很是让人震惊
这是一个递归的访问，从递归的方程中可以看出来是右左根的顺序，这个是先序遍历根左右的反序(之所以不使用先序遍历直接访问，因为在构建这个扁平化二叉树时会破坏访问结构)

          1
		/   \
	   2     3

上面的这颗二叉树使用这个顺序遍历的结果是321，然后就是使用类似于头插法(反序)建立链表的方法建立符合要求的扁平化二叉树
*/

private TreeNode prev = null;

public void flatten(TreeNode root) {
    if (root == null)
        return;
    flatten(root.right);
    flatten(root.left);
    root.right = prev;
    root.left = null;
    prev = root;
}

/*
O(1)的空间复杂度，可以画个图体会一下代码，大概流程就是从根节now开始遍历，每次找到now->right的前驱节点，然后找到节点右子指针指向now->right，然后将now节点的右指针指向now->left，now->left = 0
指针向原来的左子树移动
*/
class Solution 
{
public:
    void flatten(TreeNode *root) 
	{
		TreeNode*now = root;
		while (now)
		{
			if(now->left)
			{
                //Find current node's prenode that links to current node's right subtree
				TreeNode* pre = now->left;//找当前节点右子节点的先序遍历的前驱节点
				while(pre->right)
				{
					pre = pre->right;
				}
				pre->right = now->right;
                //Use current node's left subtree to replace its right subtree(original right 
                //subtree is already linked by current node's prenode
				now->right = now->left;
				now->left = NULL;
			}
			now = now->right;
		}
    }
};
