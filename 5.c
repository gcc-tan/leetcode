#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Longest Palidromic substring
/*
Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example:

Input: "babad"

Output: "bab"

Note: "aba" is also a valid answer.
Example:

Input: "cbbd"

Output: "bb"
*/




/*
题目的意思就是查找一个字符串的最长回文子串

----------------------------------------------------------------------------------------------------------------------
这里有一个常见的错误做法，就是将字符串s反转得到s'，然后比较两个字符串的最长的公共子串。举个例子就知道错误在哪了s="abacdfgdcaba" s' = "abacdgfdcaba"


下面介绍一个O(n^2)的算法和一个O(n)的算法

时间复杂度为O(n^2)的算法有两种:
a) 动态规划，首先给定字符数组s[] = "abaacd",和p[i][j]表示字符数组i~j的字符串是否是回文字符串。所以p[i][j]的取值有true，false两种。
根据上面的定义，很容易写出状态转移方程。p[i][j] = p[i+1][j-1] and s[i] == s[j]。然后初始值是p[i][i] = true,p[i][i+1] = (s[i] == s[i+1])


b)观察回文字符串我们就能知道字符串是关于中心对称的，因此可以检查给定字符串的每个字符，然后以它为中心向两边扩展。这个方法相比动态规划的方法空间复杂度更低。不过扩充的时候要注意，像abb这样的字符串，'bb'这样的偶数长度的回文串他们的中心是两个点。

时间复杂度是O(n)的算法是一个叫Manacher算法，具体的介绍见md文档
*/


//扩充的方法实现
int expand(char *s,int len,int l,int r)
{
	while(l >= 0 && r < len && s[l] == s[r])
		--l,++r;
	return r - l - 1;
}
char* longestPalindrome(char* s) 
{
	int i,len1,len2,max_len = 0,str_len = strlen(s),start;
	char *str;
	for(i = 0; i < str_len;++i)
	{
		len1 = expand(s,str_len,i,i);
		len2 = expand(s,str_len,i,i+1);
		if(max_len < len1)
		{
			start = i - len1 / 2;
			max_len = len1;
		}
		if(max_len < len2)
		{
			start = i - len2 / 2 + 1;
			max_len = len2;
		}
	}
	str = (char *)malloc(max_len + 1);
	strncpy(str,s+start,max_len);
	str[max_len] = '\0';
	return str;
}



#define MIN(a,b) ((a) < (b) ? (a) : (b))
char* longestPalindrome(char *s)
{
	char str[2048],*ret;
	int p[2048];
	int i,len,mx = 0,id = 0,pos = 0,rlen,start;//rlen最长回文串的长度，start在s中的开始位置
	//预处理
	str[0] = '$';
	for(i = 0,len = 0; s[i]; ++i)
	{
		str[++len] = '#';
		str[++len] = s[i];
	}
	str[++len] = '#';
	str[++len] = '\0';

	for(i = 1; i < len; ++i)
	{
		p[i] = i < mx ? MIN(p[2*id-i],mx - i) : 1;
		while(str[i+p[i]] == str[i-p[i]]) p[i]++;
		if(i + p[i] > mx)
		{
			mx = i + p[i];
			id = i;
		}
		if(p[pos] < p[i])
			pos = i;
	}

	rlen = (2 * p[pos] - 1) / 2;
	start = (pos -p[pos]) / 2;
	ret = (char *)malloc(rlen + 1);
	strncpy(ret,s + start,rlen);
	ret[rlen] = '\0';
	return ret;
}
