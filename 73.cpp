//Set Matrix Zeroes

/*

Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.

click to show follow up.

Follow up:
Did you use extra space?
A straight forward solution using O(mn) space is probably a bad idea.
A simple improvement uses O(m + n) space, but still not the best solution.
Could you devise a constant space solution?

*/


/*
题目的意思就是矩阵中有一个位置是0,那么那个元素所在的行和列都设置为0，最后将矩阵输出
-----------------------------------------------------------------------------------------------------------------
题目的要求是用常量的空间。m和n表示矩阵的行列，如果能使用O(m*n)的空间那么问题就很简单，直接重新申请一个m*n的矩阵p，扫描原来的矩阵s，s中为0的行列在p中都设置为0。最后再扫描原来的矩阵s，如果s中(i, j)
p[i][j] == 0 那么s[i][j]就设置为0。再优化空间可以用hash表row，col表示为0的那些行和列，也是很上面方法类似，扫描s，更新row和col，最后遍历s，只要(i, j)中i在row中，或者j在col中就设置为0。
这个时候空间复杂度降低成O(m + n)

空间复杂度为O(1)的算法

看完解决方案我这个心里阴影面积很大，我以为是真的能够节省空间。原来就是利用了原有的空间进行记录。主要思想是将这一行或者这列的状态(是否为0)记录在行开始或者是列开始的位置，需要注意的是
第一行和第一列有交叉，不能放在行首，那就放在两个变量row0,col0中表示行列的状态信息

*/


class Solution 
{
public:
    void setZeroes(vector<vector<int>>& matrix) 
	{
		int i, j, row0 = 1, col0 = 1, m = matrix.size(), n = matrix[0].size();
		//获取行列的状态信息
		for(i = 0; i < m; ++i)
		{
			for(j = 0; j < n; ++j)
			{
				if(matrix[i][j] != 0) continue;
				if(i != 0 && j != 0)
				{
					matrix[i][0] = 0;
					matrix[0][j] = 0;
				}
				else if(i == 0 && j != 0)
				{
					row0 = 0;
					matrix[0][j] = 0;
				}
				else if(i != 0 && j == 0)
				{
					matrix[i][0] = 0;
					col0 = 0;
				}
				else
					row0 = col0 = 0;
			}
		}

		for(i = m - 1; i >= 0; --i)//行倒着更新的原因是防止第一行(所有的列头)被更新，破坏了状态信息
		{
			for(j = n - 1; j >= 0; --j)//列反序更新也是为了防止第一列(行首)被提前更新破坏了状态信息
			{
				if(i != 0 && j != 0 && (matrix[i][0] == 0|| matrix[0][j] == 0))
					matrix[i][j] = 0;
				else if(i == 0 && j != 0 && (row0 == 0 || matrix[0][j] == 0))
					matrix[i][j] = 0;
				else if(i != 0 && j == 0 && (matrix[i][0] == 0 || col0 == 0))
					matrix[i][j] = 0;
				else if(i == 0 && j == 0 && (row0 == 0 || col0 == 0))
					matrix[i][j] = 0;
			}
		}
    }
};


//上面这个是第一版的代码，很复杂，参考discuss里面的代码写了一个，简单了不少，主要是没有用row0这个变量，只用col0,row0用原来的matrix[0][0]代替了
class Solution 
{
public:
    void setZeroes(vector<vector<int>>& matrix) 
	{
		int m = matrix.size(), n = matrix[0].size(), i, j, col0 = 1;

		for(i = 0; i < m; ++i)
		{
			if(matrix[i][0] == 0) col0 = 0;
			for(j = 1; j < n; ++j)//j == 0的那一列没有必要检查了
			{
				if(matrix[i][j] != 0) continue;
				matrix[i][0] = matrix[0][j] = 0;
			}
		}

		for(i = m - 1; i >= 0; --i)
		{
			for(j = n - 1; j >= 1; --j)
			{
				if(matrix[i][0] == 0 || matrix[0][j] == 0)
					matrix[i][j] = 0;
			}
			if(col0 == 0) matrix[i][0] = 0;
		}
    }
};
