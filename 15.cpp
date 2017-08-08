//3Sum











/*
Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note: The solution set must not contain duplicate triplets.

For example, given array S = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
*/

/*
这个题目貌似是见过的。就是给定一个数组，找到这个数组中所有三个数之和为零的所有不重复的组合

----------------------------------------------------------------------------------------------------------------------------------------------

首先回顾一下类似的问题。之前应该是在编程之美上看到的问题。题目的意思就是给定一个整数数组arr，然后给定一个sum，要求找到这个数组中所有的两个数的组合使得和为sum。

因为是两个数，假设为a + b = sum。先假设已经知道a的值，那么需要求的就是b的值，b = sum - a。因此我们需要做的就是遍历a的所有可能的值(就是遍历数组),查找b是否在数组中。
遍历操作需要的O(n)的时间是没有办法减少的，但是查找操作可以做文章。查找可以对数组排序再进行二分查找，此时的查找时间复杂度为log(n)，还可以利用空间换取时间，对数组建立一个hash表。
然后查找的时间复杂度就降低为O(1)了。

然后三个数的和为a + b + c = sum的做法和两个数的做法相似。首先先固定一个数a，然后就找b + c = sum -a的这样的b和c。因此为了加速查找这样的b和c，那就最首先对数组进行排序。所以整个程序的流程就是先排序，
在定义一个i去遍历a的位置。定义j和k去查找sum - arr[i] 的值(这里假设数组是升序排列，if arr[j] + arr[k] > sum - arr[i] k-- else j--)

*/


class Solution
{
public:
    vector<vector<int> > threeSum(vector<int>& nums)
	{
		int i, j, k, sum;
		vector<vector<int> > v;
		sort(nums.begin(), nums.end());
		for(i = 0; i + 2 < nums.size(); ++i)
		{
			sum = -nums[i];
			for(j = i + 1, k = nums.size() - 1; j < k;)
			{
				if(nums[j] + nums[k] > sum) --k;
				else if(nums[j] + nums[k] < sum) ++j;
				else
				{
					vector<int> tmp(3,0);
					tmp[0] = nums[i], tmp[1] = nums[j], tmp[2] = nums[k];
					v.push_back(tmp);

					//跳过相同的元素,防止有重复的组合出现
					//没有相同的时候就是j，k分别向后，向前移动
					while(j < k && nums[j] == tmp[1]) ++j;
					while(j < k && nums[k] == tmp[2]) --k;
				}
			}
			while(i + 2 < nums.size() && nums[i] == nums[i+1]) ++i;
		}
		return v;
    }
};

