//Unique Binary Search Trees


/*

Given n, how many structurally unique BST's (binary search trees) that store values 1...n?

For example,
Given n = 3, there are a total of 5 unique BST's.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

*/



/*
题目的意思很清晰，就是问给定一个数字n，有多少中不同形态的二叉搜索树来存储数字1~n
------------------------------------------------------------------------------------------------------------------------
瞬间感觉额无从下手，放弃直接看discuss。

大多数的时候看discuss都是有一种震惊的感觉，现在都有一种感觉，代码写得多并不是基本功不好，大多数情况下是思维不清楚，或者没有想到简洁的办法

作者的解释非常清楚，首先必须要知道的是如何构造一个BST，例如给定一个输入的序列[1, ..., n]怎么构造一个不重复的BST。正确的方法枚举集合中的每个数字i当作根节点，[1,i-1]的数字放在根节点的左边，
[i+1,n]放到根节点的右边，然后可以用这些子序列递归地构造子树。通过上面的方法我们可以保证构造一个不重复的二叉搜索树

知道了上面的知识之后可以进一步地解决要求的问题。为了解决这个问题，先定义两个函数
G(n): 代表利用n个数组构造的不同的BST的个数
F(i, n):  1<= i <= n 表示i号数字是根节点时不同的BST的个数

因此只要求出了G(n)问题就解决了

而G(n) = F(1, n) + F(2, n) + ... + F(n, n)，所以关键问题只要求出F(i, n)怎么用G的表达式表示

然后作者举了个例子F(3, 7)就是以3为根节点，左子树是[1, 2]右子树是[4, 5, 6, 7]的BST的个数，很明显左子树的个数是G(2),右子树的个数是G(4)，所以F(3, 7) = G(2) * G(4)

根据上面的结论

G(n) = G(0)*G(n-1) + G(1)*G(n-2) + ... + G(n-1)*G(0) //查了一下资料发现这个数列叫做卡特兰数(Catalan)

然后边界条件是G(0) = 1,问题很轻松就解决了
*/



/*
discuss里面的原文

The problem can be solved in a dynamic programming way. I’ll explain the intuition(直观) and formulas(公式) in the following.

Given a sequence 1…n, to construct a Binary Search Tree (BST) out of the sequence, we could enumerate(枚举) each number i in the sequence, and use the number as the root, naturally, the subsequence 1…(i-1) on its left side would lay on the left branch of the root, and similarly the right subsequence (i+1)…n lay on the right branch of the root. We then can construct the subtree from the subsequence 
recursively. Through the above approach, we could ensure that the BST that we construct are all unique, since they have unique roots.

The problem is to calculate the number of unique BST. To do so, we need to define two functions:

G(n): the number of unique BST for a sequence of length n.

F(i, n), 1 <= i <= n: the number of unique BST, where the number i is the root of BST, and the sequence ranges from 1 to n.

As one can see, G(n) is the actual function we need to calculate in order to solve the problem. And G(n) can be derived from F(i, n), which at the end, would recursively refer to G(n).

First of all, given the above definitions, we can see that the total number of unique BST G(n), is the sum of BST F(i) using each number i as a root.
i.e.

G(n) = F(1, n) + F(2, n) + ... + F(n, n). 
Particularly, the bottom cases, there is only one combination to construct a BST out of a sequence of length 1 (only a root) or 0 (empty tree).
i.e.

G(0)=1, G(1)=1. 
Given a sequence 1…n, we pick a number i out of the sequence as the root, then the number of unique BST with the specified root F(i), is the cartesian product of the number of BST for its left and right subtrees. For example, F(3, 7): the number of unique BST tree with number 3 as its root. To construct an unique BST out of the entire sequence [1, 2, 3, 4, 5, 6, 7] with 3 as the root, which is to say, we need to construct an unique BST out of its left subsequence [1, 2] and another BST out of the right subsequence [4, 5, 6, 7], and then combine them together (i.e. cartesian product). The tricky part is that we could consider the number of unique BST out of sequence [1,2] as G(2), and the number of of unique BST out of sequence [4, 5, 6, 7] as G(4). Therefore, F(3,7) = G(2) * G(4).

i.e.

F(i, n) = G(i-1) * G(n-i)	1 <= i <= n 
Combining the above two formulas, we obtain the recursive formula for G(n). i.e.

G(n) = G(0) * G(n-1) + G(1) * G(n-2) + … + G(n-1) * G(0) 
In terms of calculation, we need to start with the lower number, since the value of G(n) depends on the values of G(0) … G(n-1).
*/

class Solution 
{
public:
    int numTrees(int n) 
	{
		int *G = new int[n+1], i, j, ans;
		G[0] = 1;
		for(i = 1; i <= n; ++i)
		{
			G[i] = 0;
			for(j = 0; j < i; ++j)
				G[i] += G[j] * G[i-j-1];
		}
		ans = G[n];
		delete[] G;
		return ans;
    }
};

