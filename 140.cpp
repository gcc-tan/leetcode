//word break II

/*
Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct a sentence where each word is a valid dictionary word. You may assume the 
dictionary does not contain duplicate words.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].
*/


/*
题目的要求比之前的Word Break II多了一个，就是要输出所有组合的可能。这种情况下动态规划应该是不能做，只能用递归
*/


/*
直接的递归在测试用例
s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
wordDict = ["a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"]
情况下TLE了，这种情况因为计算了很多重复的情形，只需要用hashmap来存储已经计算过的情况就行

在没有将dict改成hashmap之前是23ms，将顺序查找改成O(1)的查找时间变成12ms
*/


class Solution
{
private:
	unordered_map<string, vector<string>> m;
	unordered_map<string, bool> dict;
public:
	vector<string> wordBreak(string s, vector<string> &wordDict)
	{
		int i;
		m.clear();
		dict.clear();
		for(i = 0; i < wordDict.size(); ++i)
			dict[wordDict[i]] = true;
		return recursive(s);
	}
    vector<string> recursive(string s)
	{
		int i, n = s.length(), j;
		vector<string> ans, tmp;
		string str;
		if(m.count(s)) return m[s];
		if(dict.count(s))//处理整个是一个单词的情况
		{
			ans.push_back(s);
			//return ans;注释掉这行是因为整个s是一个单词还有肯能有其他的拆分情况。例如输入s = "aaa", wordDict = {"aaa", "a"},s不光能作为一个整体，还能够单独的一个字符进行使用
		}
		for(i = 1; i <= n; ++i)
		{
			str = s.substr(0, i);
			if(dict.count(str))
			{
				tmp = recursive(s.substr(i, n - i));
				for(j = 0; j < tmp.size(); ++j)
					ans.push_back(str + " " + tmp[j]);
			}
		}
		m[s] = ans;
		return ans;
    }
};
