//Unique Paths II

/*

Follow up for "Unique Paths":

Now consider if some obstacles(障碍) are added to the grids. How many unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

For example,
There is one obstacle in the middle of a 3x3 grid as illustrated below.

[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
The total number of unique paths is 2.

Note: m and n will be at most 100.

*/

/*
和之前的Unique Path一样，只是多了一些障碍，还是找左上角到右下角的不同的路径
--------------------------------------------------------------------------------------------------------------------------------------------
dp[i][j] = matrix[i][j] == 1 ? 0 : dp[i-1][j] + dp[i][j-1]
*/


//9ms垫底的成绩，哎看来这个是真的慢，好在没有刷新下限，我是真的想不通慢在哪里，时间复杂度没办法优化了，能优化的是空间复杂度，难道是malloc和free消耗了时间
int uniquePathsWithObstacles(int** matrix, int row, int col) 
{
	int i, j, ans, **dp = malloc((row + 1) * sizeof(int *));
	dp[0] = malloc((row + 1) * (col + 1) * sizeof(int));//多分配一层的空间，让状态转移方程能够统一处理
	for(i = 1; i <= row; ++i)
		dp[i] = dp[0] + i * (col + 1);

	//边界条件
	for(i = 0; i <= row; ++i)
		dp[i][0] = 0;
	for(j = 0; j <= col; ++j)
		dp[0][j] = 0;
	dp[0][1] = 1;//给dp[1][1]的一个特殊的边界值,当matrix[0][0]是0的时候dp[1][1]应该是1

	for(i = 1; i <= row; ++i)
		for(j = 1; j <= col; ++j)
			dp[i][j] = matrix[i-1][j-1] ? 0 : dp[i-1][j] + dp[i][j-1];

	ans = dp[row][col];
	free(dp[0]);
	free(dp);
	return ans;
}



/*
上面的代码有两个冗余的地方，一个是空间，之前的那题已经说过了，还有就是明显不可达的情况可以提前结束循环。于是根据这两点写出了改进的c++代码，主要看人家的c++代码很简洁
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
我试了一下，没有写删除明显不可达的情况，发现只用了3ms，他discuss里面的代码用了4ms
*/


class Solution 
{
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) 
	{
		int i, j, row = obstacleGrid.size(), col = obstacleGrid[0].size();
		vector<int> cur(row + 1, 0);
		for(i = 1; i <= row; ++i)
		{
			if(!obstacleGrid[i-1][0])
				cur[i] = 1;
			else break;
		}

		for(j = 1; j < col; ++j)
			for(i = 1; i <= row; ++i)
				cur[i] =  obstacleGrid[i-1][j] ? 0 : cur[i] + cur[i-1];

		return cur[row];
    }
};








/*
* 根据我刚刚讲的思想discuss里面的实现代码
*/
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
		//边界条件
        vector<int> cur(m, 0);
        for (int i = 0; i < m; i++) {
            if (!obstacleGrid[i][0])
                cur[i] = 1;
            else break;
        }
        for (int j = 1; j < n; j++) {
            bool flag = false;//flag为false表示肯定不可达
            if (obstacleGrid[0][j])
                cur[0] = 0;
            else flag = true;
            for (int i = 1; i < m; i++) {
                if (!obstacleGrid[i][j]) {
                    cur[i] += cur[i - 1]; 
                    if (cur[i]) flag = true;
                }
                else cur[i] = 0; 
            }
            if (!flag) return 0;
        }
        return cur[m - 1];
    }
};
















