//Text Justification

/*
Given an array of words and a length L, format the text such that each line has exactly L characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly L characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.

For example,
words: ["This", "is", "an", "example", "of", "text", "justification."]
L: 16.

Return the formatted lines as:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
*/


/*
题目翻译：
给出一个单词数组和长度L，格式化文本保证每行有L个字符(is fully justified不知道什么意思)。你应该用一种贪心的方法，意思是每行尽量多放单词。为了保证每行有L个字符，
可以添加额外的空格(单词之间正常的分隔还是要的)。空格应该尽可能均匀地分布，如果空格不可能均匀分布，空格应该放在左边。如果是最后一行，要左对齐，不允许插入空格
-----------------------------------------------------------------------------------------------------------------------------------------------------------

*/



class Solution 
{
public:
    vector<string> fullJustify(vector<string>& words, int L) 
	{
		int n = words.size(), i, j, slot, remain, k;
		string line;
		vector<string> ans;
		for(i = 0; i < n;)
		{
			remain = L;
			remain -= words[i].length();
			for(j = i; j + 1 < n && remain >= 0; ++j)
				remain -= words[j+1].length() + 1;//留一个空格
			if(j + 1 == n && remain >= 0)//最后一行
			{
				line = words[i++];
				while(i < n)
					line += " " + words[i++];
				line += string(remain, ' ');//最后补上空格
			}
			else 
			{
				if(j == i || j == i + 1)//一行一个单词的情况
				{
					ans.push_back(words[i] + string(L - words[i].length(), ' '));
					++i;
					continue;
				}
				slot = j - i - 1;//间隔
				remain += words[j].length() + 1;
				line = words[i++];
				for(k = 0; k < remain % slot; ++k)
					line += string(remain / slot + 2, ' ') + words[i++];//remain 剩余的空格, remain / slot平均值，将上单词之间本来就一个空格，在加上靠左边的需要多分一个
				while(i < j)
					line += string(remain / slot + 1, ' ') + words[i++];
			}

			ans.push_back(line);
		}
		return ans;
    }
};


















//dicuss里面的一个很简洁的代码，有兴趣自己看看，这个代码本身比较恶心
vector<string> fullJustify(vector<string> &words, int L) {
    vector<string> res;
    for(int i = 0, k, l; i < words.size(); i += k) {
        for(k = l = 0; i + k < words.size() and l + words[i+k].size() <= L - k; k++) {
            l += words[i+k].size();
        }
        string tmp = words[i];
        for(int j = 0; j < k - 1; j++) {
            if(i + k >= words.size()) tmp += " ";
            else tmp += string((L - l) / (k - 1) + (j < (L - l) % (k - 1)), ' ');
            tmp += words[i+j+1];
        }
        tmp += string(L - tmp.size(), ' ');
        res.push_back(tmp);
    }
    return res;
}
/*
For each line, I first figure out which words can fit in. According to the code, these words are words[i] through words[i+k-1]. Then spaces are added between the words. The trick here is to use mod operation to manage the spaces that can't be evenly distrubuted: the first (L-l) % (k-1) gaps acquire an additional space.
*/
