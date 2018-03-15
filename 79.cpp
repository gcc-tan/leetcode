//Word Search

/*
Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

For example,
Given board =

[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]
word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
*/


/*
给出一个字母组成的二维数组，你可以从二维数组的任何一点出发，每个点只能走一次，每次移动只能移动到上下左右相邻的一个格子。判断给定的单词word能否由二维数组上的合法走法生成
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
1. 有个很直接的想法就是根据单词的第一个字符找到所有的开始点，然后从这点开始dfs
*/


/*
方法1的实现，在测试用例下超时了
["aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaaaaaab"]
"baaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
*/
class Solution 
{
public:
    bool exist(vector<vector<char>>& board, string word) 
	{
		int i, j, m = board.size(), n = board[0].size();
		bool ans = false;
		vector<vector<bool>> visit;
		for(i = 0; i < m; ++i)
			visit.push_back(vector<bool>(n, false));
		for(i = 0; i < m; ++i)
		{
			for(j = 0; j < n; ++j)
			{
				if(board[i][j] != word[0]) continue;
				ans |= dfs(i, j, word, 0, board, visit);
				if(ans) return true;
			}
		}
		return false;
    }

	bool dfs(int i, int j, string &s, int start, vector<vector<char>> &board, vector<vector<bool>> &visit)
	{
		int m = board.size(), n = board[0].size();
		bool ans = false;
		if(visit[i][j]) return false;
		visit[i][j] = true;
		if(start >= s.length() || (start + 1 == s.length() && board[i][j] == s[start])) return true;
		if(board[i][j] != s[start]) return false;
		/**
		 * 两个代码的差距在这4个递归的子条件，会进行4次，但是下面的使用短路的||，只要有一个子条件搜索成功就直接返回，放弃剩下的结点
		 */
		//上
		if(i > 0)
			ans |= dfs(i - 1, j, s, start + 1, board, visit);
		//下
		if(i + 1 < m)
			ans |= dfs(i + 1, j, s, start + 1, board, visit);
		//左
		if(j > 0)
			ans |= dfs(i, j - 1, s, start + 1, board, visit);
		//右
		if(j + 1 < n)
			ans |= dfs(i, j + 1, s, start + 1, board, visit);
		visit[i][j] = false;
		return ans;
	}
};



/*
参考discuss之后对代码进行修改

下面的代码确实是节省了空间，但是我感觉和之前的代码相比效率应该没有很大的提高，为什么上面的代码执行超时了，下面的这个代码还挺快的
*/
class Solution 
{
public:
    bool exist(vector<vector<char>>& board, string word) 
	{
		const char *p = word.c_str();
		int i, j, m = board.size(), n = board[0].size();
		for(i = 0; i < m; ++i)
		{
			for(j = 0; j < n; ++j)
			{
				if(board[i][j] != word[0]) continue;
				if(search(board, i, j, p))
					return true;
			}
		}
		return false;
    }
	bool search(vector<vector<char>> &board, int i, int j, const char *word)
	{
		bool ans = false;
		if(*word == '\0') 
			return true;
		if(i < 0 || j < 0 || i >= board.size() || j >= board[0].size())
			return false;
		if(board[i][j] != *word)
			return false;

		/*
		*这行很关键，首先理解起来很有困难。因为ascii码的码值是0~127所以所有的ascii码肯定是0xxxxxxx的形式，128是1000000
		*两者异或将最高位变为1，这个时候就不是任何一个合理的ascii码，就相当于这个点已经被访问过了，而在搜索完成之后再进行进行异或就能恢复原值，这个是因为
		*a ^ 10000000 ^ 10000000 = a ^ (10000000 ^ 10000000) = a ^ 00000000 = a
		*/
		board[i][j] ^= 128;
		ans = search(board, i - 1, j, word + 1) || search(board, i + 1, j, word + 1) || search(board, i, j - 1, word + 1) || search(board, i, j + 1, word + 1);

		board[i][j] ^= 128;

		return ans;
	}
};
