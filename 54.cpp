//Spiral Matrix


/*
Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

For example,
Given the following matrix:

[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
You should return [1,2,3,6,9,8,7,4,5].
*/

/*
题目的意思是给出一个二维数组，要你将数组像螺旋的形状输出成一维的形式
----------------------------------------------------------------------------------------------------------------------------
好像是腾讯招聘2016实习生的笔试题，我记得当时好像做的还可以，不知道为什么不给我面试的机会


1.很直接的想法也是和旋转图片的那道题目一样，通过一个左上角的顶点左边，边长确定四个顶点坐标，每次循环将上下左右对应的边上的点加入结果集合中


2.在discuss里面看到一个很好理解的代码，通过记录四个值row_begin, row_end, col_begin, col_end然后每从上，右，下，左进行操作++row_begin, --col_end, --row_end, ++col_begin
*/


//方法1，3ms
class Solution 
{
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) 
	{
		int m = matrix.size();
		vector<int> ans;
		if(m <= 0) return ans;
		int n = matrix[0].size(), m1 = m - 1, n1 = n - 1, i, j;//m1表示圈中横向的长度，n1表示纵向的长度

		for(i = 0; m1 > 0 && n1 > 0; ++i, m1 -= 2, n1 -= 2)//更新这个螺旋中横向和纵向的长度
		{
			for(j = i; j < i + n1; ++j)//上
				ans.push_back(matrix[i][j]);

			for(j = i; j < i + m1; ++j)//右
				ans.push_back(matrix[j][i+n1]);

			for(j = i + n1; j > i; --j)//下
				ans.push_back(matrix[i+m1][j]);

			for(j = i + m1; j > i; --j)//左
				ans.push_back(matrix[j][i]);
			
		}
		if(m1 == 0)
		{
			for(j = i; j <= i + n1; ++j)
				ans.push_back(matrix[i][j]);
		}
		else if(n1 == 0)
		{
			for(j = i; j <= i + m1; ++j)
				ans.push_back(matrix[j][i]);
		}
		return ans;
    }
};





//方法2的实现 0ms
class Solution 
{
public:
	vector<int> spiralOrder(vector<vector<int>> &matrix)
	{
		int i, j, row_begin, row_end, col_begin, col_end;
		vector<int> ans;
		
		if(matrix.size() == 0) return ans;

		row_begin = 0, col_begin = 0;
		row_end = matrix.size() - 1, col_end = matrix[0].size() - 1;

		while(row_begin <= row_end && col_begin <= col_end)
		{
			for(j = col_begin; j <= col_end; ++j)//上
				ans.push_back(matrix[row_begin][j]);
			++row_begin;

			for(i = row_begin; i <= row_end; ++i)//右
				ans.push_back(matrix[i][col_end]);
			--col_end;

			if(row_begin <= row_end)
			{
				for(j = col_end; j >= col_begin; --j)//下
					ans.push_back(matrix[row_end][j]);
				--row_end;
			}

			if(col_begin <= col_end)
			{
				for(i = row_end; i >= row_begin; --i)//左
					ans.push_back(matrix[i][col_begin]);
				++col_begin;
			}
		}
		return ans;
	}
};
