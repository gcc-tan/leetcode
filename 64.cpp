//Minimum Path Sum


/*

Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

*/



/*
又是走格子的题目，也是从左上角走到右下角，只能向下或者向右走，每个格子里都有一个数字，要求走过的格子中数字的和最小
---------------------------------------------------------------------------------------------------------------------------------------
直接看状态转移方程和边界条件吧，dp[i][j]表示到达(i, j)点的最小分值, grid[i][j]代表(i, j)点的分值
dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j]

*/









class Solution 
{
public:
    int minPathSum(vector<vector<int>>& grid) 
	{
		int i, j, row = grid.size(), col = grid[0].size();
		vector<int> cur(row, 0x3f3f3f3f);

		for(j = 0; j < col; ++j)
		{
			for(i = 0; i < row; ++i)
			{
				if(i == 0)
				{
					if(j == 0) cur[0] = grid[0][0];
					else cur[0] += grid[0][j];
				}
				else cur[i] = min(cur[i], cur[i-1]) + grid[i][j];
			}
		}

		return cur[row-1];
    }
};


//discuss里面的代码

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> cur(m, grid[0][0]);
        for (int i = 1; i < m; i++)//将第一列的计算完了
            cur[i] = cur[i - 1] + grid[i][0]; 
        for (int j = 1; j < n; j++) {//从第二列开始算
            cur[0] += grid[0][j]; 
            for (int i = 1; i < m; i++)
                cur[i] = min(cur[i - 1], cur[i]) + grid[i][j];
        }
        return cur[m - 1];
    }
};
