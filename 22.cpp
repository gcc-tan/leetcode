//Generate Parentheses

/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]
*/


/*
题目的意思是给出n对括号，写一个函数产生所有配对括号的组合

-----------------------------------------------------------------------------------------------------------------

苦思半天不得其解，结果别人几行代码就搞定了。

其实仔细思考这个题目，它就是一个树型结构，但不是一颗完全二插树(完全的状态就是根节点有两个子节点左括号和右括号，左括号有两个子节点左括号和右括号，同样右括号也有两个节点)，它需要左右括号配对。
但是不管怎么样，这是一个树形的结构，那么肯定就会有两种方式bfs和dfs进行搜索。
*/


class Solution 
{
public:
	void dfs(vector<string> &v,string s,int l,int r)
	{
		if(l == 0 && r == 0)
		{
			v.push_back(s);
			return;
		}
		if(l > 0) dfs(v, s + "(", l - 1, r + 1);
		if(r > 0) dfs(v, s + ")", l, r -1);
	}
    vector<string> generateParenthesis(int n) 
	{
		vector<string> v;
		dfs(v, "", n, 0);
		return v;
    }
};


/*
My method is DP. First consider how to get the result f(n) from previous result f(0)...f(n-1).
Actually, the result f(n) will be put an extra () pair to f(n-1). Let the "(" always at the first position, to produce a valid result, we can only put ")" in a way that there will be i pairs () inside the extra () and n - 1 - i pairs () outside the extra pair.

Let us consider an example to get clear view:

f(0): ""

f(1): "("f(0)")"

f(2): "("f(0)")"f(1), "("f(1)")"

f(3): "("f(0)")"f(2), "("f(1)")"f(1), "("f(2)")"

So f(n) = "("f(0)")"f(n-1) , "("f(1)")"f(n-2), "("f(2)")"f(n-3) ... "("f(i)")"f(n-1-i) ... "(f(n-1)")"

Below is my code:

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
我的方法是dp。 首先考虑一下怎么从f(0)...f(n-1)的结果的到f(n)
事实上，f(n)就是f(n-1)加上一对额外的括号。让"("总是在第一个位置，为了产生有效的结果，我们只能把")"放在某个位置是的这个括号对中有i对括号并且这对括号对外面有n-1-i对括号

为了更清楚看出来，我们举个例子

f(0): ""

f(1): "("f(0)")"

f(2): "("f(0)")"f(1), "("f(1)")"

f(3): "("f(0)")"f(2), "("f(1)")"f(1), "("f(2)")"

So f(n) = "("f(0)")"f(n-1) , "("f(1)")"f(n-2), "("f(2)")"f(n-3) ... "("f(i)")"f(n-1-i) ... "(f(n-1)")"

*/

public class Solution
{
    public List<String> generateParenthesis(int n)
    {
        List<List<String>> lists = new ArrayList<>();
        lists.add(Collections.singletonList(""));
        
        for (int i = 1; i <= n; ++i)
        {
            final List<String> list = new ArrayList<>();
            
            for (int j = 0; j < i; ++j)
            {
                for (final String first : lists.get(j))
                {
                    for (final String second : lists.get(i - 1 - j))
                    {
                        list.add("(" + first + ")" + second);
                    }
                }
            }
            
            lists.add(list);
        }
        
        return lists.get(lists.size() - 1);
    }
}
