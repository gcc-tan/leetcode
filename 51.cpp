//N-Queens

/*
The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.



Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
*/

/*
n皇后问题，n*n的棋盘上要放置n个皇后，皇后之间不能相互攻击。皇后攻击的范围是横竖还有斜线方向任意多个格子
*/


class Solution 
{
private:
	vector<int> col;//该列是否放置过皇后
	/*
	*以3*3的矩阵为例子
	*dig1[0] 表示 (0, 0), (1, 1), (2, 2)
	*dig1[1] 表示 (1, 0), (2, 1)
	*dig1[2] 表示 (2, 0)
	*dig1[3] 表示 (0, 1), (1, 2)
	*dig1[4] 表示 (0, 2)
	*dig2就是与dig1垂直的方向
	*/
	vector<int> dig1;//表示45°的斜线是否放置过皇后
	vector<int> dig2;//表示135°的斜线是否放置过皇后
	vector<string> board;
	int n;//皇后的个数
	void bt(vector<vector<string>> &ans, int row)
	{
		if(row >= n) 
		{
			ans.push_back(board);
			return;
		}
		int n = board.size(), i, j, idx1, idx2;//idx1,idx2表示在dig1, dig2中的位置
		for(j = 0; j < n; ++j)
		{
			if(col[j]) continue;

			if(row < j) idx1 = n + j - row - 1;
			else idx1 = row - j;
			idx2 = row + j;
			if(dig1[idx1] || dig2[idx2]) continue;

			board[row][j] = 'Q';
			col[j] = true;
			dig1[idx1] = true;
			dig2[idx2] = true;

			bt(ans, row + 1);

			board[row][j] = '.';
			col[j] = false;
			dig1[idx1] = false;
			dig2[idx2] = false;
		}
	}
public:
	vector<vector<string>> solveNQueens(int n) 
	{
		vector<vector<string>> ans;
		board.resize(n), col.resize(n), dig1.resize(2 * n - 1), dig2.resize(2 * n - 1);
		this->n = n;
		fill(board.begin(), board.end(), string(n, '.'));
		fill(col.begin(), col.end(), false);
		fill(dig1.begin(), dig1.end(), false);
		fill(dig2.begin(), dig2.end(), false);
		bt(ans, 0);
		return ans;
	}
};




/*
不看完discuss里面的解答我都感觉不算做完这道题目。discuss里面的解答总是让人耳目一新
*/

/*
这是最直接的方法，还有一个和这个类似的写法，他用一个长度为n的数组a表示皇后的信息，a[i] = j表示i行的皇后在j列上，搜索的过程与这个类似。
In this problem, we can go row by row, and in each position, we need to check if the column, the 45° diagonal and the 135° diagonal had a queen before.

Solution A: Directly check the validity of each position, 12ms:
*/
class Solution {
public:
    std::vector<std::vector<std::string> > solveNQueens(int n) {
        std::vector<std::vector<std::string> > res;
        std::vector<std::string> nQueens(n, std::string(n, '.'));
        solveNQueens(res, nQueens, 0, n);
        return res;
    }
private:
    void solveNQueens(std::vector<std::vector<std::string> > &res, std::vector<std::string> &nQueens, int row, int &n) {
        if (row == n) {
            res.push_back(nQueens);
            return;
        }
        for (int col = 0; col != n; ++col)
            if (isValid(nQueens, row, col, n)) {
                nQueens[row][col] = 'Q';
                solveNQueens(res, nQueens, row + 1, n);
                nQueens[row][col] = '.';
            }
    }
    bool isValid(std::vector<std::string> &nQueens, int row, int col, int &n) {
        //check if the column had a queen before.
        for (int i = 0; i != row; ++i)
            if (nQueens[i][col] == 'Q')
                return false;
        //check if the 45° diagonal had a queen before.
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
            if (nQueens[i][j] == 'Q')
                return false;
        //check if the 135° diagonal had a queen before.
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j)
            if (nQueens[i][j] == 'Q')
                return false;
        return true;
    }
};
/*
这个方法就是我采用的方法，不过我的写法没有这个简洁
Solution B: Use flag vectors as bitmask, 4ms:

The number of columns is n, the number of 45° diagonals is 2 * n - 1, the number of 135° diagonals is also 2 * n - 1. When reach [row, col], the column No. is col, the 45° diagonal No. is row + col and the 135° diagonal No. is n - 1 + col - row. We can use three arrays to indicate if the column or the diagonal had a queen before, if not, we can put a queen in this position and continue.

NOTE: Please don't use vector<bool> flag to replace vector<int> flag in the following C++ code. In fact, vector<bool> is not a STL container. You should avoid to use it. You can also get the knowledge from here and here.

/**    | | |                / / /             \ \ \
  *    O O O               O O O               O O O
  *    | | |              / / / /             \ \ \ \
  *    O O O               O O O               O O O
  *    | | |              / / / /             \ \ \ \ 
  *    O O O               O O O               O O O
  *    | | |              / / /                 \ \ \
  *   3 columns        5 45° diagonals     5 135° diagonals    (when n is 3)
  * 上面这个图实在画得太形象了，利用上面这个图就可以很直接的算出这两种斜率的坐标点对应的索引。e.g. (0, 0)在45°投影对应坐标(n - 1, 1 - n)，(i, j)45°投影对应的坐标是(n - 1, i +　j - n + 1)，而(0, 0)对应的是索引0，那么(i, j)对应的是索引i + j，
  * 另外一个的计算方法类似
  */
