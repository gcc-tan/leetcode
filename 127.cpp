//Word Ladder

/*
Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:

Only one letter can be changed at a time.
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log","cog"]
As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Note:
Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
*/


/*
给一个单词列表，给出一个开始的单词beginWord和结束单词endWord，判断从beginWord到endWord最少要几次转换，要求每次转换的单词都出现在单词列表中，每次转换只能改变一个单词
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
明明这些算法都学过，就是对问题的转化能力和分析能力有限。这是一个典型的bfs的结构。开始节点是beginWord，下一层节点是和beginWord只差一个单词的wordList里面的单词，就这样构成一层一层的树形结构，
最后能够访问到endWord就可以结束遍历，当前的层数就行
*/


//这个代码运行时间是316ms
class Solution 
{
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) 
	{
		queue<int> q;//存放在wordList中的位置
		int front, n, i, end;
		wordList.push_back(beginWord);
		n = wordList.size();
		char visit[n];//visit记录了一个层数信息，0表示未访问，非0表示访问过，且层数为visit[i]
		fill_n(visit, n, 0);
		visit[n-1] = 1;
		q.push(n-1);
		for(i = 0; i < n - 1; ++i)//判断endWord是否在wordList中
		{
			if(wordList[i] == endWord) 
			{
				end = i;
				break;
			}
		}
		if(i == n - 1) return 0;

		while(!q.empty())
		{
			front = q.front();
			if(front == end) return visit[front];
			q.pop();
			//这么循环的时间复杂度是O(worList_len^2)，还有一种做法是当前输入单词的长度word_len的每个字符进行更改一共25*word_len次查找是否在wordList中，这个就是O(word_len * wordList_len)
			for(i = 0; i < n; ++i)
			{
				if(visit[i] || diff(wordList[front], wordList[i]) != 1) continue;
				visit[i] = visit[front] + 1;
				q.push(i);
			}
		}
		return 0;
    }
	int diff(string &a, string &b)
	{
		int cnt, i, len = a.length();
		for(i = 0, cnt = 0; i < len; ++i)
			if(a[i] != b[i]) ++cnt;
		return cnt;
	}
};





/*
上面这个代码中bfs的过程还有加速的办法，就是利用双向扫描，从beginWord和endWord两个方向，只要中间有相遇，你就是成功返回了

这个代码的时间是33ms，击败了94.09%
*/
class Solution 
{
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) 
	{
		unordered_set<string> word_set(wordList.begin(), wordList.end()), *phead, *ptail, head, tail;
		string word;
		int i, j, dist = 2;
		head.insert(beginWord), tail.insert(endWord);
		phead = &head, ptail = &tail;
		word_set.insert(beginWord);//插入beginWord

		if(word_set.find(endWord) == word_set.end())
			return 0;
		while(!phead->empty())
		{
			if(phead->size() > ptail->size())//保证每次扩展下一层扩展的数目最少
				swap(phead, ptail);

			unordered_set<string> tmp;
            //auto c++ 11  可以用 unordered_set<string>::const_iterator it 或者是unordered_set<string>::iterator it代替
			for(auto it = phead->begin(); it != phead->end(); ++it)
			{
				word_set.erase(*it);
				for(i = 0; i < it->length(); ++i)
				{
					word = *it;
					for(j = 0; j < 26; ++j)
					{
						word[i] = 'a' + j;
						if(ptail->find(word) != ptail->end())
							return dist;
						if(word_set.find(word) != word_set.end())
							tmp.insert(word);
					}
				}
			}
			*phead = tmp;
			++dist;
		}
		return 0;
    }
};
