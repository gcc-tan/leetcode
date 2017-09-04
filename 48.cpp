//Rotate Image



/*
You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Note:
You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

Example 1:

Given input matrix = 
[
  [1,2,3],
  [4,5,6],
  [7,8,9]
],

rotate the input matrix in-place such that it becomes:
[
  [7,4,1],
  [8,5,2],
  [9,6,3]
]
Example 2:

Given input matrix =
[
  [ 5, 1, 9,11],
  [ 2, 4, 8,10],
  [13, 3, 6, 7],
  [15,14,12,16]
], 

rotate the input matrix in-place such that it becomes:
[
  [15,13, 2, 5],
  [14, 3, 4, 1],
  [12, 6, 8, 9],
  [16, 7,10,11]
]
*/


/*
就是给一个二维n*n矩阵每个点都顺时针旋转90度
-------------------------------------------------------------------------------------------------------------------------
1. 一个很直观的想法就是一圈圈的旋转，首先从(0, 0)点开始最外围的一圈，然后从(1, 1)开始内一层一圈，一直到所有的圈的移动结束

2. 有旋转的算法
顺时针旋转就是先按行反转，第一行变成最后一行，第二行变成倒数第二行。然后再沿着从左上到右下的对角线交换元素
e.g.
123    789      741
456 => 456  =>  852
789    123      963

逆时针旋转
先按照列反转，第一列变成最后一列，第二列变成倒数第二列。然后同样沿着对角线交换元素
123    321     369
456 => 654  => 258
789    987     147
*/



//方法1的实现
class Solution 
{
public:
    void rotate(vector<vector<int>>& matrix) 
	{
		int i, j, n = matrix.size(), len = n - 1, tmp;
		for(i = 0; i < n / 2; ++i)
		{
			for(j = i; j < i + len; ++j)
			{
				//(i,j)表示需要移动的点,就是每个从左上角顶点开始长度为len个点

				//与(i,j)对应的4个边上的位置都要移动,这几个坐标是通过四个定点(i,i),(i,i+len),(i+len,i+len),(i+len,i)四个顶点确定的
				tmp = matrix[i][j];
				matrix[i][j] = matrix[2*i-j+len][i];
				matrix[2*i-j+len][i] = matrix[i+len][2*i-j+len];
				matrix[i+len][2*i-j+len] = matrix[j][i+len];
				matrix[j][i+len] = tmp;
			}
			len -= 2;
		}
    }
};



//方法2实现
class Solution 
{
public:
    void rotate(vector<vector<int>>& matrix) 
	{
		int i, j, n = matrix.size();
		reverse(matrix.begin(), matrix.end());

		for(i = 0; i < n; ++i)
			for(j = 0; j < i; ++j)
				swap(matrix[i][j], matrix[j][i]);
    }
};










