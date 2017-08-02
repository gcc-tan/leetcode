#include<stdio.h>
#include<string.h>
/*
   Longest Substring Without Repeating Characters
Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/





/**
 * Solution (DP, O(n)):
 * 
 * Assume L[i] = s[m...i], denotes the longest substring without repeating
 * characters that ends up at s[i], and we keep a hashmap for every
 * characters between m ... i, while storing <character, index> in the
 * hashmap.
 * We know that each character will appear only once.
 * Then to find s[i+1]:
 * 1) if s[i+1] does not appear in hashmap
 *    we can just add s[i+1] to hash map. and L[i+1] = s[m...i+1]
 * 2) if s[i+1] exists in hashmap, and the hashmap value (the index) is k
 *    let m = max(m, k), then L[i+1] = s[m...i+1], we also need to update
 *    entry in hashmap to mark the latest occurency of s[i+1].
 * 
 * Since we scan the string for only once, and the 'm' will also move from
 * beginning to end for at most once. Overall complexity is O(n).
 *
 * If characters are all in ASCII, we could use array to mimic hashmap.
 *
 *
 * 假设L[i] = s[m...i]，表示以s[i]结尾的不重复的最长字串，并且我们为m...i的字符维护一个hashmap，里面存储的是 <字符，在s中的下标>
 *
 *我们知道每个字符都只会出现一次
 *那么我们可以对S[i+1]进行查找：
 *
 *1) 如果s[i+1]不出现在hashmap中，我们可以将s[i+1]加入到hashmap里面,并且L[i+1] = s[m...i+1]
 *
 *2) 如果s[i+1]出现在hashmap中，在hashmap中找到这个字符对应的索引k，m = max(m,k)，L[i+1] = s[m...i+1],并且在hashmap中更新s[i+1]出现的最新位置
 *
 *注意这个max(m,k)是必须的，举个例子s = "eabcbe" 这个例子中在扫描完c这个字符，前面四个字符都没出现过，这个时候最长的长度就是L[3] = 4,m = -1(初始值)。在读入下一个字符b，此时m = 2,L[4] = 2
 *读入最后的e时，hashmap里面肯定有这样一个键值对 <e,0> ，假如是m = k 而不是 m = (m,k) 最后得到的错误答案就是5
 */
#define MAX(a,b) ((a) > (b) ? (a) : (b))
int lengthOfLongestSubstring(char* s) 
{
	int i,result = 0,len = 0,m = -1;
	int map[128];//之前用char，忘记了s的长度可能很长
	for(i = 0;i < 128;++i)
		map[i] = -1;
	for(i = 0;s[i];++i)
	{
		if(map[s[i]] == -1)
		{
			len++;
			map[s[i]] = i;
		}
		else
		{
			m = MAX(m,map[s[i]]);
			len = i - m;
			map[s[i]] = i;
		}
		if(result < len)
			result = len;
	}
	return result;
}

int main()
{
	char *s = "bbbbb";
	printf("%d\n",lengthOfLongestSubstring(s));
	return 0;
}
