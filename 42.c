//Trapping Rain Water

/*
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

For example, 
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.
*/


/*
和之前的11题Container With Most Water有点像，这个题目的意思是给出一些方块的高度，然后方块的宽度都是1，要求这些方块之间堆成的面积能够接多少水
看原题描述的这个图就知道了https://leetcode.com/problems/trapping-rain-water/description/
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
1. 可以模仿判断最长回文字符串的方法思想，利用从中间扩展的办法，求出这个bar左边的最大高度，右边的最大高度，然后可以计算这个bar的承水量，把每个bar的水量加在一起就是总水量，时间复杂度为O(n^2)

2. 可以利用动态规划优化上面的算法，首先从左向有扫描，计算dp[i]数组，这个是i位置左边的最大高度，接着从右向左扫描，计算右边的最大高度，同样存入dp[i]数组中，这个计算的同时就能计算每个bar的水量，
扫描两次，时间复杂度是O(n)


3.用两个指针从两端往中间扫，在当前窗口下，如果哪一侧的高度是小的，那么从这里开始继续扫，如果比它还小的，肯定装水的瓶颈就是它了，可以把装水量加入结果，如果遇到比它大的，立即停止，
重新判断左右窗口的大小情况，重复上面的步骤

3中提到的方法理解起来可能有点抽象，这里先解释一下，左右两个指针l，r然后bar的高度是height，先要选择一个height[l]和height[r]中最小的高度min，因为这个肯定是其他bar的瓶颈，然后假设l是小的，
++l，从l向后扫描，如果发现height[l]小于min值，那么将这个min-height[l]的水加入，这个时候不管中间其他的bar的高度，这个l能够装最多的水已经由左右两边确定了，水肯定不能多，因为超过min就出去了
然后肯定也不会少，中间就算什么都没有还是有height[r]将水堵住
*/


//方法2的实现
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
int trap(int* height, int heightSize) 
{
	int *dp = malloc(sizeof(int) * heightSize), i, max = 0, ans = 0;
	for(i = 0; i < heightSize; ++i)
	{
		dp[i] = max;
		max = MAX(height[i], max);
	}
	for(i = heightSize - 1, max = 0; i >= 0; --i)
	{
		dp[i] = MIN(max, dp[i]);
		ans += dp[i] - height[i] > 0 ? dp[i] - height[i] : 0;
		max = MAX(height[i], max);
	}
	free(dp);
	return ans;
}


//方法3实现

#define MIN(a, b) ((a) < (b) ? (a) : (b))
int trap(int *height, int heightSize)
{
	int l, r, min, ans = 0;
	for(l = 0, r = heightSize - 1; l < r;)//l < r而不是 l <= r是因为l,r都是已经判断过了的(开始的时候l，r指向的位置都是不能装水的)
	{
		min = MIN(height[l], height[r]);
		if(height[l] == min)
		{
			for(++l; l < r && height[l] < min; ++l)
				ans += min - height[l];
		}
		else
		{
			for(--r; l < r && height[r] < min; --r)
				ans += min - height[r];
		}
	}
	return ans;
}
















