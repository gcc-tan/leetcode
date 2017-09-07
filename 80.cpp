//Remove Duplicates from Sorted Array II

/*
What if duplicates are allowed at most twice?

For example,
Given sorted array nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond the new length(留下的空间超过了新的长度)
*/


/*
和之前的Remove Duplicates from Sorted Array一样，要求都是去除重复的元素，返回长度，但是这里不同的是元素可以出现两次
---------------------------------------------------------------------------------------------------------------------------
也是用两个指针，一个记录最多两个重复元素的最后一个位置i，另外一个用来遍历的j，然后用一个变量two记录i这个元素在[0,i]中出现的次数
*/


class Solution 
{
public:
    int removeDuplicates(vector<int>& nums) 
	{
		int i, j, n = nums.size(), two = 1;//two
		if(n <= 2) return n;
		for(i = 0, j = 1; j < n; ++j)
		{
			if(nums[i] != nums[j])
			{
				two = 1;
				nums[++i] = nums[j];
			}
			else if(nums[i] == nums[j] && two == 1)
			{
				two = 2;
				nums[++i] = nums[j];
			}
		}
		return i + 1;
    }
};



//discuss里面的c++代码，看了discuss里面的代码你才知道别人的代码有多厉害
int removeDuplicates(vector<int>& nums) {
    int i = 0;
    for (int n : nums)
        if (i < 2 || n > nums[i-2])//这个判断利用了递增关系，利用了长度最多为2的条件，真是写的好
            nums[i++] = n;
    return i;
}
