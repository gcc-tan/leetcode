//First Missing Positive

/*
Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space.
*/





/*
题目虽然写得很简单，但是可能是我的理解能力不太好。看了好一会儿才看明白

题目的意思是有一个无序的数组，要你寻找数组里面没有出现的，最小的正整数，时间复杂度是O(n)，只能使用常量的空间

----------------------------------------------------------------------------------------------------------------------------------------------------------
从时间复杂度的要求来看肯定是不能使用排序算法进行排序，然后找两个数之间有没有插入正数的空隙

在discuss中看到了一个很厉害的解法，不过这个解法很难想出来。如果给定的数组是A，那么它通过一个调整，A中的i位存放的是i + 1的值，所有的数都调整完了之后遍历数组找到第一个不是这个值的i，
然后返回i+1
*/



int firstMissingPositive(int* nums, int numsSize) 
{
	int i, tmp;
	for(i = 0; i < numsSize; ++i)
	{
		//while(nums[i] > 0 && nums[i] != i + 1 && nums[i] <= numsSize && nums[nums[i]-1] != nums[i])
		/*
		*上面的判断中仔细思考一下nums[i] != i + 1这个是多余的，因为当前的这次交换本来就是要把nums[i]的值放到正确的位置上，而后面这个nums[i] != nums[nums[i]-1]就已经判断了
		*两者的值是一样的，就没有必要交换了，这个时候已经是正确的值，两者的值不相同那么就需要将这个正确的值交换到正确的位置上
		*/
		while(nums[i] > 0 && nums[i] <= numsSize && nums[i] != nums[nums[i]-1])
		{
			//swap(nums[i], nums[nums[i]-1])
			tmp = nums[nums[i]-1];
			nums[nums[i]-1] = nums[i];
			nums[i] = tmp;
		}
	}

	for(i = 0; i < numsSize; ++i)
		if(nums[i] != i + 1)
			return i + 1;
	return i + 1;
}
