//Unique Binary Search Trees II 


/*
Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
*/


/*
题目的意思是给定一个整数n，然后让你构造所有可能的二叉搜索树来存储[1,n]共n个树
-------------------------------------------------------------------------------------------------------------
一共有两种方法:
1. 利用前面说的枚举每个数作为根节点，然后递归构造左子树和右子树。具体来说就是使用递归，递归函数的定义参数的定义比较简单vector<TreeNode *> f(int lower, int upper)。
这个返回的vector就是以[lower，upper]为数字的所有BST的根节点的集合，所以我们只要在f函数体中枚举根节点的编号i,然后递归调用left = f(lower, i - 1), right = f(i + 1, upper)，最后将left和right的所有
子树组合

2.我感觉明显第一种方法有个缺点就是要利用很多vector对象，空间的消耗有点惊人，所以discuss里面有人提出了第二种方法。第二种方法看起来复杂，其实也额还算简单。
基本的思想就是通过构造[1, n-1]的BST,能够的到[1, n]的BST，基本情况只有两种

1) 第n个节点作为根节点，那么 newroot->left = oldroot(这里的意思就是作为一个BST，n号节点是跟节点，那么其他所有节点的数字都小于n，所以旧的BST只能挂在n号节点的左边来构成包含n个节点的BST)

2) 第n个节点不是根节点，那么同样根据BST的性质，这个n号节点只能挂在[1,n-1]节点的右子节点。所以遍历老的BST，每次老的BST中有一个右孩子我们就执行:old node->right = nth node, nth node->left = right child;
当到达老BST的末端不要忘记第n号节点但可以加在这个地方。还有一个地方学要注意的，每次把一个TreeNode放到结果集中，都是放入的一个拷贝版本，并且都会马上回复老的BST，这个老的BST可能不止使用一次
*/

/*
方法二的英文原文
The basic idea is that we can construct the result of n node tree just from the result of n-1 node tree.
Here's how we do it: only 2 conditions: 
1) The nth node is the new root, so newroot->left = oldroot

2) the nth node is not root, we traverse the old tree, every time the node in the old tree has a right child, we can perform: old node->right = nth node, nth node ->left = right child;
and when we reach the end of the tree, don't forget we can also add the nth node here. One thing to notice is that every time we push a TreeNode in our result, I push the clone version of the root,
and I recover what I do to the old node immediately. This is because you may use the old tree for several times.
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
//方法1的实现 16ms
class Solution 
{
private:
	vector<TreeNode *> recursive(int lower, int upper)
	{
		int i, j, k;
		TreeNode *root;
		vector<TreeNode *> left(0), right(0), ans;
		if(lower > upper)
		{
			ans.push_back(0);
			return ans;
		}
		for(i = lower; i <= upper; ++i)
		{
			left = recursive(lower, i - 1);
			right = recursive(i + 1, upper);
			for(j = 0; j < left.size(); ++j)
			{
				for(k = 0; k < right.size(); ++k)
				{
					root = new TreeNode(i);
					root->left = left[j], root->right = right[k];
					ans.push_back(root);
				}
			}
		}
		return ans;
	}
public:
    vector<TreeNode*> generateTrees(int n) 
	{
		vector<TreeNode *> v;
		if(n <= 0) return v;//这组测试用例很魔性，应该返回一个空集合，而不是有一个空节点的集合
		return recursive(1, n);
    }
};

//方法2的实现 19ms好像更慢了
class Solution 
{
private:
	//深拷贝一个树
	TreeNode * deep_copy(TreeNode * root)
	{
		TreeNode *tmp;
		if(!root) return 0;
		tmp = new TreeNode(root->val);
		tmp->left = deep_copy(root->left);
		tmp->right = deep_copy(root->right);
		return tmp;
	}
public:
    vector<TreeNode*> generateTrees(int n) 
	{
		int i, j, len;
		TreeNode *old_tree, *new_node, node(0), *p, *root, *p_right;
		vector<TreeNode *> ans, tmp;
		if(n <= 0) return ans;
		ans.push_back(new TreeNode(1));

		new_node = &node;
		for(i = 2; i <= n; ++i)
		{
			tmp.assign(ans.begin(), ans.end());
			ans.clear();
			len = tmp.size();
			for(j = 0; j < len; ++j)
			{
				old_tree = tmp[j];
				new_node->val = i;

				//新的i号节点作为根节点
				new_node->left = old_tree;
				root = deep_copy(new_node);
				ans.push_back(root);

				//新的i号节点作为old_tree中的右子节点
				for(p = old_tree; p;)
				{
					//在old_tree中插入新节点
					p_right  = p->right;
					p->right = new_node;
					new_node->left = p_right;

					root = deep_copy(old_tree);
					ans.push_back(root);

					p->right = p_right;//还原old_tree
					p = p->right;//继续遍历右节点
				}
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
/*
注释掉的原因是这个代码有错误，错误就在于多个子树共用了一个根节点，真是伤心，一动手居然还错了
class Solution 
{
public:
    vector<TreeNode*> generateTrees(int n) 
	{
		vector<TreeNode *> a_tree;
		vector<TreeNode *> trees;
		TreeNode *tmp;
		recursive(trees, 1, n, n, a_tree, tmp);
		return trees;
    }

	void recursive(vector<TreeNode *> &trees, int bound, int upper, int n, vector<TreeNode *> &a_tree, TreeNode *&parent)
	{
		int i;
		TreeNode *root;
		for(i = bound; i<= upper; ++i)
		{
			root = new TreeNode(i);
			parent = root;
			a_tree.push_back(root);

			recursive(trees, bound, i - 1, n, a_tree, root->left);
			recursive(trees, i + 1, upper, n, a_tree, root->right);

			if(a_tree.size() == n)
			{
				trees.push_back(a_tree[0]);
				return;
			}
			a_tree.pop_back();
		}
	}
};
*/
