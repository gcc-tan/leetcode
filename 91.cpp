//Decode Ways

/*

A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.

*/


/*
给定一个编码的方式，A对应1,B对应2,...Z对应26，然后给出一个数字串，问有多少中解码的方式
-------------------------------------------------------------------------------------------------------------------------------------------------------
动态规划关键是要写出状态转移方程,dp[i]表示被编码的前i个字符的编码方式个数

if s[i-2]s[i-1] 组成的数在10到26之间
  dp[i] += dp[i-2];
if s[i-1] != 0 
  dp[i] += dp[i-1];
*/



//其实不用dp数组也可以，直接用两个变量代替，因为只用到了i-2,i-1两个变量，这个有兴趣自己优化
class Solution 
{
public:
    int numDecodings(string s) 
	{
		int n = s.size(), i;
		if(n == 0) return 0;
		vector<int> dp(n + 1, 0);

		dp[0] = 1;
		dp[1] = s[0] == '0' ? 0 : 1;
		for(i = 2; i <= n; ++i)
		{
			if(s[i-2] == '1' || (s[i-2] == '2' && s[i-1] <= '6'))
				dp[i] = dp[i-2];
			if(s[i-1] != '0')
				dp[i] += dp[i-1];
		}
		return dp[n];
    }
};









