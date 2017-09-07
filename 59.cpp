//Spiral Matrix II

/*
Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

For example,
Given n = 3,

You should return the following matrix:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]
*/


/*
和之前的题目一模一样，就是螺旋型地填入数字
*/


class Solution 
{
public:
    vector<vector<int>> generateMatrix(int n) 
	{
		int i, j, row_begin, row_end, col_begin, col_end, cnt = 0;
		vector<vector<int>> ans;
		for(i = 0; i < n; ++i)
			ans.push_back(vector<int>(n));

		row_begin = 0, col_begin = 0;
		row_end = n - 1, col_end = n - 1;

		while(row_begin <= row_end && col_begin <= col_end)
		{
			for(j = col_begin; j <= col_end; ++j)//上
				ans[row_begin][j] = ++cnt;
			++row_begin;

			for(i = row_begin; i <= row_end; ++i)//右
				ans[i][col_end] = ++cnt;
			--col_end;

			if(row_begin <= row_end)
			{
				for(j = col_end; j >= col_begin; --j)//下
					ans[row_end][j] = ++cnt;
				--row_end;
			}

			if(col_begin <= col_end)
			{
				for(i = row_end; i >= row_begin; --i)
					ans[i][col_begin] = ++cnt;
				++col_begin;
			}
		}
		return ans;
    }
};
