//Combinations


/*
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
*/


/*
给出两个数n和k，在1, 2, ... n中找出所有的k个数的组合
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
很容易想到递归的方法，递归的方法就是根据公式C(n,k)=C(n-1,k-1)+C(n-1,k),这里写一个非递归的方法。
*/
/*
这个迭代方法的主要思想就是按照排列的字母序从小到达依次穷举，这个代码没有一句是多余的，真的是写得好
*/
class Solution 
{
public:
    vector<vector<int>> combine(int n, int k) 
    {
        vector<vector<int>> ans;
        vector<int> p(k, 0);
        int i = 0;
        while(i >= 0)
        {
        	++p[i];
        	if(p[i] > n) --i;//当前的i位已经最大，需要增加i-1位的值来调整大小
        	else if(i == k - 1) ans.push_back(p);
        	else
        	{
        		++i;
        		p[i] = p[i-1];//下次的起点从上次的终点开始，这样保证升序
        	}
        }
        return ans;
    }
};