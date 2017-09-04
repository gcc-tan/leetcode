//Word Break


/*
Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words. You may assume the dictionary does not contain duplicate words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code".
*/


/*
题目的意思是给一个字符串s，和字典dict，判断分割成一个或者多个dict里面的单词
---------------------------------------------------------------------------------------------------
定义dp[i]表示长度为i的字符串能被word break。主要的想法就是穷举所有的单词被分割的点
if find j
   dp[i] = dp[j] && (s[j...i-1] in dict) 
else 
   dp[i] = 0

*/







class Solution 
{
public:
    bool wordBreak(string s, vector<string>& wordDict) 
	{
		int i, n = s.length(), j;
		bool dp[n+1];
		unordered_map<string, int> dict;
		fill_n(dp, n + 1, false);
		dp[0] = true;//防止整体一个单词的情况
		for(i = 0; i < wordDict.size(); ++i)
			dict[wordDict[i]] = 1;
		for(i = 1; i <= n; ++i)
		{
			for(j = i - 1; j >= 0; --j)
			{
				if(dp[j] && dict.find(s.substr(j, i - j)) != dict.end())
				{
					dp[i] = true;
					break;
				}
			}
		}

		return dp[n];
    }
};


