//Search a 2D Matrix



/*
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.
For example,

Consider the following matrix:

[
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
Given target = 3, return true.
*/



/*
给定一个二维数组，行内是有序的，行间也是有序的，需要你快速地查找一个给定的target是否在数组中
---------------------------------------------------------------------------------------------------------------
肯定就是一个而分查找的变种，思路很简单。二维数组中每个数字都对应矩阵中的唯一的位置,对应关系是num = i * n + j，(i, j)是坐标点
*/



class Solution 
{
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) 
	{
		if(!matrix.size() || !matrix[0].size()) 
			return false;
		int m = matrix.size(), n = matrix[0].size(), i, j, mid, l, r;
		for(l = 0, r = m * n - 1; l <= r;)
		{
			mid = (l + r) / 2;
			i = mid / n, j = mid % n;
			if(matrix[i][j] > target) r = mid - 1;
			else if(matrix[i][j] < target) l = mid + 1;
			else break;
		}
		if(l > r) return false;
		return true;
    }
};

