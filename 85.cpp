//Maximal Rectangle

/*
Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 6.
*/


/*
题目的意思很简单，就是给出一个二维数组，然后里面由0和1组成，要求找到由1组成的面积最大的矩形
---------------------------------------------------------------------------------------------------------------------------------------------------------------
一看就是没有什么思路的题目。总结一下做法
1. 暴力方法 暴力方法思路很清晰，对给定matrix的每个点去计算以该点为左上角点的面积的最大值，然后取这些点中面积最大的就行。计算以该店为左上角的点面积最大的方法就是以输入点(i, j)为起点，
向右边进行扩展(就是)，记录这个时候的最大宽度,最大面积=宽度*1，然后行数加一，同样向右进行扩展，如果此时扩展的最大最大宽度小于前行，更新此时的宽度，此时面积就等于宽度*2，重复上面过程直到最后一行
这个算法的时间复杂度应该是O(n^4),计算最大面积时O(n^2)遍历所有点是O(n^2)

2. 这个discuss的解释我也是日了狗，用于dp的三个量left, right, height都没解释清楚怎么能让人看懂啊，今天这个解法花了两个小时都没看懂什么意思。最后还是用google搜出来的这篇文章，
感谢作者 https://segmentfault.com/a/1190000004239097 的解释，终于看懂了

这篇文章在doc里面也有

其实主要的思想是为每个点维护三个变量，高度height，左边界的值left，右边界的值right，然后整个矩形的面积是height*(right-left)。所以对于矩阵中任意一点，我们可以根据以上三个变量维护三个数组，
分别为height[][], right[][], left[][]，来表示以这个点为底边的任意一点，以这个点为最底向上连续’1‘的长度为轴向左向右扫，能够组成的面积最大的内部全部为’1‘的长方形。

所以关键是怎么维护和更新三个变量

a. height[i][j] = matrix[i][j] == 1 ? ++height[i-1][j]: 0
b. left[i][j]   = max(left[i-1][j], cur_left)   cur_left表示对ith行而言，从（i，j)向左连续为'1'直至(i,cur_left)那个点 通俗点说是到当前点一直为1的左边的点
c. right[i][j] = min(right[i-1][j], cur_right) cur_right表示对ith行而言，从(i, j)向右连续为'1'直至(i, cur_right-1)那个点

而且由于每个点只与上一行有关，可以用一维数组代替二维数组

下面就是按行遍历时几个变量对应的值:
matrix:
0 0 0 1 0 0 0 
0 0 1 1 1 0 0 
0 1 1 1 1 1 0

各点height, left及right值如下：

row 0:
h: 0 0 0 1 0 0 0
l: 0 0 0 3 0 0 0
r: 7 7 7 4 7 7 7

row 1:
h: 0 0 1 2 1 0 0
l: 0 0 2 3 2 0 0
r: 7 7 5 4 5 7 7 

row 2:
h: 0 1 2 3 3 1 0
l: 0 1 2 3 2 1 0
r: 7 6 5 4 5 6 7
*/


class Solution 
{
public:
    int maximalRectangle(vector<vector<char>>& matrix) 
	{
		if(matrix.empty()) return 0;//leetcode的测试用例有点蠢啊，有必要弄这个测试吗
		int cur_left, cur_right, i, j, area = 0, row = matrix.size(), col = matrix[0].size(), tmp;
		vector<int> height(col, 0), left(col, 0), right(col, col);

		for(i = 0; i < row; ++i)
		{
			cur_left = 0, cur_right = col;
			for(j = 0; j < col; ++j)
			{
				//更新height
				if(matrix[i][j] == '1') ++height[j];
				else height[j] = 0;

				//更新left
				if(matrix[i][j] == '1')  left[j] = max(left[j], cur_left);
				else 
				{
					left[j] = 0;
					cur_left = j + 1;
				}
			}

			for(j = col - 1; j >= 0; --j)
			{

				//更新right
				if(matrix[i][j] == '1') right[j] = min(right[j], cur_right);
				else
				{
					right[j] = col;
					cur_right = j;//这个地方不和之前left一样是为了形成一个左开右闭的区间，计算宽度就直接right-left而已
				}

				tmp = (right[j] - left[j]) * height[j];
				if(area < tmp)
					area = tmp;
			}
		}
		return area;
	}
};
