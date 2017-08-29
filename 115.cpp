//Distinct SubSequnces

/*
Given a string S and a string T, count the number of distinct subsequences of S which equals T.

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Here is an example:
S = "rabbbit", T = "rabbit"

Return 3.
*/




/*
题目的意思就是给定字符串s和t，求s中有多少个不同的子串和t相同，s的子串的就是s中删除0个或者多个字符
---------------------------------------------------------------------------------------------------------------------------------------------------------------
动态规划，定义dp[i][j]表示s的[0,i-1]中有多少个子串和t[0,j-1]相同

dp[i][j] = 

if s[i-1] != t[j-1] 
    dp[i][j] = dp[i-1][j]//结尾的两个字符不相等，直接删掉s的最后一个字符
else
    dp[i][j] = dp[i-1][j-1] + dp[i-1][j]//结尾的两个字符相等，那么s的子串中可以包括，也可以删除最后这个字符

边界条件是dp[0][j] = 0, dp[i][0] = 1(其中i，j都不为0) dp[0][0] = 1
*/


//从状态转移方程中很明显之用到了两个点，完全可以用一维的空间代替
//本来是使用了二维的vector，速度是垫底的，现在改成一维之后就是3ms AC了，变成最快的解决方案了
class Solution 
{
public:
    int numDistinct(string s, string t) 
	{
		int row = s.length(), col = t.length(), i, j, tmp, pre;
		vector<int> cur(row + 1, 1);

		for(j = 1; j <= col; ++j)
		{
			pre = cur[0];//pre代表dp[i-1][j-1]
			cur[0] = 0;//边界条件dp[0][j]
			for(i = 1; i <= row; ++i)
			{
				if(s[i-1] != t[j-1])
				{
					pre = cur[i];
					cur[i] = cur[i-1];
				}
				else
				{
					tmp = cur[i];
					cur[i] = pre + cur[i-1];
					pre = tmp;
				}
			}
		}
		return cur[row];
    }
};




