//Remove Duplicates from Sorted Array 


/*
Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

For example,
Given input array nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. It doesn't matter what you leave beyond the new length(留下来的空间超过了新长度)
*/


/*
给定一个有序数组，去除数组中重复的元素，不能使用额外的空间.(这些元素就在原来的空间上存储，从开始的位置存)
---------------------------------------------------------------------------------------------------------------------------------------
正确的做法是利用两个指针，一个指针是去除掉重复元素的最后一个位置i，一个是向后遍历的位置j，这两个位置值不相同就进行赋值i向后移动
*/


class Solution 
{
public:
    int removeDuplicates(vector<int>& nums) 
	{
		int i, j, n = nums.size();
		if(n == 0) return 0;
		for(i = 0, j = 1; j < n; ++j)
		{
			if(nums[j] != nums[i])
				nums[++i] = nums[j];
		}
		return i + 1;
    }
};

