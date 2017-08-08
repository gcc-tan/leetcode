#include<stdio.h>

//Container With Most Water

/*
Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical(垂直的) lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). 
Find two lines, which together with x-axis(x轴) forms a container, such that the container contains the most water.

Note: You may not slant(倾斜) the container and n is at least 2
*/


/*
题目的大概意思就是有一些长短不同的板子，他们间隔都一样，问哪两个板子之间能够装最多的水，板子之间可以不连续(没有说清楚吗,看来我太天真了)

------------------------------------------------------------------------------------------------------------------------------------------------------------------

Start by evaluating the widest container, using the first and the last line. All other possible containers are less wide, so to hold more water, they need to be higher. Thus, after evaluating that 
widest container, skip lines at both ends that don't support a higher height. Then evaluate that new container we arrived at. Repeat until there are no more possible containers left.


贪心的策略。从最宽的容器开始计算，用第一根线和最后一根线。因为所以其他可能的容器都更窄一些，所以为了装更多的谁，它们需要更高。因此，在计算完了最宽的容器之后。跳过那些不支持更高高度的容器。
然后重新计算新容器的面积。重复上述过程，直到最后没有容器剩余。
*/

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
int maxArea(int* height, int heightSize) 
{
	int i, j, h, area = 0;
	for(i = 0, j = heightSize - 1; i < j;)
	{
		h = MIN(height[i],height[j]);
		area = MAX(area,h * (j - i));
		while(i < j && height[i] <= h) ++i;
		while(i < j && height[j] <= h) --j;
	}
	return area;
}

int main()
{
	int a[] = {1,2,1,4};
	printf("%d\n",maxArea(a, 4));
	return 0;
}