*/
class Solution {
public:
    std::vector<std::vector<std::string> > solveNQueens(int n) {
        std::vector<std::vector<std::string> > res;
        std::vector<std::string> nQueens(n, std::string(n, '.'));
        std::vector<int> flag_col(n, 1), flag_45(2 * n - 1, 1), flag_135(2 * n - 1, 1);
        solveNQueens(res, nQueens, flag_col, flag_45, flag_135, 0, n);
        return res;
    }
private:
    void solveNQueens(std::vector<std::vector<std::string> > &res, std::vector<std::string> &nQueens, std::vector<int> &flag_col, std::vector<int> &flag_45, std::vector<int> &flag_135, int row, int &n) {
        if (row == n) {
            res.push_back(nQueens);
            return;
        }
        for (int col = 0; col != n; ++col)
            if (flag_col[col] && flag_45[row + col] && flag_135[n - 1 + col - row]) {
                flag_col[col] = flag_45[row + col] = flag_135[n - 1 + col - row] = 0;
                nQueens[row][col] = 'Q';
                solveNQueens(res, nQueens, flag_col, flag_45, flag_135, row + 1, n);
                nQueens[row][col] = '.';
                flag_col[col] = flag_45[row + col] = flag_135[n - 1 + col - row] = 1;
            }
    }
};
/*
这么写感觉没有太多的必要，前面一个写法还能清楚一些，这个是太过追求简洁的代码了
But we actually do not need to use three arrays, we just need one. Now, when reach [row, col], the subscript of column is col, the subscript of 45° diagonal is n + row + col and the subscript of 135° diagonal is n + 2 * n - 1 + n - 1 + col - row.
*/
class Solution {
public:
    std::vector<std::vector<std::string> > solveNQueens(int n) {
        std::vector<std::vector<std::string> > res;
        std::vector<std::string> nQueens(n, std::string(n, '.'));
        /*
        flag[0] to flag[n - 1] to indicate if the column had a queen before.
        flag[n] to flag[3 * n - 2] to indicate if the 45° diagonal had a queen before.
        flag[3 * n - 1] to flag[5 * n - 3] to indicate if the 135° diagonal had a queen before.
        */
        std::vector<int> flag(5 * n - 2, 1);
        solveNQueens(res, nQueens, flag, 0, n);
        return res;
    }
private:
    void solveNQueens(std::vector<std::vector<std::string> > &res, std::vector<std::string> &nQueens, std::vector<int> &flag, int row, int &n) {
        if (row == n) {
            res.push_back(nQueens);
            return;
        }
        for (int col = 0; col != n; ++col)
            if (flag[col] && flag[n + row + col] && flag[4 * n - 2 + col - row]) {
                flag[col] = flag[n + row + col] = flag[4 * n - 2 + col - row] = 0;
                nQueens[row][col] = 'Q';
                solveNQueens(res, nQueens, flag, row + 1, n);
                nQueens[row][col] = '.';
                flag[col] = flag[n + row + col] = flag[4 * n - 2 + col - row] = 1;
            }
    }
};
