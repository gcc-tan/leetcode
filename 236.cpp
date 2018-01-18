/*
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”

        _______3______
       /              \
    ___5__          ___1__
   /      \        /      \
   6      _2       0       8
         /  \
         7   4
For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
*/

/*
题目的很明确，就是最小公共祖先的问题(lca)
------------------------------------------------------------------------------------------------------------------------------------------------------
1. 对于这个问题，很直接的方法是找到一条从根结点到结点p的路径和从根结点到结点q的路径。两条路径中最长前缀的最后一个结点就是p与q的lca

2. 第二种算法能够运行的条件是给出的结点p, q都在树的结点中。主要的思路是基于这样的一个考虑。假设当前的子树是以root为根结点的。如果p, q都在左子树，那么计算lca(root->left)；如果p，q都在右子树，
计算lca(root->right)。如果p,q一个在左，一个在右，那么返回root。思路比较简单，关键代码有点小技巧

3. 利用Tarjan的脱机最小公共祖先算法。这个算法能够高效地查找多对结点的lca。
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
	{
		TreeNode *left, *right;
		if (!root || root == p || root == q)
			return root;
		left = lowestCommonAncestor(root->left, p, q);
		right = lowestCommonAncestor(root->right, p, q);
		if (left == NULL)
			return right;
		else if (right == NULL)
			return left;
		return root;
	}
};

template<class T> 
class union_find_set
{
private:
	struct element
	{
		T data;//元素标志，在集合中应该唯一
		int rank;//秩
		T p;//父元素
		element() {}
		element(T a_data, int a_rank, T a_p) : data(a_data), rank(a_rank) , p(a_p) {}
	};
	unordered_map<T , element> map;//将输入的标志与元素一一对应
public:
	//创建集合
	void make_set(T x)
	{
		element e(x, 0, x);
		map[x] = e;
	}

	//返回集合中的代表
	T find_set(T x)
	{
		if (x != map[x].p)
			map[x].p = find_set(map[x].p);
		return map[x].p;
	}

	//合并两个集合
	void union_set(T x, T y)
	{
		T rx = find_set(x), ry = find_set(y);
		if (map[rx].rank > map[ry].rank)
			map[ry].p = rx;
		else
		{
			map[rx].p = ry;
			if (map[rx].rank == map[ry].rank)
				++map[ry].rank;
		}
	}

	void clear()
	{
		map.clear();
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
//在执行大的测试用例时runtime error，估计限制了内存的使用
class Solution 
{
private:
	unordered_map<TreeNode *, int> visit;
	unordered_map<TreeNode *, TreeNode *> parent;//parent[x]表示结点x的祖先结点
	union_find_set<TreeNode *> ufs;
	TreeNode *p;
	TreeNode *q;
	TreeNode *ans;
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
	{
		this->p = p;
		this->q = q;
		this->ans = NULL;
		visit.clear();
		parent.clear();
		ufs.clear();
		lca(root);
		return ans;
    }
	
	void lca(TreeNode *root)
	{
		ufs.make_set(root);
		this->parent[ufs.find_set(root)] = root;

		if (root->left)
		{
			lca(root->left);
			ufs.union_set(root, root->left);
			this->parent[ufs.find_set(root)] = root;
		}
		if (root->right)
		{
			lca(root->right);
			ufs.union_set(root, root->right);
			this->parent[ufs.find_set(root)] = root;
		}

		visit[root] = 1;

		//开始询问点集P
		if (root == p || visit.count(q))
			this->ans = this->parent[ufs.find_set(q)];
		else if (root == q && visit.count(p))
			this->ans = this->parent[ufs.find_set(p)];
	}
};
