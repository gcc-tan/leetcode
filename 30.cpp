//Substring with Concatenation of All words

/*
You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices(索引) of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).
*/

/*
说实话题目的意思有点难看懂，大概意思就是有个字符串s，里面是长度相同的单词组成的，现在给出单词列表，在s中找出恰好包含单词列表的所有位置。给出的单词列表中可能有重复的
例如这个测试用例，leetcode最恶心的地方就是题目里面不说清楚，测试用例里面又出现了
"wordgoodgoodgoodbestword"
["word","good","best","good"]
*/



class Solution 
{
public:
	//主要就是通过一个map对所有单词的出现做标记。这个代码有问题，没有办法处理列表中单词重复的现象，所以是标准的错误代码
    vector<int> findSubstring(string s, vector<string>& words) 
	{
		map<string, int> m;
		string tmp;
		map<string, int>::iterator it;
		vector<int> v;
		int i, wl = words[0].length(), match;
		for(i = 0; i < words.size(); ++i)
			m.insert(pair<string, int>(words[i], 0));

		for(i = 0, match = 0; i < s.length(); i += wl)
		{
			tmp = s.substr(i, wl);
			it = m.find(tmp);
			if(it == m.end()) 
			{
				reset_map(m);
				continue;
			}
			if(it->second != 0)
			{
				reset_map(m);
				match = 0;
				i -= wl;
				continue;
			}
			it->second = 1;
			++match;
			if(match == words.size())
			{
				v.push_back(i - (match - 1) * wl);
				match = 0;
				reset_map(m);
			}
		}
		return v;
    }
private:
	void reset_map(map<string, int> &m)
	{
		map<string, int>::iterator it;
		for(it = m.begin(); it != m.end(); ++it)
			it->second = 0;
	}
};
