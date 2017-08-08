#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
//3Sum Closest

/*
Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

    For example, given array S = {-1 2 1 -4}, and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/

/*
做法和之前的15题3Sum一样，基本没有什么改动
*/
//下面的代码是看了别人的代码改了一点，之前我自己的代码比较生硬，罗嗦
class Solution 
{
public:
#define ABS(a) ((a) > 0 ? (a) : -(a))
    int threeSumClosest(vector<int>& nums, int target) 
	{
		int i, sum, l, r, ret = 0x3f3f3f3f;
		sort(nums.begin(),nums.end());
		for(i = 0; i < nums.size(); ++i)
		{
			for(l = i + 1, r = nums.size() - 1; l < r;)
			{
				sum = nums[i] + nums[l] + nums[r];
				if(target < sum)
				{
					if(ABS(ret - target) > ABS(sum - target))
						ret = sum;
					--r;
				}
				else if(target > sum)
				{
					if(ABS(ret - target) > ABS(sum - target))
						ret = sum;
					++l;
				}
				else
					return target;
			}
		}
		return ret;
    }
};

/*
之前写的代码，改了之后效率有一点提升。感觉应该不至于这么差劲吧
class Solution
{
public:
#define ABS(a) ((a) > 0 ? (a) : -(a))
    int threeSumClosest(vector<int>& nums, int target)
	{
		int i, sum, l, r, ret = 0x3f3f3f3f;
		sort(nums.begin(),nums.end());
		for(i = 0; i < nums.size(); ++i)
		{
			sum = target - nums[i];
			for(l = i + 1, r = nums.size() - 1; l < r;)
			{
				if(nums[l] + nums[r] > sum)
				{
					if(ABS(ret - target) > ABS(nums[l] + nums[r] - sum))
						ret = nums[i] + nums[l] + nums[r];
					--r;
				}
				else if(nums[l] + nums[r] < sum)
				{
					if(ABS(ret - target) > ABS(nums[l] + nums[r] - sum))
						ret = nums[i] + nums[l] + nums[r];
					++l;
				}
				else
					return target;
			}
		}
		return ret;
    }
};
*/

int main()
{
	Solution s;
	vector<int> nums(4,0);
	nums[0] = 1, nums[1] = 1, nums[2] = 1;
	cout<<s.threeSumClosest(nums, 0)<<endl;
}
