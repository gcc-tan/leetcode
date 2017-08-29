//Sudoku Solver


/*
写一个能够填充数独的函数
----------------------------------------------------------------
典型的回溯，但是要注意在搜索的时候可以利用之前计算的行列格子数字填充的情况进行剪枝，否则9^81数量级肯定计算不出来
*/

//这个代码我还是很满意的，打败了82.6%的用户(还有17.24%是和我同样的速度)
typedef struct point
{
	int x,y;
	struct point *next;
}point;
int bt(char **board, char **used, point *p, int remain)
{
	int x = p[0].x, y = p[0].y, num, idx = x / 3 * 3 + y / 3;
	char (*u1)[10] = (char (*)[10])used[0], (*u2)[10] = (char (*)[10])used[1], (*u3)[10] = (char (*)[10])used[2];//将普通指针转换成指针数组，比较少见
	int find = 0;
	if(remain <= 0) return;
	for(num = 1; num < 10; ++num)
	{
		if(u1[x][num] || u2[y][num] || u3[idx][num]) continue;
		u1[x][num] = u2[y][num] = u3[idx][num] = 1;
		board[x][y] = '0' + num;
		find = bt(board, used, p + 1, remain - 1);
		if(find) return 1;
		board[x][y] = '.';
		u1[x][num] = u2[y][num] = u3[idx][num] = 0;
	}
	return 0;
}
void solveSudoku(char** board, int boardRowSize, int boardColSize) 
{
	char u1[10][10] = {0}, u2[10][10] = {0}, u3[10][10] = {0}, *used[3] = {u1[0], u2[0], u3[0]};
	int num, idx, i, j, remain = 0;
	point p[81];
	for(i = 0; i < boardRowSize; ++i)//通过预处理的方式取出需要填充的节点，利用前面计算过的节点的使用信息进行剪纸，减少搜索量
	{
		for(j = 0; j < boardColSize; ++j)
		{
			if(board[i][j] == '.')
			{
				p[remain].x = i;
				p[remain++].y = j;
				continue;
			}
			num = board[i][j] - '0';
			idx = i / 3 * 3 + j / 3;
			u1[i][num] = u2[j][num] = u3[idx][num] = 1;
		}
	}
	bt(board, used, p, remain);//使用指针数组，减少传递的参数
}
