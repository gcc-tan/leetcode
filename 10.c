#include<stdio.h>
#define bool char
//Regular Expression Matching


/*

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") ? false
isMatch("aa","aa") ? true
isMatch("aaa","aa") ? false
isMatch("aa", "a*") ? true
isMatch("aa", ".*") ? true
isMatch("ab", ".*") ? true
isMatch("aab", "c*a*b") ? true

*/

/*
这是给定一个需要匹配的字符串和一个正则表达式，判断这个正则表达式能否和这个字符串匹配

-----------------------------------------------------------------------------------------------------------------------------------------------------------

ps:我发现了一个巨坑爹的地方，在terminal执行./a.out aaa a*看似正常的命令的时，argv[1] = "aaa" argv[2] = "a.out" terminal将*当成适配符，转换成可执行文件的名字了。

这个题目的思路就是递归或者动态规划，递归注意边界条件就够了。接下来讲讲动态规划

二维dp，定义f[i][j]，如果s[0...i-1]和p[0...j-1]匹配f[i][j] = true，否则f[i][j] = false;//之前定义的是0～i，主要发现一个问题，最后返回的值是dp[m-1][n-1] m和n要是有一个为0就尴尬了，代码无形中就增加

1. 如果p[j-1] == '*'
   a) p[j-2] 代表的字符不进行扩展 f[i][j] = f[i][j-2]
   b) p[j-2] 代表的字符扩展一次或者多次   f[i][j] = (f[i-1][j] && s[i-1] == p[j-2]) 
   ps:b) 中的情况要格外注意，我首先写的状态转移的方程是f[i][j] = (f[i-1][j-1] && s[i-1] == p[j-2])这样看起来也对，但是因为这个*表示的是重复一次或者多次，f[i-1][j-1]这个状态中就看不到*了，
   也就是说我只是默认重复了一次，并没有提供重复多次的机会
2. 如果p[j-1] != '*'
   f[i][j] = f[i-1][j-1] && s[i-1] == p[j-1];
*/

bool isMatch(char *s, char *p)
{
	int m = strlen(s) + 1, n = strlen(p) + 1, i, j;
	char **dp = malloc(m * sizeof(char *)),is_match;
	dp[0] = malloc(m * n *sizeof(char));
	for(i = 1; i < m; ++i)
		dp[i] = dp[0] + i * n;

	//边界条件
	dp[0][0] = 1;
	for(i = 1; i < m; ++i)
		dp[i][0] = 0;
	for(j = 1; j < n; ++j)
		dp[0][j] = p[j-1] == '*' ? dp[0][j-2] : 0;

	for(i = 1; i < m; ++i)
	{
		for(j = 1; j < n; ++j)
		{
			if(p[j-1] != '*')
				dp[i][j] = dp[i-1][j-1] && (s[i-1] == p[j-1] || p[j-1] == '.');
			else
				dp[i][j] = dp[i][j-2] || (dp[i-1][j] && (s[i-1] == p[j-2] || p[j-2] == '.'));
		}
	}

	is_match = dp[m-1][n-1];
	free(dp[0]);
	free(dp);

	return is_match;
}


//ugly implement
bool empty_partern(char *p)
{
	int i;
	if(*p == 0)//空串
		return 1;
	for(i = 0; p[i]; i += 2)
	{
		if(p[i+1] != '*')
			return 0;
	}
	return 1;
}
bool isMatch(char* s, char* p) 
{
	char match = 0;
	int i;
	if(s[0] == '\0' && empty_partern(p))
		return 1;
	else if(s[0] == '\0' || p[0] == '\0')
		return 0;
	if(p[1] == '*')
	{
		if(s[0] == p[0] || p[0] == '.')
			match |= isMatch(s + 1,p);
		match |= isMatch(s,p + 2);
	}
	else
	{
		if(s[0] == p[0] || p[0] == '.')
			return isMatch(s + 1,p + 1);
		else
			return 0;
	}
	return match;
}

int main(int argc,char **argv)
{
	printf("%d\n",isMatch(argv[1],argv[2]));
	return 0;
}





//简洁明了的c++代码，惭愧啊，惭愧，完全不是在一个等级上面
class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.empty())    return s.empty();
        
        if ('*' == p[1])
            // x* matches empty string or at least one character: x* -> xx*
            // *s is to ensure s is non-empty
            return (isMatch(s, p.substr(2)) || !s.empty() && (s[0] == p[0] || '.' == p[0]) && isMatch(s.substr(1), p));
        else
            return !s.empty() && (s[0] == p[0] || '.' == p[0]) && isMatch(s.substr(1), p.substr(1));
    }
};

class Solution {
public:
    bool isMatch(string s, string p) {
        /**
         * f[i][j]: if s[0..i-1] matches p[0..j-1]
         * if p[j - 1] != '*'
         *      f[i][j] = f[i - 1][j - 1] && s[i - 1] == p[j - 1]
         * if p[j - 1] == '*', denote p[j - 2] with x
         *      f[i][j] is true iff any of the following is true
         *      1) "x*" repeats 0 time and matches empty: f[i][j - 2]
         *      2) "x*" repeats >= 1 times and matches "x*x": s[i - 1] == x && f[i - 1][j]
         * '.' matches any single character
         */
        int m = s.size(), n = p.size();
        vector<vector<bool>> f(m + 1, vector<bool>(n + 1, false));
        
        f[0][0] = true;
        for (int i = 1; i <= m; i++)
            f[i][0] = false;
        // p[0.., j - 3, j - 2, j - 1] matches empty iff p[j - 1] is '*' and p[0..j - 3] matches empty
        for (int j = 1; j <= n; j++)
            f[0][j] = j > 1 && '*' == p[j - 1] && f[0][j - 2];
        
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (p[j - 1] != '*')
                    f[i][j] = f[i - 1][j - 1] && (s[i - 1] == p[j - 1] || '.' == p[j - 1]);
                else
                    // p[0] cannot be '*' so no need to check "j > 1" here
                    f[i][j] = f[i][j - 2] || (s[i - 1] == p[j - 2] || '.' == p[j - 2]) && f[i - 1][j];
        
        return f[m][n];
    }
};
