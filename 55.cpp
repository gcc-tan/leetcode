//Jump Game

/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false.
*/


/*
题目的意思是给一个整数的数组，然后数组的每个元素大小表示能够向后跳动的最大长度，问初始在第一个元素的位置，问是否能跳到最后一个元素
-------------------------------------------------------------------------------------------------------------------------------------
45题Jump Game II是问跳到最后一个需要的次数最小，这个题目只是问能否跳到最后一个元素。

主要的思想和之前的45题一样，用一个变量记录上一次跳动的最远距离，这个记录变量保证这次的点都可达，然后利用这个变量记录范围的点，更新下一次跳动的距离
*/



class Solution 
{
public:
    bool canJump(vector<int>& nums) 
	{
		int last = 0, i, n = nums.size();//last表示当前一轮的最远距离
		for(i = 0; i < n - 1 && i <= last; ++i)
		{
			if(i <= last)//保证扫描到的当前的i位置都能被覆盖
				last = max(last, i + nums[i]);
		}
		return last >= n - 1 ? true : false;
    }
};



//discuss里面的代码，想法差不多，比较简洁
bool canJump(int A[], int n) 
{
    int i = 0;
    for (int reach = 0; i < n && i <= reach; ++i)
        reach = max(i + A[i], reach);
    return i == n;
}
