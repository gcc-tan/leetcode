//Wildcard(通配符) Matching


/*
'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "*") → true
isMatch("aa", "a*") → true
isMatch("ab", "?*") → true
isMatch("aab", "c*a*b") → false
*/




/*
题目的意思是实现通配符?和*字符串匹配

这个题目和之前的10题Regular Expression Matching很相似，之前的那个题目是用动态规划来做的，比较恶心

------------------------------------------------------------------------------------------------------------
这个题目的用法是"?"匹配任何字符，那么不和.进行的匹配一样吗
*/




