//Word Ladder II



/*
Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation sequence(s) from beginWord to endWord, such that:

Only one letter can be changed at a time
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log","cog"]
Return
  [
    ["hit","hot","dot","dog","cog"],
    ["hit","hot","lot","log","cog"]
  ]
Note:
Return an empty list if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
*/


/*
紧接着Word Ladder的一道题，两道题的要求不同，这个题目要求返回最短的所有路径
------------------------------------------------------------------------------------------
其实有了之前题目的基础，这道题目的要求的就是从一个节点到达另一个节点的所有的最短路径。这个题目比较难

原理还是相似用bfs进行搜索，不过在标记是否是已经访问过的单词时没有在扩展的时候就进行删除，上层的多个节点可以到达下层的一个节点，所以这个时候有多条路径，不能在一个结点进行扩展之后就标记访问。
*/



class Solution 
{
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) 
	{
		int i, ch, level = 1, min_level = 0x3f3f3f3f;//level当前的层次，min_level到达endWord的最小层
		string path_last, str;
		vector<vector<string>> ans;
		unordered_set<string> word_set(wordList.begin(), wordList.end()), tmp;
		queue<vector<string>> q;//存储的是从根节点到当前节点的路径
        /*
		*vector<string> path{beginWord}
		*/
		vector<string> path = {beginWord};
		q.push(path);
		while(!q.empty())
		{
			path = q.front();
			q.pop();
			//当前的层的路径都扩展完了，可以进入下一层，所以之前的节点全部删除
			if(path.size() > level)
			{
				for(auto it = tmp.begin(); it != tmp.end(); ++it)
					word_set.erase(*it);
				tmp.clear();
				level = path.size();
				if(level > min_level) break;
			}

			path_last = path.back();
			for(i = 0; i < path_last.length(); ++i)
			{
				str = path_last;
				for(ch = 'a'; ch <= 'z'; ++ch)
				{
					if(path_last[i] == ch) continue;//和path_last相同的不考虑
					str[i] = ch;
					if(!word_set.count(str)) continue;
					tmp.insert(str);
					vector<string> next_path = path;
					next_path.push_back(str);

					if(str == endWord)
					{
						ans.push_back(next_path);
						min_level = level;
					}
					else q.push(next_path);
				}
			}
		}
		return ans;
    }
};



