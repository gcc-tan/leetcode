//Populating Next Right Pointers in Each Node

/*
Given a binary tree

    struct TreeLinkNode {
      TreeLinkNode *left;
      TreeLinkNode *right;
      TreeLinkNode *next;
    }
Populate(填充) each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

You may only use constant extra space.
You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
For example,
Given the following perfect binary tree,
         1
       /  \
      2    3
     / \  / \
    4  5  6  7
After calling your function, the tree should look like:
         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL
*/

/*
有一颗完全二叉树，要求使用常量的空间，将这个完全二叉树的同层节点用指针链接起来
-------------------------------------------------------------------------------------------------------
我们可以利用好这个每层的next指针域来辅助进行二叉树的遍历，在上层构建好下层的next指针域，然后向下层移动，利用本层next指针迭代构造下层的next指针
*/


/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution 
{
public:
    void connect(TreeLinkNode *root) 
	{
		TreeLinkNode *level_head = root, *cur;
		if(!root) return;
		while(level_head->left)//最后一层终止
		{
			for(cur = level_head; cur; cur = cur->next)//遍历本层的next指针，构造下层的next指针
			{
				cur->left->next = cur->right;
				if(cur->next)
					cur->right->next = cur->next->left;
			}
			level_head = level_head->left;
		}
    }
};
