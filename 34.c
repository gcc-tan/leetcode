//Search for a Range 



/*
Given an array of integers sorted in ascending order, find the starting and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].

*/


/*
给定目标数target，在升序的数组中找到索引的位置，位置是个范围，可能有重复的数字
----------------------------------------------------------------------------------
很明确的问题，思路就是直接二分查找，然后找到一个之后向左右扩展。额，好像是不对，这里有个时间复杂度的要求，我这个算法比较的次数和相同数的长度有关，像输入3,3,3,3,3,3这样的序列时间复杂度为O(n)

正确的做法应该是利用两次二分查找，一次找左边界，一次找右边界。注意代码中的关键部分，两次二分查找的时候代码类似，不同的是设置mid的值一个是一半的下取整，一个是一半的上取整。
这是为了能够在二分的情况下剩下两个数时mid被设置成新的值从而退出循环，否则退不出循环
*/


/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
//这个方法不符合时间复杂度的要求
int* searchRange(int* nums, int n, int target, int* returnSize) 
{
	int i, j, mid, *p = malloc(sizeof(int *) * 2);
	*returnSize = 2;
	for(i = 0, j = n - 1; i <= j;)
	{
		mid = i + (j - i) / 2;//说是防止索引的位置大了溢出
		if(nums[mid] > target) j = mid - 1;
		else if(nums[mid] < target) i = mid + 1;
		else break;
	}
	if(i > j)
	{
		p[0] = -1, p[1] = -1;
		return p;
	}
	for(i = mid; i > 0 && nums[i] == nums[i-1]; --i);
	for(j = mid; j < n - 1 && nums[j] == nums[j+1]; ++j);

	p[0] = i, p[1] = j;
	return p;
}
















/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int n, int target, int* returnSize) 
{
	int l, r, mid, l_bound, r_bound, *p = malloc(sizeof(int) * 2);
	*returnSize = 2;
	//找左边界
	for(l = 0, r = n - 1; l < r;)
	{
		mid = (l + r) / 2;
		if(nums[mid] > target) r = mid - 1;
		else if(nums[mid] < target) l = mid + 1;
		else r = mid;
	}
	l_bound = l;
	//找右边界
	for(l = 0, r = n - 1; l < r;)
	{
		mid = (l + r + 1) / 2;
		if(nums[mid] > target) r= mid - 1;
		else if(nums[mid] < target) l = mid + 1;
		else l = mid;
	}
	r_bound = r;

	if(nums[l_bound] != target)
	{
		p[0] = -1, p[1] = -1;
		return p;
	}
	p[0] = l_bound, p[1] = r_bound;
	return p;
}











//别人的c++代码，这的是和优秀的人之间的差距很大
vector<int> searchRange(int A[], int n, int target) 
{
    int i = 0, j = n - 1;
    vector<int> ret(2, -1);
    // Search for the left one
    while (i < j)
    {
        int mid = (i + j) /2;
        if (A[mid] < target) i = mid + 1;
        else j = mid;
    }
    if (A[i]!=target) return ret;//在第一次搜索完就判断有没有找到，比我的代码在没有找到目标的时候性能更优秀
    else ret[0] = i;
    
    // Search for the right one
    j = n-1;  // We don't have to set i to 0 the second time.//因为上面已经找到了左边界，所以不需要重置左边界的值，可以在这个基础上继续寻找右边界，这里又加快的查找的速度
    while (i < j)
    {
        int mid = (i + j) /2 + 1;	// Make mid biased to the right
        if (A[mid] > target) j = mid - 1;  
        else i = mid;				// So that this won't make the search range stuck.
    }
    ret[1] = j;
    return ret; 
}
