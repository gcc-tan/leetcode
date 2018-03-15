//Minimum Window Substring

/*
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the empty string "".

If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.
*/


/*
在S中寻找最短的字符串包含T中的所有字符
--------------------------------------------------------------------------------------------------------------------------------------------------
想法是用begin和end维护一个窗口，begin和end的初始值是0，begin和end表示窗口的开始和结束位置。然后记录T中每个字符的出现次数。然后开始遍历S，遇到T中的字符，就把对应的哈希表中的value减1, ++end。
直到包含了T中的所有的字符，纪录一个最小长度并更新最小长度值。将子窗口的左边界右移，跳过那些不在T中的字符和第一个在T中的字符。重复上面过程就是了。每个元素最多遍历2次时间复杂度是O(n)
*/


class Solution 
{
public:
    string minWindow(string s, string t) 
	{
		int begin = 0, end = 0, i, map[128], cnt = t.size(), min_len = 0x3f3f3f3f, head;
		fill_n(map, 128, 0);
		for(i = 0; i < t.size(); ++i)
			++map[t[i]];

		while(end < s.size())
		{
			if(map[s[end++]]-- > 0) --cnt;
			while(cnt == 0)//所有字符都出现
			{
				if(min_len > end - begin)
				{
					min_len = end - begin;
					head = begin;
				}
				if(map[s[begin++]]++ == 0)//为了防止t中出现的字符次数比在begin和end中出现出现的次数少，从而漏算了最短的情况
					cnt++; 
			}
		}
		return min_len == 0x3f3f3f3f ? "" : s.substr(head, min_len);
    }
};
