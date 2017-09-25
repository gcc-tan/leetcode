//Surrounded Regions

/*
Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

For example,
X X X X
X O O X
X X O X
X O X X
After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X
*/

/*
将棋盘中所有被x包围的o翻转成x，类似于围棋被包围了，不同在于只有完全被x包围才算，而处于边界的不算是被完全包围
---------------------------------------------------------------------------------------------------------------------------------------------------------
思路就是从四条边开始dfs点o，将所有遍历的o都变成其他字符(e.g. $)，然后将剩下的o都变成x，然后将$,变成o即可

我首先的思路从中间的O开始遍历，将O都变成X，能到达边界就再变回去....代码实现起来想想都可怕

这个dfs代码在leetcode上跑大数据集合会报runtime error的错误，查了一下之后，说是栈调用层次太深

结果换成bfs就好了

*/

class Solution 
{
private:
	int row;
	int col;
	void dfs(vector<vector<char>> &board, int i, int j)
	{
		board[i][j] = '$';
		if(i > 0 && board[i-1][j] == 'O')//上
			dfs(board, i - 1, j);
		if(i < row - 1 && board[i+1][j] == 'O')//下
			dfs(board, i + 1, j);
		if(j > 0 && board[i][j-1] == 'O')//左
			dfs(board, i, j - 1);
		if(j < col - 1 && board[i][j+1] == 'O')//右
			dfs(board, i, j + 1);
	}
	void bfs(vector<vector<char>> &board, int i, int j)
	{
		int x, y, t;
		queue<int> q;//用i * col + j的方式存储坐标
		board[i][j] = '$';
		q.push(i * col + j);
		while(q.size())
		{
			t = q.front();
			q.pop();
			x = t / col, y = t % col;
			if(x > 0 && board[x-1][y] == 'O')
			{
				board[x-1][y] = '$';
				q.push((x - 1) * col + y);
			}
			if(x < row - 1 && board[x+1][y] == 'O')
			{
				board[x+1][y] = '$';
				q.push((x + 1) * col + y);
			}
			if(y > 0 && board[x][y-1] == 'O')
			{
				board[x][y-1] = '$';
				q.push(x * col + y - 1);
			}
			if(y < col - 1 && board[x][y+1] == 'O')
			{
				board[x][y+1] = '$';
				q.push(x * col + y + 1);
			}
		}
	}
public:
    void solve(vector<vector<char>>& board) 
	{
		if(board.size() == 0) return;
		int i, j, m = board.size(), n = board[0].size();
		this->row = m, this->col = n;
		//遍历四条边
		for(j = 0; j < n; ++j)
			if(board[0][j] == 'O')
				bfs(board, 0, j);
		if(m > 1)
		{
			for(j = 0; j < n; ++j)
				if(board[m-1][j] == 'O')
					bfs(board, m - 1, j);
		}
		for(i = 0; i < m; ++i)
			if(board[i][0] == 'O')
				bfs(board, i, 0);
		if(n > 1)
		{
			for(i = 0; i < m; ++i)
				if(board[i][n-1] == 'O')
					bfs(board, i, n - 1);
		}
		//将最后的棋盘按照要求转换
		for(i = 0; i < m; ++i)
		{
			for(j = 0; j < n; ++j)
			{
				if(board[i][j] == '$') board[i][j] = 'O';
				else if(board[i][j] == 'O') board[i][j] = 'X';
			}
		}
    }
};


