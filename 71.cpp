//Simplify Path
/*
Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"
click to show corner cases.

Corner Cases:
 Did you consider the case where path = "/../"?
 In this case, you should return "/".
 Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
 In this case, you should ignore redundant slashes and return "/home/foo".
*/


/*
题目很切实际，就是将输入的unix风格的路径进行化简
*/

class Solution 
{
public:
    string simplifyPath(string path) 
	{
		int i, j, n;
		string cur, ans;//cur当前一级的目录名字
		vector<string> st;//栈，保存每级目录的名字，遇到"."不处理，遇到".."弹栈，其他情况入栈
		for(i = 1; i < path.size(); ++i)//去除冗余的'/'
		{
			if(path[i-1] == '/' && path[i] == '/') 
			{
				path.erase(i, 1);
				--i;
			}
		}
		if(path.back() == '/') path.erase(path.length() - 1);
		n = path.size();
		for(i = 0; i < n; ++i)//遍历每个目录的名字
		{
			if(path[i] != '/') continue;
			for(j = i + 1; j < n && path[j] != '/'; ++j);
			cur = path.substr(i + 1, j - i - 1);
			if(cur == ".") continue;
			if(cur != "..") 
			{
				st.push_back(cur);
				continue;
			}
			if(!st.empty())
				st.pop_back();
		}
		if(st.empty()) return "/";
		for(i = 0; i < st.size(); ++i)
			ans += "/" + st[i];
		return ans;
    }
};




/*
我发现我的代码就是造车轮子造太多
*/
string simplifyPath(string path) {
    string res, tmp;
    vector<string> stk;
    stringstream ss(path);//利用path构造一个流对象
    while(getline(ss,tmp,'/')) {//第一个是流对象，第二个是返回的结果，第三个是结尾标识
        if (tmp == "" or tmp == ".") continue;
        if (tmp == ".." and !stk.empty()) stk.pop_back();
        else if (tmp != "..") stk.push_back(tmp);
    }
    for(auto str : stk) res += "/"+str;
    return res.empty() ? "/" : res;
}
