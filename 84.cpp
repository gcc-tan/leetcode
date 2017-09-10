//Largest Rectangle in Histogram

/*
Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.

For example,
Given heights = [2,1,5,6,2,3],
return 10.

*/

/*
给定一个数组heights，每个元素代表一个高度，每个元素的宽度是1，要求这个数组构成的矩形的面积最大值
------------------------------------------------------------------------------------------------------------------------------------
为什么好多leetcode的题目总是给我一种似曾相识的感觉，但是就是不会做。。。

1. 暴力的解决方案就不用多说，列出矩形的两个端点i, j然后求出i，j之间的最小高度h就行，总的时间复杂度是O(n^3)

2. 这个解决方案求最长回文子串的思想一样，以每个矩形为中心向两边扩展，扩展的标准是其他矩形的高度要比当前矩形高。其实就是根据一个这样的原则----不管最大面积在哪，反正其中肯定是有一个高度最低的，
而我只要穷举所有高度最低的，肯定能得到最后答案。这个实现的算法很简单，时间复杂度是O(n^2)

3. 其实方法3就是基于方法2的一个改进方案，利用stack提高效率，主要思想还是那个，计算每个bar作为最矮的bar时最大的矩形面max_cur。但是计算max_cur的过程中需要知道小于这个bar的最左边位置left，
和最右侧位置right。怎么计算这两个值是个难题。栈是一个索引栈，记录的是每个bar在数组中的位置，入栈的要求是当前位置i代表的bar比栈顶高，直接入栈。当前位置i代表的bar比栈顶低，
弹栈计算当前栈顶的bar作为最低高度的面积。这里我解释一下，因为从出入栈的要求来看，栈肯定是个高度递增的栈。小于当前栈顶高度的bar是栈顶的下一个元素(left),然后当前位置i肯定是right。
所以left和right位置都计算完成，这个max_cur就能计算。

*/


/*
方法3的解释可能我的解释不太清楚，直接看英文的解释好了
We have discussed a Divide and Conquer based O(nLogn) solution for this problem. In this post, O(n) time solution is discussed. Like the previous post, width of all bars is assumed to be 1 for simplicity. For every bar ‘x’, we calculate the area with ‘x’ as the smallest bar in the rectangle. If we calculate such area for every bar ‘x’ and find the maximum of all areas, our task is done. How to calculate area with ‘x’ as smallest bar? We need to know index of the first smaller (smaller than ‘x’) bar on left of ‘x’ and index of first smaller bar on right of ‘x’. Let us call these indexes as ‘left index’ and ‘right index’ respectively.
We traverse all bars from left to right, maintain a stack of bars. Every bar is pushed to stack once. A bar is popped from stack when a bar of smaller height is seen. When a bar is popped, we calculate the area with the popped bar as smallest bar. How do we get left and right indexes of the popped bar – the current index tells us the ‘right index’ and index of previous item in stack is the ‘left index’. Following is the complete algorithm.

1) Create an empty stack.

2) Start from first bar, and do following for every bar ‘hist[i]’ where ‘i’ varies from 0 to n-1.
  a) If stack is empty or hist[i] is higher than the bar at top of stack, then push ‘i’ to stack.
  b) If this bar is smaller than the top of stack, then keep removing the top of stack while top of the stack is greater. Let the removed bar be hist[tp]. Calculate area of rectangle with hist[tp] as smallest bar. For hist[tp], the ‘left index’ is previous (previous to tp) item in stack and ‘right index’ is ‘i’ (current index).

3) If the stack is not empty, then one by one remove all bars from stack and do step 2.b for every removed bar.

Following is implementation of the above algorithm.
*/







class Solution 
{
public:
    int largestRectangleArea(vector<int>& heights) 
	{
		vector<int> st;//使用vector当栈顶
		int i, n, max_area = 0, cur;
		heights.push_back(0);
		n = heights.size();
		for(i = 0; i < n;)
		{
			if(st.empty() || heights[st.back()] <= heights[i])
				st.push_back(i++);
			else//这种情况不移动i，继续弹栈计算面积
			{
				cur = heights[st.back()];
				st.pop_back();
				max_area = max(max_area, cur * (st.empty() ? i : i - st.back() - 1));
			}
		}
		heights.pop_back();
		return max_area;
    }
};





