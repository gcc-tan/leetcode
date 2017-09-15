//Group Anagrams

/*
Given an array of strings, group anagrams(易位构词游戏) together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"], 
Return:

[
  ["ate", "eat","tea"],
  ["nat","tan"],
  ["bat"]
]
*/


/*
Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"], 
Return:

[
  ["ate", "eat","tea"],
  ["nat","tan"],
  ["bat"]
]
*/


/*
给一组单词，然后单词中只是字符位置不同的单词为一组e.g. abb和bab就是一组，将这些单词都进行分组
*/


/*
很直接的想法，遍历字符串列表，判断这个字符串是否在当前某个结果集合中。结果最后一组测试用例超时。
这个算法的时间复杂度应该是O(n * n * str_len)，n是输入字符串的长度，str_len是个每个字符串的长度
*/
//比较愚蠢的代码，可以忽略
class Solution 
{
private:
	//判断两个字符串是否是易位
	bool anagrams(string &a, string &b)
	{
		char cnt_a[26], cnt_b[26];
		int i, len_a = a.length(), len_b = b.length();
		if(len_a != len_b) return false;
		for(i = 0; i < 26; ++i)
			cnt_a[i] = cnt_b[i] = 0;

		for(i = 0; i < len_a; ++i)
		{
			++cnt_a[a[i]-'a'];
			++cnt_b[b[i]-'a'];
		}

		for(i = 0; i < 26; ++i)
		{
			if(cnt_a[i] != cnt_b[i]) 
				return false;
		}
		return true;
	}
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) 
	{
		vector<vector<string>> ans;
		int i, j;
		ans = {{strs[0]}};
		for(i = 1; i < strs.size(); ++i)
		{
			for(j = 0; j < ans.size(); ++j)
			{
				if(anagrams(strs[i], ans[j][0]))
				{
					ans[j].push_back(strs[i]);
					break;
				}
			}
			if(j == ans.size())
				ans.push_back(vector<string>(1, strs[i]));
		}
		return ans;
    }
};










/*
*这个算法的时间复杂度是O(n * str_len * log str_len) n是输入列表的长度，str_len是每个单词的长度(每个单词虽然不一样长，这个是一个大概估算)
*/
class Solution 
{
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) 
	{
		unordered_map<string, int> map;//map记录排序后的单词存放在ans里的位置
		vector<vector<string>> ans;
		int i, n = strs.size();
		string tmp;
		for(i = 0; i < n; ++i)
		{
			tmp = strs[i];
			sort(tmp.begin(), tmp.end());
			if(map.count(tmp))//同样排序的单词存在，直接插入
				ans[map[tmp]].push_back(strs[i]);
			else//不存在，插入后更新map
			{
				ans.push_back(vector<string>(1, strs[i]));
				map[tmp] = ans.size() - 1;
			}
		}
		return ans;
    }
};


/*
这个是discuss里面的代码，想法都差不多，也是将排序之后的单词为key，value是vector，就是对应这个key的所有单词，最后再将这些value组合。时间复杂度是一样的
*/
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, multiset<string>> mp;
        for (string s : strs) {
            string t = strSort(s);//这里的排序他就重复造车轮子，为了更快，使用了计数排序算法，时间复杂度为O(str_len)
            mp[t].insert(s);
        }
        vector<vector<string>> anagrams;
        for (auto m : mp) { 
            vector<string> anagram(m.second.begin(), m.second.end());
            anagrams.push_back(anagram);
        }
        return anagrams;
    }
private:
    string strSort(string& s) {
        int count[26] = {0}, n = s.length();
        for (int i = 0; i < n; i++)
            count[s[i] - 'a']++;
        int p = 0;
        string t(n, 'a');
        for (int j = 0; j < 26; j++)
            for (int i = 0; i < count[j]; i++)
                t[p++] += j;
        return t;
    } 
};





/*
*discuss里面还有一个比较有意思的答案，java写的，程序主体思想和之前的没有区别，关键是key的使用这块
*/
public static List<List<String>> groupAnagrams(String[] strs) { 
	//一个z就是103,最大的int就20亿，哪里能有10609?个z?
	//n^2 + n + 41. It gives primes from 41 to 1601小质数公式
	int[] prime = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103};//最多10609个z

	List<List<String>> res = new ArrayList<>();
	HashMap<Integer, Integer> map = new HashMap<>();
	for (String s : strs) {
		int key = 1;
		//用质数相乘保证不同类型的单词之间的key不同
		for (char c : s.toCharArray()) {
			key *= prime[c - 'a'];
		}
		List<String> t;
		if (map.containsKey(key)) {
			t = res.get(map.get(key));
		} else {
			t = new ArrayList<>();
			res.add(t);
			map.put(key, res.size() - 1);
		}
		t.add(s);
	}
	return res;
}


