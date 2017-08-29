//Unique Paths

/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?
*/


/*
题目的意思就是在一个左上角的位置，要到达右下角的点，而移动的时候只能向下或者向右移动，问有多少中不同的移动方法
----------------------------------------------------------------------------------------------------------------------------
这个题目之前肯定是见过的，好像就是大三的那会找实习网上笔试的时候。我还记得这个题目不太会，现在想起来很明显是个动态规划的题目

状态转移方程dp[i][j] = dp[i-1][j] + dp[i][j-1], i, j表示网格中的位置dp[i][j]到达(i, j)的走法数目
边界条件dp[i][0] = 1 ，dp[0][j] = 1
*/


//时间复杂度是O(m*n)，空间复杂度是O(m*n)的算法
int uniquePaths(int m, int n) 
{
	int i, j, **dp = malloc(m * sizeof(int *)), ans;
	dp[0] = malloc(m * n * sizeof(int));
	for(i = 1; i < m; ++i)
		dp[i] = dp[0] + i * n;

	for(i = 0; i < m; ++i)
		dp[i][0] = 1;
	for(j = 0; j < n; ++j)
		dp[0][j] = 1;

	for(i = 1; i < m; ++i)
		for(j = 1; j < n; ++j)
			dp[i][j] = dp[i-1][j] + dp[i][j-1];

	ans = dp[m-1][n-1];
	free(dp[0]);
	free(dp);
	return ans;
}
//虽然方法就是上面的动态规划，但是空间上还是有很大的优化的

/*
优化空见复杂度为O(min(m, n))的算法，优化的依据很简单，根据上面状态转移的方程，只是使用了左边一列，上面一行的状态，所以使用两列或者是两行就能满足状态转移的方程，

在实现的时候选择两列
*/
int uniquePaths(int m, int n)
{
	int i, j, *cur, *pre, ans;
	if(m > n) return uniquePaths(n, m);//交换的目的保证空间是最小的
	cur = malloc(m * sizeof(int)), pre = malloc(m * sizeof(int));
	//边界条件
	cur[0] = 1;
	for(i = 0; i < m; ++i)
		pre[i] = 1;
	for(j = 1; j < n; ++j)
	{
		for(i = 1; i < m; ++i)
		{
			cur[i] = cur[i-1] + pre[i];
		}
		//pre = cur
		for(i = 0; i < m; ++i)
			pre[i] = cur[i];
	}
	ans = cur[m-1];
	free(pre), free(cur);
	return ans;
}


/*
接着在仔细观察一下，cur[i] = cur[i-1] + pre[i]这个状态转移的方程pre[i]是当前未更新的cur[i]的值，所以pre可以去掉，进一步提高效率和空间复杂度
*/
int uniquePaths(int m, int n)
{
	int i, j, *cur, ans;
	if(m > n) return uniquePaths(n, m);
	cur = malloc(m * sizeof(int));

	for(i = 0; i < m; ++i)
		cur[i] = 1;

	for(j = 1; j < n; ++j)
		for(i = 1; i < m; ++i)
			cur[i] += cur[i-1];

	ans = cur[m-1];
	free(cur);
	return ans;
}


//下面这个是discuss里面的内容
This is a fundamental DP problem. First of all, let's make some observations.

Since the robot can only move right and down, when it arrives at a point, there are only two possibilities:

It arrives at that point from above (moving down to that point);
It arrives at that point from left (moving right to that point).
Thus, we have the following state equations: suppose the number of paths to arrive at a point (i, j) is denoted as P[i][j], it is easily concluded that P[i][j] = P[i - 1][j] + P[i][j - 1].

The boundary conditions of the above equation occur at the leftmost column (P[i][j - 1] does not exist) and the uppermost row (P[i - 1][j] does not exist). These conditions can be handled by initialization (pre-processing) --- initialize P[0][j] = 1, P[i][0] = 1 for all valid i, j. Note the initial value is 1 instead of 0!

Now we can write down the following (unoptimized) code.

class Solution {
    int uniquePaths(int m, int n) {
        vector<vector<int> > path(m, vector<int> (n, 1));
        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                path[i][j] = path[i - 1][j] + path[i][j - 1];
        return path[m - 1][n - 1];
    }
};
As can be seen, the above solution runs in O(n^2) time and costs O(m*n) space. However, you may have observed that each time when we update path[i][j], we only need path[i - 1][j] (at the same column) and path[i][j - 1] (at the left column). So it is enough to maintain two columns (the current column and the left column) instead of maintaining the full m*n matrix. Now the code can be optimized to have O(min(m, n)) space complexity.

class Solution {
    int uniquePaths(int m, int n) {
        if (m > n) return uniquePaths(n, m); 
        vector<int> pre(m, 1);
        vector<int> cur(m, 1);
        for (int j = 1; j < n; j++) {
            for (int i = 1; i < m; i++)
                cur[i] = cur[i - 1] + pre[i];
            swap(pre, cur);
        }
        return pre[m - 1];
    }
};
Further inspecting the above code, we find that keeping two columns is used to recover pre[i], which is just cur[i] before its update. So there is even no need to use two vectors and one is just enough. Now the space is further saved and the code also gets much shorter.

class Solution {
    int uniquePaths(int m, int n) {
        if (m > n) return uniquePaths(n, m);
        vector<int> cur(m, 1);
        for (int j = 1; j < n; j++)
            for (int i = 1; i < m; i++)
                cur[i] += cur[i - 1]; 
        return cur[m - 1];
    }
}; 
Well, till now, I guess you may even want to optimize it to O(1) space complexity since the above code seems to rely on only cur[i] and cur[i - 1]. You may think that 2 variables is enough? Well, it is not. Since the whole cur needs to be updated for n - 1 times, it means that all of its values need to be saved for next update and so two variables is not enough.
