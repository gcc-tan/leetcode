//Jump Game II

/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

For example:
Given array A = [2,3,1,1,4]

The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)

Note:
You can assume that you can always reach the last index.
*/



/*
给定一个正数的数组，里面每个数字代表你能从该位置向后移动的最大长度，现在你从开始位置，要求跳到最后位置的最少的步数
1. 第一个想到的方法就是递归，从起始位置0开始，能够向后移动的最远的步数就是nums[0]，所以穷举1~nums[0]的步数，进行递归调用，取其中最小的就行。
但是这个方法效率上很大的问题，不难看出来这个方法时间复杂度是指数级别的。首先没注意我以为是死循环了，我说leetcode上运行怎么超时了

2.效率稍高的办法应该是动态规划，dp[i]表示从0到达i需要最短的跳数，先从0位置开始，初始条件dp[0] = 0,遍历每个位置，然后利用当前的dp[i]和nums[i]去更新i+1 ~ i+nums[i]的dp值，更新的办法就是
dp[j] = min(dp[j], dp[i] + 1)，这个算法的时间复杂度应该是O(n^2)

3.这个还是看代码吧，其实主要的方法就是贪心，每次跳动都是跳到当前能够覆盖最远的位置
*/


//方法1的实现，效率很低
#define MIN(a, b) ((a) < (b) ? (a) : (b))
int jump(int* nums, int numsSize)
{
	int i, ans = 0x3f3f3f3f;
	if(numsSize <= 1) return 0;
	for(i = 1; i <= nums[0] && i < numsSize; ++i)
		ans = MIN(ans, jump(nums + i, numsSize - i) + 1);
	return ans;
}






//方法2的实现，搞不懂O(n^2)的时间复杂度，也不是特别大，居然要622ms，真的是惭愧
#define MIN(a, b) ((a) < (b) ? (a) : (b))
int jump(int *nums, int numsSize)
{
	int i, j, *dp = malloc(numsSize * sizeof(int)), ans;
	//初始值
	dp[0] = 0;
	for(i = 1; i < numsSize; ++i)
		dp[i] = numsSize;
	for(i = 0; i < numsSize; ++i)//遍历位置
		for(j = i + 1; j <= i + nums[i] && j < numsSize; ++j)//利用当前i位置，以及i位置能够到达的最远距离更新dp数组
			dp[j] = MIN(dp[j], dp[i] + 1);

	ans = dp[numsSize-1];
	free(dp);
	return ans;
}


/*
 * We use "last" to keep track of the maximum distance that has been reached
 * by using the minimum steps "ret", whereas "curr" is the maximum distance
 * that can be reached by using "ret+1" steps. Thus,
 * curr = max(i+A[i]) where 0 <= i <= last.
 */
#define MAX(a, b) ((a) > (b) ? (a) : (b))
int jump(int *nums, int numsSize)
{
	int i, last = 0, cur = 0, ret = 0;
	for(i = 0; i < numsSize; ++i)
	{
		/*
		* last表示上一次跳动的位置，如果超过上次跳动的范围，那么跳动的次数要增加1,并且要更新last的值为当前这一次最远的距离
		*/
		if(i > last)
		{
			last = cur;
			++ret;
		}
		cur = MAX(cur, i + nums[i]);
	}
	return ret;
}
