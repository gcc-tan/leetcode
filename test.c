#include<iostream>
#include<stdlib.h>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<stack>
using namespace std;

class Solution
{
public:
    void rotate(vector<vector<int>>& matrix)
	{
		int i, j, n = matrix.size(), len = n, tmp;
		for(i = 0; i < n / 2; ++i)
		{
			--len;
			for(j = i; j < i + len; ++j)
			{
				//(i,j)表示需要移动的点,就是每个从左上角顶点开始长度为len个点

				//与(i,j)对应的4个边上的位置都要移动
				tmp = matrix[i][j];
				matrix[i][j] = matrix[i+len-j][i];
				matrix[i+len-j][i] = matrix[i+len][i+len-j];
				matrix[i+len][i+len-j] = matrix[i+j][i+len];
				matrix[i+j][i+len] = tmp;
			}
		}
    }
};





int main()
{
    Solution s;
    int a[7][7] = {{43,39,3,33,37,20,14},{9,18,9,-1,40,22,38},{14,42,3,23,12,14,32},{18,31,45,11,8,-1,31},{28,44,14,23,40,24,13},{29,45,33,45,20,0,45},{12,23,35,32,22,39,8}};
    vector<vector<int>> m;
    for(int i = 0; i < 7; ++i)
    {
        vector<int> tmp(a[i], a[i+1]);
        m.push_back(tmp);
    }
    s.rotate(m);
    return 0;
}













