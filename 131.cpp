//Palindrome Partitioning


/*
Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

[
  ["aa","b"],
  ["a","a","b"]
]
*/


/*
将一个字符串s分割成多个子串，每个子串都要求是回文串，求出所有的分割方法
-------------------------------------------------------------------------------------------------------------------------------------
主要想法就是找到第一个回文字符串，对剩余的字符串进行递归调用，再将这个字符串加入到递归调用返回的结果中
*/


class Solution 
{
private:
	vector<vector<string>> bt(string s)
	{
		string t;
		int i, j;
		vector<vector<string>> ans, tmp;
		if(s.empty()) ans = {{}};
		for(i = s.length() - 1; i >= 0; --i)
		{
			t = s.substr(i, s.length() - i);
			if(!is_palindrome(t)) continue;
			tmp = bt(s.substr(0, s.length() - t.length()));
			for(j = 0; j < tmp.size(); ++j)
			{
				tmp[j].push_back(t);
				ans.push_back(tmp[j]);
			}
		}
		return ans;
	}
	bool is_palindrome(string s)
	{
		int l, r;
		for(l = 0, r = s.length() - 1; l < r;)
		{
			if(s[l] != s[r]) return false;
			++l, --r;
		}
		return true;
	}
public:
    vector<vector<string>> partition(string s) 
	{
		return bt(s);
    }
};



//上面的这个的代码虽然很好懂，但是速度却是相当慢，主要的时间话费在对ans对象的拷贝以及substr操作上了，下面这个代码是上面代码的改进版本，改进也是针对前面我说的两个问题
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string> > ret;
        if(s.empty()) return ret;
        
        vector<string> path;
        dfs(0, s, path, ret);
        
        return ret;
    }
    
    void dfs(int index, string& s, vector<string>& path, vector<vector<string> >& ret) {
        if(index == s.size()) {
            ret.push_back(path);
            return;
        }
        for(int i = index; i < s.size(); ++i) {
            if(isPalindrome(s, index, i)) {
                path.push_back(s.substr(index, i - index + 1));
                dfs(i+1, s, path, ret);
                path.pop_back();
            }
        }
    }
    
    bool isPalindrome(const string& s, int start, int end) {
        while(start <= end) {
            if(s[start++] != s[end--])
                return false;
        }
        return true;
    }
};
