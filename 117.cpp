//Populating Next Right Pointers in Each Node II

/*
Follow up for problem "Populating Next Right Pointers in Each Node".

What if the given tree could be any binary tree? Would your previous solution still work?

Note:

You may only use constant extra space.
For example,
Given the following binary tree,
         1
       /  \
      2    3
     / \    \
    4   5    7
After calling your function, the tree should look like:
         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \    \
    4-> 5 -> 7 -> NULL
*/


/*
一个普通的二叉树，将同一层的节点链接
-------------------------------------------------------------------------------------
和之前完全二叉树的条件是想法是差不多的。

但是实现时需要注意两个问题，第一个是在链接同层节点是需要考虑的不光是前后两个节点，如果后面那个节点的左右子树都是空，前面那个节点的子节点肯定不能和后面这个节点的子节点链接。
第二个问题是，如何确定每层的第一个节点的问题

         1
		/ \ 
	   2   3
	      / \
		 4   5
		/    /
	   6    7
以上面的二叉树为例子，如果根节点为第一层，按照之前的思路，可能是head = head->left ? head->left : head->right这么迭代得到下一层的头节点，那碰到上面的第二层之后，就没有头结点，这显然是不对的
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
		TreeLinkNode *level_head = root, *cur, *after, *next;//after表示cur的子节点的后的第一个节点，cur之后有子节点的后继节点
		while(level_head)
		{
			for(cur = level_head; cur;)
			{
				for(next = cur->next; next && !next->left && !next->right; next = next->next);
				after = 0;
				if(next)
					after = next->left ? next->left : next->right;
				if(cur->left)
				{
					if(cur->right)
					{
						cur->left->next = cur->right;
						cur->right->next = after;
					}
					else
						cur->left->next = after;
				}
				else
				{
					if(cur->right)
						cur->right->next = after;
				}
				cur = next;
			}
			while(level_head)//遍历同层中第一个有子节点的节点，更新level_head
			{
				if(level_head->left)
				{
					level_head = level_head->left;
					break;
				}
				if(level_head->right)
				{
					level_head = level_head->right;
					break;
				}
				level_head = level_head->next;
			}
		}
    }
};





/*
上面的代码是在leetcode上测试用例改出来的，感觉有点逻辑不清楚，看了discuss之后对代码进行了改进
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
		TreeLinkNode *head = 0;//每层的第一个节点
		TreeLinkNode *pre = 0;//迭代过程中cur的前一个节点
		TreeLinkNode *cur = root;//迭代每层的节点
		while(cur)
		{
			while(cur)
			{
				if(cur->left)
				{
					if(pre)
						pre->next = cur->left;
					else
						pre = head = cur-> left;
					pre = cur->left;
				}
				if(cur->right)
				{
					if(pre)
						pre->next = cur->right;
					else
						head = cur->right;
					pre = cur->right;
				}
				cur = cur->next;
			}

			cur = head;
			pre = 0;
			head = 0;//防止head得不到更新而有没有退出循环
		}
    }
};










/*
票数最高的代码居然不是最简单的，我感觉这个代码才是本题的最佳代码
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
		TreeLinkNode *head = root, dummy(0), *cur, *pre;
		while(head)
		{
			pre = &dummy;
			for(cur = head; cur; cur = cur->next)
			{
				if(cur->left)
				{
					pre->next = cur->left;
					pre = pre->next;
				}
				if(cur->right)
				{
					pre->next = cur->right;
					pre = pre->next;
				}
			}
			head = dummy.next;
			dummy.next = 0;
		}
    }
};
