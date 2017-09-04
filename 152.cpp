//Maximum Product Subarray

/*
Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.
*/

/*
题目的意思很好懂，就是给出一个数组a，要求出这些元素中连续的乘积最大的那个
-------------------------------------------------------------------------------------------------------------------------------------------
这个题目之前应该是见过，可能是在编程之美上面见过的。和最大子段和的解法类似，这里要维护两个变量，一个是imax，imin当前最小和当前最大，因为有负数的存在求imax时需要用到imin的信息
*/

class Solution 
{
public:
    int maxProduct(vector<int>& nums) 
	{
		int imin, imax, ans, n = nums.size(), i;
		imin = imax = ans = nums[0];

		for(i = 1; i < n; ++i)
		{
			if(nums[i] < 0)//如果当前位置的数是负数，需要交换imin,imax对imax和imin的更新是正确的
				swap(imax, imin);
			imax = max(nums[i], nums[i] * imax);//imax是以nums[i]为上界的
			imin = min(nums[i], nums[i] * imin);//imin是以nums[i]为下界的
			ans = max(ans, imax);
		}
		return ans;
    }
};
