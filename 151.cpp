//Reverse Words in a String


/*
Given an input string, reverse the string word by word.

For example,
Given s = "the sky is blue",
return "blue is sky the".

Update (2015-02-12):
For C programmers: Try to solve it in-place in O(1) space.

click to show clarification.

Clarification:
	What constitutes a word?
		A sequence of non-space characters constitutes a word.
	Could the input string contain leading or trailing spaces?
		Yes. However, your reversed string should not contain leading or trailing spaces.
	How about multiple spaces between two words?
		Reduce them to a single space in the reversed string.
*/


/*
输入一句话，由许多单词构成，反转这些单词，第一个单词在最后一个位置，第二个单词在倒数第二个位置
---------------------------------------------------------------------------------------------------------
有一个很好的思路，先反转整句话，然后反转每一个单词
*/


class Solution
{
public:
    void reverseWords(string &s)
	{
		int i, j, k, n = s.length();
		string tmp;
		reverse(s.begin(), s.end());
		for(i = 0; i < n && s[i] == ' '; ++i);//去掉开始的空格
		while(i < n)
		{
			for(j = i + 1; j < n && s[j] != ' '; ++j);//定位到当前单词最后
			for(k = j - 1; k >= i; --k)
				tmp.push_back(s[k]);

			tmp.push_back(' ');//单词间添加一个空格
			i = j;
			while(i < n && s[i] == ' ') ++i;//跳过中间的空格
		}
		if(tmp.back() == ' ')  tmp.pop_back();
		s = tmp;
    }
};












/*
空间复杂度为O(1)

代码很简介明了
*/
void reverseWords(string &s) {
    reverse(s.begin(), s.end());
    int storeIndex = 0;//记录当前结果字符串的长度
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != ' ') {
            if (storeIndex != 0) s[storeIndex++] = ' ';
            int j = i;
            while (j < s.size() && s[j] != ' ') { s[storeIndex++] = s[j++]; }
            reverse(s.begin() + storeIndex - (j - i), s.begin() + storeIndex);//反转一个单词
            i = j;
        }
    }
    s.erase(s.begin() + storeIndex, s.end());
}
