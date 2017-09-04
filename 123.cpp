//Best Time to Buy and Sell Stock III

/*

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

*/




/*
和之前卖股票的121题Best Time to Buy and Sell Stock III一样，题目的要求是最多买卖两次，但是两次买卖的时间点不能重合
-----------------------------------------------------------------------------------------------------------------------
这个题目的解决方案很多，
1.这个方法感觉很难想到，这个方案直接看代码吧，有点矛盾也好理解也不好理解

2.可以推广到任意多次交易的，在doc文档里面有，链接地址是 http://blog.csdn.net/linhuanmars/article/details/23236995，感觉不是很好理解
*/


class Solution 
{
public:
    int maxProfit(vector<int>& prices) 
	{
		const int MIN_INT = 1 << 31;
		//hold1买进一只股票的最大值，release1卖完一只股票的最大值，hold2买进两只股票的最大值，release2卖完两只股票的最大值
		int hold1 = MIN_INT, release1 = 0, hold2 = MIN_INT, release2 = 0, i, n = prices.size();

		for(i = 0; i < n; ++i)
		{
			/*
			 *hold1    = max(hold1, -prices[i]);
			 *release1 = max(release1, hold1 + prices[i]);
			 *hold2    = max(hold2, release1 - prices[i]);
			 *release2 = max(release2, hold2 + prices[i]);
			 这几行被注释的代码的更新顺序有问题，必须要卖完才能买，如果按照上面的顺序进行更新那么第一天就能卖。虽然说有问题但是我还是找不出反例
			 这个反例我都用生成随机数填充prices的代码跑了一个晚上也没有发现什么问题
			*/
			release2 = max(release2, hold2 + prices[i]);
			hold2 = max(hold2, release1 - prices[i]);
			release1 = max(release1, hold1 + prices[i]);
			hold1 = max(hold1, -prices[i]);

		}
		return release2;
    }
};




