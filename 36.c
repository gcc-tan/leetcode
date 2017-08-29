//Valid Sudoku


/*
给出一个数独的棋盘，检查这个数独是否合法(这个棋盘中可能不完整，用.表示)。数独是否合法是看每行和没列都没有重复的数字，并且每个n(应该是9)宫格里面没有重复的数字。其实棋盘就是9*9的，然后有3*3的9宫格
-------------------------------------------------------------------------------------------------------------------------------
做法就是对每个数字进行遍历，计算到x = board[i][j]这个位置上的数字的时候就记录i行使用了数字x，j列使用了数字x，
*/


//普通的数独就是9*9的，没有必要用这些参数啊?
bool isValidSudoku(char** board, int boardRowSize, int boardColSize) 
{
	int u1[10][10] = {0}, u2[10][10] = {0}, u3[10][10] = {0}, i, j, num, idx;
	for(i = 0; i < boardRowSize; ++i)
	{
		for(j = 0;j < boardColSize; ++j)
		{
			if(board[i][j] == '.') continue;
			num = board[i][j] - '0';
			idx = i / 3 * 3 + j / 3;
			if(u1[i][num] || u2[j][num] || u3[idx][num]) return false;
			u1[i][num] = u2[j][num] = u3[idx][num] = 1;
		}
	}
	return true;
}



