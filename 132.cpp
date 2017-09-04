//Palindrome Partitioning II

/*
Given a string s, partition s such that every substring of the partition is a palindrome(回文字符串).

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.
*/

/*
求一个字符串s的最小的分割次数，使得被分割的每个部分都是回文字符串
-------------------------------------------------------------------------------------------------------------------------------
解法1:
一种很典型的方法就是DP的解决方案，首先构造一个数组二维数组is_palin[i][j]表示s[i...j]是回文字符串。构造这个数组需要O(n^2)的时间复杂度。更进一步，为了或的最小的分割次数，我们需要另外一个min_cuts[i]
表示s[0...i-1]的最小的分割次数，min_cuts[i]初始化为i-1，i-1是将一个长度为i的字符串分割成回文字符串的最大的分割次数。min_cuts[0]初始值设置为-1,为了防止s[0...i-1]是一个回文串。当构造is_palin数组时，
我们每找到一个回文子串就更新min_cuts数组，举个例子如果s[i...j]是一个回文字符串，那么min_cuts[j+1] = min(min_cuts[j+1], min_cuts[i] + 1)，最后的返回值是min_cuts[n]

解法2:
第一个解法是遍历字符串的每个位置j，利用位置j结尾的所有回文字符串信息去更新min_cuts数组。方法2换了一种方式，利用以位置i为中心的回文字符串去更新min_cuts数组。更新方式同上。虽然在时间复杂度上没有提高，
但是内层循环查找回文字符串的执行次数减少了，因为中心扩展的方式当这个中心往两边扩展时不是回文字符串就能结束循环(因为分割要求是回文字符串，不是回文进行的更新不符合条件)。而前一种方式举个例子"abba"，
j的位置是最后一个a，i = j向前扫描的过程中扫描到b发现ba不够成回文字符串，但是这个循环不能停止，因为abba还是构成回文字符串。第二种方法减少了循环的次数，速度应该是要快点
*/



/*
discuss的原文

方法1
One typical solution is DP based. Such solution first constructs a two-dimensional bool array isPalin to indicate whether the sub-string s[i..j] is palindrome. To get such array, we need O(N^2) time 
complexity. Moreover, to get the minimum cuts, we need another array minCuts to do DP and minCuts[i] saves the minimum cuts found for the sub-string s[0..i-1]. minCuts[i] is initialized to i-1, 
which is the maximum cuts needed (cuts the string into one-letter characters) and minCuts[0] initially sets to -1, which is needed in the case that s[0..i-1] is a palindrome. When we construct isPalin array, we update minCuts everytime we found a palindrome sub-string, i.e. if s[i..j] is a palindrome, then minCuts[j+1] will be updated to the minimum of the current minCuts[j+1] and minCut[i]+1(i.e.
cut s[0..j] into s[0,i-1] and s[i,j]). At last, we return minCuts[N].
So the complexity is O(N^2). However, it can be further improved since as described above, we only update minCuts when we find a palindrome substring, while the DP algorithm spends lots of time to 
calculate isPalin, most of which is false (i.e. not a palindrome substring). If we can reduce such unnecessary calculation, then we can speed up the algorithm. This can be achieved with a 
Manancher-like solution, which is also given as following.

方法2
The Manancher-like solution scan the array from left to right (for i loop) and only check those sub-strings centered at s[i]; once a non-palindrome string is found, it will stop and move to i+1. 
Same as the DP solution, minCUTS[i] is used to save the minimum cuts for s[0:i-1]. For each i, we do two for loops (for j loop) to check if the substrings s[i-j .. i+j] (odd-length substring) and 
s[i-j-1.. i+j] (even-length substring) are palindrome. By increasing j from 0, we can find all the palindrome sub-strings centered at i and update minCUTS accordingly. Once we meet one non-palindrome
sub-string, we stop for-j loop since we know there no further palindrome substring centered at i. This helps us avoid unnecessary palindrome substring checks, as we did in the DP algorithm. Therefore,
this version is faster.
*/



//解法1,参考discuss里面的方法和代码写的，代码很简洁，13ms
class Solution 
{
public:
    int minCut(string s) 
	{
		int n = s.length(), i, j, min_cuts[n+1];
		bool is_palin[n][n];

		fill_n(is_palin[0], n * n, false);
		for(i = 0; i <= n; ++i)
			min_cuts[i] = i - 1;

		for(j = 0; j < n; ++j)
		{
			for(i = j; i >= 0; --i)
			{
				if(s[i] == s[j] && (j - i < 2 || is_palin[i+1][j-1]))//两边的字符相等，且中间的是回文串
				{
					is_palin[i][j] = true;
					min_cuts[j+1] = min(min_cuts[j+1], min_cuts[i] + 1);//更新的法则就是根据每个子串都是回文串的要点，只要发现了回文串就能够引发更新
				}
			}
		}
		return min_cuts[n];
    }
};




//方法2的实现，没想到快这么多3ms
class Solution 
{
public:
    int minCut(string s) 
	{
		int n = s.length(), min_cuts[n+1], i, j;

		for(i = 0; i <= n; ++i)
			min_cuts[i] = i - 1;

		for(i = 0; i < n; ++i)
		{
			//回文串的长度是奇数
			for(j = 0; i + j < n && i - j >= 0 && s[i+j] == s[i-j]; ++j)
				min_cuts[i+j+1] = min(min_cuts[i+j+1], min_cuts[i-j] + 1);

			//回文串的长度是偶数
			for(j = 1; i + j < n && i - j + 1 >= 0 && s[i+j] == s[i-j+1]; ++j)
				min_cuts[i+j+1] = min(min_cuts[i+j+1], min_cuts[i-j+1] + 1);
		}
		return min_cuts[n];
    }
};
