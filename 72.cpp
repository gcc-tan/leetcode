//Edit Distance


/*
Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character
*/


/*
题目的意思是给两个单词，然后让你找出最少的操作次数让一个单词变成另外一个单词，操作包括三种，插入一个字符，删除一个字符，替换一个字符
-----------------------------------------------------------------------------------------------------------------------------------------------------------
不用说了，肯定是网易招聘实习的时候的编程题，原来出处就在这个地方啊，但是应该好好刷刷这个题目的，不应该去刷poj，poj对我难度太大了

其实当时是不会做的，但是我之后看了解答，会做了，现在在来动手还是不会做，感觉有点浪费生命啊
*/


/*

This is a classic problem of Dynamic Programming. We define the state dp[i][j] to be the minimum number of operations to convert word1[0..i - 1] to word2[0..j - 1]. The state equations have two cases: the boundary case and the general case. Note that in the above notations, both i and j take values starting from 1.

For the boundary case, that is, to convert a string to an empty string, it is easy to see that the mininum number of operations to convert word1[0..i - 1] to "" requires at least i operations (deletions). In fact, the boundary case is simply:

dp[i][0] = i;
dp[0][j] = j.
Now let's move on to the general case, that is, convert a non-empty word1[0..i - 1] to another non-empty word2[0..j - 1]. Well, let's try to break this problem down into smaller problems (sub-problems). Suppose we have already known how to convert word1[0..i - 2] to word2[0..j - 2], which is dp[i - 1][j - 1]. Now let's consider word[i - 1] and word2[j - 1]. If they are euqal, then no more operation is needed and dp[i][j] = dp[i - 1][j - 1]. Well, what if they are not equal?

If they are not equal, we need to consider three cases:

Replace word1[i - 1] by word2[j - 1] (dp[i][j] = dp[i - 1][j - 1] + 1 (for replacement));
Delete word1[i - 1] and word1[0..i - 2] = word2[0..j - 1] (dp[i][j] = dp[i - 1][j] + 1 (for deletion));
Insert word2[j - 1] to word1[0..i - 1] and word1[0..i - 1] + word2[j - 1] = word2[0..j - 1] (dp[i][j] = dp[i][j - 1] + 1 (for insertion)).
Make sure you understand the subtle differences between the equations for deletion and insertion. For deletion, we are actually converting word1[0..i - 2] to word2[0..j - 1], which costs dp[i - 1][j], and then deleting the word1[i - 1], which costs 1. The case is similar for insertion.

Putting these together, we now have:

dp[i][0] = i;
dp[0][j] = j;
dp[i][j] = dp[i - 1][j - 1], if word1[i - 1] = word2[j - 1];
dp[i][j] = min(dp[i - 1][j - 1] + 1, dp[i - 1][j] + 1, dp[i][j - 1] + 1), otherwise.
The above state equations can be turned into the following code directly.

*/


/*
先定义状态转移方程在考虑边界条件
首先定义dp[i][j]的值表示word1的0~i-1与word2的0~j-1需要进行操作的最小次数，定义了这个之后就用利用子问题进行求解
首先先看比较简单的情况
1. 如果word1[i-1] == word2[j-1]那么dp[i][j] = dp[i-1][j-1]，因为此时不需要进行变换就能得到答案
2. 如果不等的情况，那么就要进行操作了，操作有三种，那么我们分三种情况进行考虑
   a. 进行替换操作，dp[i][j] = dp[i-1][j-1] + 1;
   b. 进行删除操作，删除可以删除不匹配的word1[i-1],也可以删除word2[j-1] 所以有两种 dp[i][j] = dp[i-1][j] + 1 或者 dp[i][j] = dp[i][j-1] + 1
   c. 进行插入操作  情况也是两种，在word1[i-1]后面加入一个字符a,使得a == word1[j-1], 或者是在word2[j-1]后面加入一个a，使得a== word1[i-1]不管怎么样dp[i][j] = dp[i][j-1] + 1，dp[i][j] = dp[i-1][j] + 1
所以加入边界条件就有上面的结论了:
dp[i][0] = i;
dp[0][j] = j;
dp[i][j] = dp[i - 1][j - 1], if word1[i - 1] == word2[j - 1];
dp[i][j] = min(dp[i - 1][j - 1] + 1, dp[i - 1][j] + 1, dp[i][j - 1] + 1), otherwise.
*/

//直接将上面表达式翻译的代码我就不写了，这里写一个能够优化空间复杂度为O(m)或者是O(n)的方法
class Solution 
{
public:
    int minDistance(string word1, string word2) 
	{
		int row = word1.size(), col = word2.size(), i, j, pre, tmp;//pre保存的是dp[i-1][j-1]的值
		vector<int> cur(row + 1, 0);

		//dp[i][0]的情况
		for(i = 1; i <= row; ++i)
			cur[i] = i;

		for(j = 1; j <= col; ++j)
		{
			pre = cur[0];
			cur[0] = j;//dp[0][j]的情况
			for(i = 1; i <= row; ++i)
			{
				if(word1[i-1] != word2[j-1])
				{
					tmp = min(pre + 1, min(cur[i-1] + 1, cur[i] + 1));
					pre = cur[i];
					cur[i] = tmp;
				}
				else
				{
					tmp = pre;
					pre = cur[i];
					cur[i] = tmp;
				}
			}
		}
		return cur[row];
    }
};
