//Longest Valid Parentheses

/*
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.
*/



/*
题目已经写得很清楚了，就是在字符串中找最长的合理的括号
------------------------------------------------------------------------------------------------------------------

反正我觉得正常人的第一想法是利用栈对括号的合法性进行检查， 标记出不合理的括号以及位置，两个不合理括号之间的长度就是合理的括号的长度
*/



//这个题目的测试用例是真的皮
class Solution 
{
public:
    int longestValidParentheses(string s) 
	{
		stack<char> p_st;
		vector<int> v;
		int pos = -1, i, len = s.length(), ans = 0, valid = 1;//pos当前右括号不匹配的位置，反正不合理只有一种表现，要么左括号多了，要么右括号多了，不会两者一起多，所以只要单独考虑就行
		for(i = 0; i < len; ++i)
		{
			if(s[i] == '(') 
			{
				p_st.push(s[i]);
				v.push_back(i);
			}
			else
			{
				if(p_st.empty())//右括号多的情况
				{
					valid = 0;
					ans = max(ans, i - pos -1);
					pos = i;
					continue;
				}
				p_st.pop();
				v.pop_back();
			}
		}
		//if面临的是"))()()"
		if(!valid)
			ans = max(ans, len - pos - 1);

		if(!p_st.empty())//计算左括号多的情况
		{
			valid = 0;
			for(i = 0;i < v.size(); ++i)
			{
				//利用上面更新的pos是"())(()"有这样的情况
				ans = max(ans, v[i] - pos - 1);
				pos = v[i];
			}
			ans = max(ans, len - pos - 1);
		}
		if(valid)
			return len;
		return ans;
    }
};









/*
这个是是和上面时间复杂度一样的算法，思想也差不多。
主要就是使用一个存储数组索引的栈，入栈和出栈的条件是
1. 遇到'('直接将其在s中的下标入栈
2. 遇到')'
    a.如果栈当前为空，直接入栈
	b.如果栈当前非空，判断栈顶位置在s中是否是'('
	  i. 是，弹栈
	  ii. 否，将此时')'在s中的下表入栈

依次弹栈计栈中元素的间隔最大的就行
*/
class Solution 
{
public:
    int longestValidParentheses(string s) 
	{
        int n = s.length(), longest = 0;
        stack<int> st;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') st.push(i);
            else {
                if (!st.empty()) {
                    if (s[st.top()] == '(') st.pop();
                    else st.push(i);
                }
                else st.push(i);
            }
        }
        if (st.empty()) longest = n;
        else {
            int a = n, b = 0;
            while (!st.empty()) {
                b = st.top(); st.pop();
                longest = max(longest, a-b-1);
                a = b;
            }
            longest = max(longest, a);
        }
        return longest;
    }
};
