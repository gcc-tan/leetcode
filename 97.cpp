//Interleaving String


/*
Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.
*/

/*
题目的意思是判断给定字符串s3能否由s1,和s2交替取一部分得到
---------------------------------------------------------------------------------------------------------------------------------------------
其实动态规划就是递归的一种较为高效的实现，因为动态规划利用数组存储了子问题的解，所以没有重复计算和遍历子问题，所以大大提高了程序的运行效率

*/




//递归的版本，肯定是超时，重复计算了很多子问题。但是这个这个代码简洁明了，简直无敌的存在
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        bool ans = false;
        if (s1.empty() && s2.empty() && s3.empty())
            return true;
        if (s3.empty())//执行这个判断时s1, s2, s3至少一个不为空，但是s3是空的，s1，s2至少一个不为空，这种情况返回false
            return false;
        if (!s1.empty() && s1[0] == s3[0])
            ans |= isInterleave(s1.substr(1), s2, s3.substr(1));
        if (ans == true)
            return true;
        if (!s2.empty() && s2[0] == s3[0])
            ans |= isInterleave(s1, s2.substr(1), s3.substr(1));
        return ans;
    }
};



/*
动态规划的实现，定义dp[i][j]表示长度为i的串s1，和长度为j的串s2，能否通过interleaving的方式构成长度为i+j的s3。边界条件dp[0][0] = 1

dp[i][j] = 0
if s1[i-1] == s3[i+j-1]
	dp[i][j] |= dp[i-1][j]
else if s2[j-1] == s3[i+j-1]
	dp[i][j] |= dp[i][j-1]

*/


class Solution {
public:
	//使用了二维dp，完全可以使用一维dp优化
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.size(), n = s2.size(), i, j;
        vector<vector<short>> dp(m + 1, vector<short>(n + 1, 0));

        if (m + n != s3.size())
            return false;
        if (s1.empty() && s2.empty() && s3.empty())
            return true;

        dp[0][0] = 1;
        for (i = 1; i <= m; ++i)
            dp[i][0] = dp[i-1][0] && (s1[i-1] == s3[i-1]);
        for (j = 1; j <= n; ++j)
            dp[0][j] = dp[0][j-1] && (s2[j-1] == s3[j-1]);

        for (i = 1; i <= m; ++i)
        {
            for (j = 1; j <= n; ++j)
            {
                if (s1[i-1] == s3[i+j-1])
                    dp[i][j] |= dp[i-1][j];
                if (s2[j-1] == s3[i+j-1])
                    dp[i][j] |= dp[i][j-1];
            }
        }
        return dp[m][n];
    }
};
