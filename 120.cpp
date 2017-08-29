//Triangle


/*
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle
[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:
Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.
*/


/*
给定一个三角形，要求从顶点走到底部的的路径上最小的分值
----------------------------------------------------------------------------------------
之前肯定做过一个一样的题目，是一个矩形要求最小的和

状态转移方程很很好写
dp[i][j] = min(dp[i-1][j-1], dp[i-1][j]) + triangle[i][j]

这里求出来的dp[i][j]是到达某个点的最小分值，遍历最后一行，取分值最小的就行

*/


//这是一种自顶向下的解决方案
class Solution 
{
public:
    int minimumTotal(vector<vector<int>>& triangle) 
	{
		const int MAX_INT = 0x3f3f3f3f;
		int i, j, n = triangle.size(), min_score = MAX_INT;
		vector<int> cur(n, MAX_INT);//行向量

		cur[0] = triangle[0][0];
		for(i = 1; i < n; ++i)
		{
			for(j = i; j >= 0; --j)//倒着算是防止使用一维空间时候被覆盖
			{
				if(j == 0)
				{
					cur[j] = cur[j] + triangle[i][j];
					continue;
				}
				cur[j] = min(cur[j], cur[j-1]) + triangle[i][j];
			}
		}
		for(j = 0; j < n; ++j)
			min_score = min(min_score, cur[j]);
		return min_score;
    }
};



//还有一种自向上的方法更简单，道理也是一样的，只是求解的过程是从最后一行开始，利用最后一行的结果去求上一行每个点到最后一行的最小的sum

class Solution 
{
public:
    int minimumTotal(vector<vector<int> > &triangle) 
	{
		int n = triangle.size(), i, j;
		vector<int> cur(triangle.back());

		for(i = n - 2; i >= 0; --i)
		{
			for(j = 0; j <= i; ++j)
			{
				cur[j] = min(cur[j], cur[j+1]) + triangle[i][j];
			}
		}

		return cur[0];//返回最顶端的点到最后一行的最小距离
    }
};
