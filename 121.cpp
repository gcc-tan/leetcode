//Best Time to Buy ans Sell Stock



/*
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.

Example 1:
Input: [7, 1, 5, 3, 6, 4]
Output: 5

max. difference = 6-1 = 5 (not 7-1 = 6, as selling price needs to be larger than buying price)
Example 2:
Input: [7, 6, 4, 3, 1]
Output: 0

In this case, no transaction is done, i.e. max profit = 0.
*/



/*
题目的意思就是给一个数组，这个数组是股票每天的价格，通过买卖股票，来赚取最大的利益。要注意买的价钱肯定只能比卖的低才能赚钱。数学描述一下就是给定数组a，查找i < j，return max(a[j]-a[i])
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
这个题目设置的很巧妙，其实就是一个最大子段和的问题。例如给定的数组a = {a1, a2, a3, a4, a5}，我们做一个变换，相邻的a的元素之间互相减，得到了b = {a2-a1, a3-a2, a4-a3, a5-a4}
与是求出b数组的最大子段和就求出来了这个股票问题。举个例子，b数组的最大子段和是b1, b2也就是a2-a1, a3-a2这个子段和的值是b1 + b2 = a3 - a1就是告诉我们a3-a1是最大的

这里顺便也回顾一下最大子段和问题的解法给定数组b的最大子段和，先定义dp数组dp[i]表示以b[i]为结尾元素的最大的子段和

状态转移方程为dp[i] = max(b[i] + dp[i-1], b[i])

因为以b[i]结尾的最大子段和只有两种可能的情况，就是只有b[i]或者是包含一b[i-1]为结尾的元素。
if dp[i-1] < 0 
   dp[i] = b[i]; 
else 
   dp[i] = b[i];
*/





class Solution
{
public:
    int maxProfit(vector<int>& prices)
	{
		int n = prices.size(), i, profit, b = 0, max_p = 0;
		for(i = 1; i < n; ++i)
		{
			profit = prices[i] - prices[i-1];
			b = max(profit + b, profit);
			max_p = max(max_p, b);
		}
		return max_p <= 0 ? 0 : max_p;
    }
};
