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
说实话题目的意思有点难看懂，大概意思就是有个目标字符串s，里面是长度相同的单词组成的，现在给出单词列表words，在s中找出恰好包含单词列表的所有位置。给出的单词列表中可能有重复的
例如这个测试用例，leetcode最恶心的地方就是题目里面不说清楚，测试用例里面又出现了。还有就是注意s中不一定全都是单词
"wordgoodgoodgoodbestword"
["word","good","best","good"]

"lingmindraboofooowingdingbarrwingmonkeypoundcake"
["fooo","barr","wing","ding","wing"]
这组测试用例我就日了狗，给出的s里面单词的长度都不一样
*/



class Solution 
{
public:
	//两层循环暴力求解
    vector<int> findSubstring(string s, vector<string>& words) 
	{
		unordered_map<string, int> m;
		string tmp;
		unordered_map<string, int>::iterator it;
		vector<int> v;
		int i, j, wl = words[0].length(), s_len = s.length(), words_len = words.size();
		for(i = 0; i < words.size(); ++i)//统计每个单词的出现次数
			++m[words[i]];

		for(i = 0; i <= s_len - wl * words_len; ++i)
		{
			unordered_map<string, int> m1;
			for(j = i; j < words_len; j += wl)
			{
				tmp = s.substr(j, wl);
				it = m.find(tmp);
				if(it == m.end()) break;
				++m1[tmp];
				if(m1[tmp] > m[tmp]) break;
			}
			if(j == words_len)
				v.push_back(i);
		}
		return v;
    }
};










/*
上面的算法是很直接的算法，下面的这个算法在效率上要提高很多。据说是我觉得应该是O(n),之前的算法应该是O(n^2)的算法

算法的核心思想是利用给定单词定长，并且要求的字符串是连续的单词序列这个特点，减少不必要的节点的检查。具体的方法是，假设单词的长度是wl，那么开始的检查点的位置可能是[0,wl - 1]。对于每个开始的检查点，
依次i,i+wl,i+2*wl,i+3*wl...这些位置开始的s串是否出现在单词列表words中。只要遍历0~wl-1的wl个初始位置，目标的位置肯定会出现在上面的i,i+wl...的序列中，并且它的所有单词都会被检查到。这样的检查方法
每个检查点应该只会被检查一次，时间复杂度应该是O(n)

而具体的做法和之前的方案区别不大
*/
//之前的算法196ms，现在这个39ms还是有很大的区别的
class Solution
{
public:
    vector<int> findSubstring(string s, vector<string>& words)
	{
		vector<int> v;
		unordered_map<string, int> m1, m2;
		string tmp,t;
		int left, i, j, wl = words[0].size(), len = s.length(), cnt, num = words.size();//left满足条件的子串的可能开始位置,cnt单词匹配的个数

		for(i = 0; i < words.size(); ++i)//统计words中单词的出现次数
			++m1[words[i]];
		for(i = 0; i < wl; ++i)
		{
			left = i, m2.clear(), cnt = 0;
			for(j = i; j <= len - wl; j += wl)
			{
				tmp = s.substr(j, wl);
				if(m1.count(tmp))
				{
					++m2[tmp];
					if(m2[tmp] <= m1[tmp])//这个小于等于有道理额，因为words中会有重复的单词
						++cnt;
					else
					{
						while(m2[tmp] > m1[tmp])//保证left的窗口中出现的单词都是小于等于words中出现的次数
						{
							t = s.substr(left, wl);
							--m2[t];
							if(m2[t] < m1[t]) --cnt;
							left += wl;
						}
					}
					if(cnt == num)
					{
						v.push_back(left);
						--m2[s.substr(left, wl)];
						--cnt;//cnt不置0因为在left的右边还有已经匹配的单词了，只需要减去left这个位置单词计数left就能向右移动
						left += wl;
					}
				}
				else
				{
					m2.clear();
					left = j + wl;
					cnt = 0;
				}
			}
		}
		return v;
    }
};
